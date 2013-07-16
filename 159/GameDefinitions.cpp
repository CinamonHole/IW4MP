/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 11-7-2013
Start hour: 11:34 PM (Pacific hour)

Purpose: Important game definitions

*/

#include "stdafx.h"
#include "GameDefinitions.h"

extern "C"
{
	DB_LoadXAssets_t DB_LoadXAssets = (DB_LoadXAssets_t) 0x4E5930;
	DB_FindXAssetHeader_t DB_FindXAssetHeader = (DB_FindXAssetHeader_t) 0x407930;

	FS_ReadFile_t FS_ReadFile = (FS_ReadFile_t) 0x4F4B90;

	Com_Error_t Com_Error = (Com_Error_t) 0x4B22D0;
	Com_Printf_t Com_Printf = (Com_Printf_t) 0x402500;

	Cmd_AddCommand_t Cmd_AddCommand = (Cmd_AddCommand_t) 0x470090;
}

DWORD* cmd_id = (DWORD*) 0x1AAC5D0;
DWORD* cmd_argc = (DWORD*) 0x1AAC614;
DWORD** cmd_argv = (DWORD**) 0x1AAC634;

int	Cmd_Argc(void)
{
	return cmd_argc[*cmd_id];
}

char *Cmd_Argv(int arg) 
{
	if ((unsigned) arg >= cmd_argc[*cmd_id]) 
	{
		return "";
	}

	return (char*) (cmd_argv[*cmd_id][arg]);
}

typedef struct
{
	int expression;
	char* comp1;
	char* comp2;
} componentExpressionDef_t;

componentExpressionDef_t* componentExpressions = (componentExpressionDef_t*) 0x745FA0;