/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 12-7-2013
Start hour: 6:25 PM (Pacific hour)

Purpose: Material/image modification stuff.

*/

#include "stdafx.h"
#include "Hooking.h"
#include "GameDefinitions.h"
#include "GamePatches.h"
#include "google/dense_hash_map"

using google::dense_hash_map;

//static dense_hash_map<const char*, Material*, asset_hash<const char*>> materialTable;
static dense_hash_map<std::string, Material*, stdext::hash_compare<std::string>> materialTable;

unsigned int R_HashString(const char* string)
{
	unsigned int hash = 0;

	while (*string)
	{
		hash = (*string | 0x20) ^ (33 * hash);
		string++;
	}

	return hash;
}

typedef int (__cdecl * _Reader_t)(int, int); // defaulting to int for now
typedef bool (__cdecl * Image_LoadFromFileWithReader_t)(Image* image, _Reader_t reader);
Image_LoadFromFileWithReader_t Image_LoadFromFileWithReader = (Image_LoadFromFileWithReader_t) 0x53ABF0;

typedef void (__cdecl * Image_Release_t)(Image* image);
Image_Release_t Image_Release = (Image_Release_t) 0x51F010;

// a3 is 'disable data needed for smoothing' or so, maybe 'do not auto-generate mipmaps'?
Image* Image_Alloc(const char* name, char a2, char a3, char a4)
{
	Image* memory = (Image*) malloc(sizeof(Image) + strlen(name) + 1);
	memset(memory, 0, sizeof(Image));

	memory->a2 = a2;
	memory->a3 = a3;
	memory->a4 = a4;
	memory->name = ((char*) memory) + sizeof(Image);
	strcpy(memory->name, name);

	return memory;
}

Image* Image_Load(const char* name)
{
	Image* image = Image_Alloc(name, 3, 0, 0);
	Image_LoadFromFileWithReader(image, (_Reader_t)/*0x42ECA0*/0x46CBF0);
	return image;
}

static unsigned char stateMapCopy[8];
static bool stateMapCopied = false;

static void Material_InitializeStateMap()
{
	if (stateMapCopied) return;

	Material* base = (Material*) DB_FindXAssetHeader(ASSET_TYPE_MATERIAL, "ui_cursor");
	memcpy(stateMapCopy, base->stateMap, 8);
	stateMapCopied = true;
}

Material* Material_Create(const char* name, const char* imageFile)
{
	Material* material = new Material;
	memset(material, 0, sizeof(Material));

	material->maps = new MaterialImage;
	memset(material->maps, 0, sizeof(MaterialImage));

	Material_InitializeStateMap();

	material->name = name;
	//material->flags = 0x2F00;
	material->flags = 0x2200;
	material->animationX = 1;
	material->animationY = 1;
	material->unknown2 = 0xFFFFFFFF;
	material->unknown3 = 0xFFFFFF00;
	memset(material->unknown4, 0xFF, sizeof(material->unknown4));
	material->numMaps = 1;
	material->unknownCount2 = 1;
	material->unknown6 = 3;
	material->unknown7 = 4;
	material->techniqueSet = DB_FindXAssetHeader(ASSET_TYPE_TECHSET, "2d");

	material->maps->typeHash = R_HashString("colorMap");
	material->maps->firstCharacter = 'c';
	material->maps->secondLastCharacter = 'p';
	material->maps->unknown = 0xE2; // causes some nice filtering
	material->maps->image = Image_Load(imageFile);

	material->stateMap = stateMapCopy;

	return material;
}

Material* Material_Obtain(const char* name, const char* imageFile)
{
	if (!materialTable[name])
	{
		materialTable[name] = Material_Create(name, imageFile);
	}

	return materialTable[name];
}

void Material_Delete(const char* name, const char* imageCondition)
{
	if (materialTable[name])
	{
		if (!imageCondition)
		{
			materialTable[name] = NULL;
		}
		else
		{
			if (!_stricmp(materialTable[name]->maps[0].image->name, imageCondition))
			{
				Image_Release(materialTable[name]->maps[0].image);
				free(materialTable[name]->maps[0].image);
				materialTable[name] = NULL;
			}
		}
	}
}

const char* LoadScreens_Filename();

Material* Material_Register(const char* filename)
{
	if (!_stricmp(filename, "preview_oilrig"))
	{
		return Material_Obtain(filename, filename);
	}

	if (!_stricmp(filename, "preview_gulag"))
	{
		return Material_Obtain(filename, filename);
	}

	if (!_stricmp(filename, "preview_invasion"))
	{
		return Material_Obtain(filename, filename);
	}

	if (!_stricmp(filename, "cardicon_t5_prestige_1"))
	{
		return Material_Obtain(filename, filename);
	}

	if (!_stricmp(filename, "hud_icon_wager"))
	{
		return Material_Obtain(filename, filename);
	}

	if (!_stricmp(filename, "$levelbriefingX"))
	{
		if (LoadScreens_Filename())
		{
			return Material_Obtain("$levelbriefingX", LoadScreens_Filename());
		}
	}

	return NULL;
}

StompHook materialLoadHook;
DWORD materialLoadHookLoc = 0x505E50;

void* MaterialLoadHookFunc(assetType_t type, const char* filename)
{
	Material* material = Material_Register(filename);

	if (material)
	{
		return material;
	}

	return (Material*) DB_FindXAssetHeader(ASSET_TYPE_MATERIAL, filename);
}

void Material_TableDebug_f()
{
	if (Cmd_Argc() < 2)
	{
		Com_Printf(0, "Usage: %s [material name]\n", Cmd_Argv(0));
		return;
	}

	Material* material = materialTable[Cmd_Argv(1)];
	Com_Printf(0, "%s is actually %s\n", Cmd_Argv(1), material->name);
}

cmd_function_t tDebugCmd;

void GamePatches::Materialism()
{
	materialTable.set_empty_key("");

	materialLoadHook.initialize(materialLoadHookLoc, MaterialLoadHookFunc);
	materialLoadHook.installHook();

	Cmd_AddCommand("materialTableDebug", Material_TableDebug_f, &tDebugCmd, 0);
}