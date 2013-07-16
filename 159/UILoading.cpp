/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 12-7-2013
Start hour: 6:01 PM (Pacific hour)

Purpose: UI file loading

*/

#include "stdafx.h"
#include "Hooking.h"
#include "GameDefinitions.h"
#include "GamePatches.h"

typedef script_t * (__cdecl * LoadScriptFile_t)(const char*) ;
typedef int (__cdecl * PC_ReadToken_t)(source_t*, token_t*);

LoadScriptFile_t LoadScriptFile = (LoadScriptFile_t) 0x480110;
PC_ReadToken_t PC_ReadToken = (PC_ReadToken_t) 0x4ACCD0;

source_t **sourceFiles = (source_t **) 0x7C4A98;
keywordHash_t **menuParseKeywordHash = (keywordHash_t **) 0x63AE928;

// 'shared' code
int KeywordHash_Key(char *keyword) 
{
	int register hash, i;
	hash = 0;

	for (i = 0; keyword[i] != '\0'; i++)
	{
		if (keyword[i] >= 'A' && keyword[i] <= 'Z')
			hash += (keyword[i] + ('a' - 'A')) * (119 + i);
		else
			hash += keyword[i] * (119 + i);
	}

	hash = (hash ^ (hash >> 10) ^ (hash >> 20)) & (KEYWORDHASH_SIZE - 1);
	
	return hash;
}

void FreeScript(script_t *script)
{
#ifdef PUNCTABLE
	if (script->punctuationtable) FreeMemory(script->punctuationtable);
#endif //PUNCTABLE
	free(script);
}

void StripDoubleQuotes(char *string)
{
	if (*string == '\"')
	{
		strcpy(string, string + 1);
	} //end if
	if (string[strlen(string) - 1] == '\"')
	{
		string[strlen(string) - 1] = '\0';
	} //end if
}

source_t *LoadSourceFile(const char *filename)
{
	source_t *source;
	script_t *script;

	script = LoadScriptFile(filename);
	if (!script) return NULL;

	script->next = NULL;

	source = (source_t *) malloc(sizeof(source_t));
	memset(source, 0, sizeof(source_t));

	strncpy(source->filename, filename, 64);
	source->scriptstack = script;
	source->tokens = NULL;
	source->defines = NULL;
	source->indentstack = NULL;
	source->skip = 0;
	source->definehash = (define_t**) malloc(4096);
	memset(source->definehash, 0, 4096);

	return source;
}

void FreeSource(source_t *source)
{
	script_t *script;
	token_t *token;
	define_t *define;
	indent_t *indent;
	//->int i;

	//PC_PrintDefineHashTable(source->definehash);
	//free all the scripts
	while (source->scriptstack)
	{
		script = source->scriptstack;
		source->scriptstack = source->scriptstack->next;
		FreeScript(script);
	} //end for
	//free all the tokens
	while (source->tokens)
	{
		token = source->tokens;
		source->tokens = source->tokens->next;
		//PC_FreeToken(token);
	} //end for
#if DEFINEHASHING
	for (i = 0; i < DEFINEHASHSIZE; i++)
	{
		while (source->definehash[i])
		{
			define = source->definehash[i];
			source->definehash[i] = source->definehash[i]->hashnext;
			PC_FreeDefine(define);
		} //end while
	} //end for
#else //DEFINEHASHING
	//free all defines
	while (source->defines)
	{
		define = source->defines;
		source->defines = source->defines->next;
		//PC_FreeDefine(define);
	} //end for
#endif //DEFINEHASHING
	//free all indents
	while (source->indentstack)
	{
		indent = source->indentstack;
		source->indentstack = source->indentstack->next;
		free(indent);
	} //end for
#if DEFINEHASHING
	//
	if (source->definehash) free(source->definehash);
#endif //DEFINEHASHING
	//free the source itself
	free(source);
}

#define MAX_SOURCEFILES		64

source_t* lastSource;

int PC_LoadSource(const char *filename)
{
	source_t *source;
	int i;

	for (i = 1; i < MAX_SOURCEFILES; i++)
	{
		if (!sourceFiles[i])
			break;
	} //end for
	if (i >= MAX_SOURCEFILES)
		return 0;
	//PS_SetBaseFolder("");
	source = LoadSourceFile(filename);
	if (!source)
		return 0;
	lastSource = source;
	sourceFiles[i] = source;
	return i;
}

int PC_FreeSource(int handle)
{
	if (handle < 1 || handle >= MAX_SOURCEFILES)
		return false;
	if (!sourceFiles[handle])
		return false;

	FreeSource(sourceFiles[handle]);
	sourceFiles[handle] = NULL;
	return true;
}

int PC_ReadTokenHandle(int handle, pc_token_t *pc_token)
{
	token_t token;
	int ret;

	if (handle < 1 || handle >= MAX_SOURCEFILES)
		return 0;
	if (!sourceFiles[handle])
		return 0;

	ret = PC_ReadToken(sourceFiles[handle], &token);
	strcpy(pc_token->string, token.string);
	pc_token->type = token.type;
	pc_token->subtype = token.subtype;
	//pc_token->intvalue = token.intvalue;
	//pc_token->floatvalue = (float) token.floatvalue;
	if (pc_token->type == TT_STRING)
		StripDoubleQuotes(pc_token->string);
	return ret;
}

void Menu_PostParse(menuDef_t *menu) {
	return;
	/*if (menu == NULL) {
	return;
	}
	if (menu->fullScreen) {
	menu->window.rect.x = 0;
	menu->window.rect.y = 0;
	menu->window.rect.w = 640;
	menu->window.rect.h = 480;
	}
	Menu_UpdatePosition(menu);*/
}

void Menu_Init(menuDef_t *menu) {
	memset(menu, 0, 2048);
	menu->items = (itemDef_t**) malloc(sizeof(itemDef_t*) * 512);
	//Window_Init(&menu->window);
}

int KeywordHash_Data(char* key)
{
	// patch this function on-the-fly, as it's some ugly C.
	DWORD func = 0x63FE90;
	int retval = 0;

	*(DWORD*) 0x63FE9E = 3523;
	*(DWORD*) 0x63FECB = 0x7F;

	__asm
	{
		mov eax, key
			call func
			mov retval, eax
	}

	*(DWORD*) 0x63FE9E = 531;
	*(DWORD*) 0x63FECB = 0x1FF;

	return retval;
}

//#define PC_SourceError(x, y, ...) Com_Printf(0, y, __VA_ARGS__)
#define PC_SourceError(x, y, ...) ((void (*)(int, const char*, ...))0x467A00)(x, y, __VA_ARGS__)

bool Menu_Parse(int handle, menuDef_t *menu) {
	pc_token_t token;
	keywordHash_t *key;

	if (!PC_ReadTokenHandle(handle, &token))
		return false;
	if (*token.string != '{') {
		return false;
	}

	while (1) {

		memset(&token, 0, sizeof(pc_token_t));
		if (!PC_ReadTokenHandle(handle, &token)) {
			PC_SourceError(handle, "end of file inside menu\n");
			return false;
		}

		if (*token.string == '}') {
			return true;
		}

		//key = KeywordHash_Find(menuParseKeywordHash, token.string);
		int idx = KeywordHash_Data(token.string);

		if (!_stricmp("onopen", token.string))
		{
			printf("a");
		}

		key = menuParseKeywordHash[idx];
		if (!key) {
			PC_SourceError(handle, "unknown menu keyword %s", token.string);
			continue;
		}
		if (!key->func((itemDef_t*) menu, handle)) {
			PC_SourceError(handle, "couldn't parse menu keyword %s", token.string);
			return false;
		}
	}
	return false; 	// bk001205 - LCC missing return value
}

menuDef_t* Menu_New(int handle) {
	menuDef_t *menu = (menuDef_t*) malloc(2048); // FIXME: tentative size

	Menu_Init(menu);
	if (Menu_Parse(handle, menu)) {
		Menu_PostParse(menu);
	}

	return menu;
}

std::vector<menuDef_t*> UI_ParseMenu(const char *menuFile) {
	int handle;
	pc_token_t token;
	std::vector<menuDef_t*> retval;


	handle = PC_LoadSource(menuFile);
	if (!handle) {
		return retval;
	}

	while (1) {
		memset(&token, 0, sizeof(pc_token_t));
		if (!PC_ReadTokenHandle(handle, &token)) {
			break;
		}

		if (token.string[0] == '}') {
			break;
		}

		if (_stricmp(token.string, "menudef") == 0) {
			// start a new menu
			retval.push_back(Menu_New(handle));
		}
	}

	PC_FreeSource(handle);

	return retval;
}

menuFile_t* UI_ParseScriptMenu(const char* filename)
{
	if (FS_ReadFile(filename, NULL) <= 0)
	{
		return (menuFile_t*) DB_FindXAssetHeader(ASSET_TYPE_MENUFILE, filename);
	}

	menuFile_t* newFile = (menuFile_t*) malloc(sizeof(menuFile_t));
	newFile->filename = (char*) filename;

	std::vector<menuDef_t*> menus = UI_ParseMenu(filename);

	newFile->count = menus.size();
	newFile->menuFiles = (menuDef_t**) malloc(sizeof(menuDef_t*) * menus.size());

	for (size_t i = 0; i < menus.size(); i++)
	{
		newFile->menuFiles[i] = menus[i];
	}

	return newFile;
}

menuDef_t* LoadScreens_MessWithConnectMenu(menuDef_t* menu);

menuFile_t* uimp_code;

std::vector<std::string> customMenusNames;

void* MenuFileHookFunc(const char* filename)
{
	menuFile_t* file = (menuFile_t*) DB_FindXAssetHeader(ASSET_TYPE_MENUFILE, filename);

	/*for(int i = 0; i < file->count; i++)
	{
	NS_LoadMW2Menus(file->menuFiles[i]);
	}*/

	if (!strcmp(file->menuFiles[0]->window.name, "default_menu"))
	{
		return UI_ParseScriptMenu(filename);
	}

	if (!strcmp(filename, "ui_mp/code.txt") && uimp_code)
	{
		return uimp_code;
	}

	int numCustomMenus = 0;

	if (!strcmp(filename, "ui_mp/menus.txt"))
	{
		numCustomMenus = customMenusNames.size();
	}

	menuFile_t* newFile = (menuFile_t*) malloc(sizeof(menuFile_t));
	memcpy(newFile, file, sizeof(menuFile_t));

	newFile->menuFiles = (menuDef_t**) malloc(sizeof(menuDef_t*) * (newFile->count + numCustomMenus));
	memset(newFile->menuFiles, 0, sizeof(menuDef_t*) * (newFile->count + numCustomMenus));
	memcpy(newFile->menuFiles, file->menuFiles, sizeof(menuDef_t*) * newFile->count);

	newFile->count += numCustomMenus;

	bool replacedMenu = false;

	for (int i = 0; i < file->count; i++)
	{
		menuDef_t* menu = file->menuFiles[i];

		if (!menu)
		{
			continue;
		}

		char uifilename[512];
		sprintf(uifilename, "ui_mp/%s.menu", menu->window.name);

		if (FS_ReadFile(uifilename, 0) >= 0)
		{
			std::vector<menuDef_t*> menus = UI_ParseMenu(uifilename);

			if (menus.size() > 0)
			{
				newFile->menuFiles[i] = menus[0];
			}

			if (menus.size() > 1)
			{
				Com_Printf(0, "Menu load warning: more than 1 menu in %s\n", uifilename);
			}

			replacedMenu = true;
		}
		else
		{
			// odd hook for loadscreens
			if (!strcmp(menu->window.name, "connect"))
			{
				newFile->menuFiles[i] = LoadScreens_MessWithConnectMenu(menu);

				replacedMenu = true;
			}
		}
	}

#define CUSTOM_MENU(name, id) { \
	std::vector<menuDef_t*> menu = UI_ParseMenu(name); \
	\
	if (menu.size() > 0) \
	{ \
	newFile->menuFiles[newFile->count - id] = menu[0]; \
	} \
	else \
	{ \
	newFile->count--; \
	} \
	}

	if (numCustomMenus)
	{
		/*CUSTOM_MENU("ui_mp/popup_friends.menu", 1);
		CUSTOM_MENU("ui_mp/clans_text.menu", 2);
		CUSTOM_MENU("ui_mp/friends_text.menu", 3);*/
		std::vector<std::string>::const_iterator cur, end;

		cur = customMenusNames.begin();
		end = customMenusNames.end();

		for (int i = 1; cur != end; cur++, i++)
		{
			// Add the menu to the list
			CUSTOM_MENU(cur->c_str(), i);
		}
	}

	if (!replacedMenu)
	{
		free(newFile->menuFiles);
		free(newFile);
	}
	else if (!strcmp(filename, "ui_mp/code.txt"))
	{
		uimp_code = newFile;
	}

	return (replacedMenu) ? newFile : file;
}

StompHook menuFileHook;
DWORD menuFileHookLoc = 0x63FE70;

void __declspec(naked) MenuFileHookStub()
{
	__asm jmp MenuFileHookFunc
}

CallHook uiAddMenuAssetHook;
DWORD uiAddMenuAssetHookLoc = 0x453406;

void __declspec(naked) UI_AddMenuAssetHookStub()
{
	__asm
	{
		cmp[esp + 28h], 0
			jz doOriginal
			xor eax, eax
			retn

		doOriginal :
		jmp uiAddMenuAssetHook.pOriginal
	}
}
cmd_function_t Cmd_OpenMenu;
void Cmd_OpenMenu_f()
{
	if (Cmd_Argc() != 2)
	{
		Com_Printf(0, "USAGE: openmenu <menu name>\n");
		return;
	}
	char* menu = Cmd_Argv(1);
	__asm
	{
		push menu
			push 62E2858h
			mov eax, 4CCE60h
			call eax
	}
}

void AddCustomMenuToList(const char* name)
{
	// Check if the file exists
	{
		// We want to check the files in m2demo, so we add it to the start of the name
		char fullFilename[256];
		sprintf(fullFilename, "m2demo/%s", name);

		FILE* fp = fopen(fullFilename, "rb+");

		// File does not exists, ignore it
		if (fp == NULL)
		{
			Com_Printf(16, "Menu %s does not exists", name);
			return;
		}

		fclose(fp);
	}

	// Insert the custom menu in the list
	customMenusNames.push_back(name);
}

void LoadCustomMenuListFromFile(const char* name)
{
	// Open the list
	FILE* fp = fopen(name, "rb+");

	// Check for errors
	if (fp == NULL) return;
	if (ferror(fp) || feof(fp)){ fclose(fp); return; }

	// Read every line while there are no errors
	while ((feof(fp) == false) && (ferror(fp) == false))
	{
		// Read one line
		char filename[256];
		fgets(filename, 256, fp);

		// Check if it exists and add it to the list
		AddCustomMenuToList(strtok(filename, "\r\n"));
	}

	// Close the file
	fclose(fp);
}

void GamePatches::UILoading()
{
	menuFileHook.initialize(menuFileHookLoc, MenuFileHookStub);
	menuFileHook.installHook();

	// disable the 2 new tokens in ItemParse_rect
	*(BYTE*) 0x640693 = 0xEB;

	// don't load ASSET_TYPE_MENU assets for every menu (might cause patch menus to fail)
	memset((void*) 0x453406, 0x90, 5);

	Cmd_AddCommand("openmenu", Cmd_OpenMenu_f, &Cmd_OpenMenu, 0);

	// Load the custom menus list from a txt(easier than hardcoding it)
	LoadCustomMenuListFromFile("m2demo/ui_mp/custommenus.txt");
}