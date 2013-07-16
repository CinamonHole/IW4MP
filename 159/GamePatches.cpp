/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 11-7-2013
Start hour: 7:00 PM (Pacific hour)

Purpose: Small patches

*/

#include "stdafx.h"
#include "GamePatches.h"

void GamePatches::Init()
{
	if (!strcmp((char*) 0x6E9638, "177"))
	{
		// Multiplayer detected, lets start game patches for it
		GamePatches::Multiplayer();
	}
	else
	{
		MessageBox(0, TEXT("You are trying to run the game with a different EXE. Re-updating the client should solve this problem."), "Error", MB_OK | MB_ICONHAND);
		ExitProcess(0xDEAD);
	}
}

void GamePatches::Multiplayer()
{
	// Unlock the game memory
	DWORD oldp;
	VirtualProtect((void*)0x401000, 0x400000, 0x40, &oldp);

	// Changes game/console's window title
	strcpy((char*) 0x786038, "dNZ Multiplayer");
	strcpy((char*) 0x6DDBE4, "dNZ Console");

	// Unlock the developer console
	memset((void*) 0x60BB58, 0x90, 11);

	// Master server stuff
	strcpy((char*) 0x6D9CBC, "84.91.237.93");		// 'cod4master.activision.com'
	strcpy((char*) 0x6E3C18, "84.91.237.93");		// 'match1.pc.iw4.iwnet.infinityward.com'
	strcpy((char*) 0x6FA098, "84.91.237.93");		// 'auth1.pc.iw4.iwnet.infinityward.com'
	strcpy((char*) 0x6FD3DC, "84.91.237.93");		// 'blob1.pc.iw4.iwnet.infinityward.com'
	strcpy((char*) 0x70AC68, "84.91.237.93");		// 'log1.pc.iw4.iwnet.infinityward.com'
	strcpy((char*) 0x733B58, "84.91.237.93");		// 'ip1.pc.iw4.iwnet.infinityward.com'

	// Close that black console
	FreeConsole();

	// 'FS_Startup' string
	strcpy((char*) 0x6F677C, "Welcome to dNZ!");

	// Bottom-right corner version string
	strcpy((char*) 0x6FEDB0, "dNZ ^31.0-019");

	// Set fs_basegame to 'm2demo'
	//*(DWORD*) 0x6431D1 = (DWORD)"m2demo";	// Causes '3_cursor3' error

	// Other patches
	GamePatches::AssetRestriction();	// Fix for 'asset' errors
}

bool __stdcall DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		GamePatches::Init();
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	return true;
}