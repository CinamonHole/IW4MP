/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 12-7-2013
Start hour: 5:25 PM (Pacific hour)

Purpose: Branding text in the corner.

*/

#include "stdafx.h"
#include "Hooking.h"
#include "GamePatches.h"

typedef void* (__cdecl * R_RegisterFont_t)(const char* asset);
R_RegisterFont_t R_RegisterFont = (R_RegisterFont_t) 0x505670;

typedef void (__cdecl * R_AddCmdDrawText_t)(const char* text, int, void* font, float screenX, float screenY, float, float, float rotation, float* color, int);
R_AddCmdDrawText_t R_AddCmdDrawText = (R_AddCmdDrawText_t) 0x509D80;

CallHook drawDevStuffHook;
DWORD drawDevStuffHookLoc = 0x5ACB99;

void DrawBrandingText()
{
	void* font = R_RegisterFont("fonts/objectivefont");
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	R_AddCmdDrawText("PREVIEW", 0x7FFFFFFF, font, 10, 30, 0.7f, 0.7f, 0.0f, color, 0);
}

void __declspec(naked) DrawDevStuffHookStub()
{
	__asm
	{
		call DrawBrandingText
		jmp drawDevStuffHook.pOriginal
	}
}

void GamePatches::Branding()
{
	drawDevStuffHook.initialize(drawDevStuffHookLoc, DrawDevStuffHookStub);
	drawDevStuffHook.installHook();
}