/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 12-7-2013
Start hour: 5:57 PM (Pacific hour)

Purpose: Important news in the main menu ticker

*/

#include "stdafx.h"
#include "Hooking.h"
#include "GamePatches.h"

CallHook newsTickerGetTextHook;
DWORD newsTickerGetTextHookLoc = 0x6388C1;

char ticker[1024];

const char* NewsTicker_GetText(const char* garbage)
{
	if (!ticker[0])
	{
		strcpy(ticker, "dNZ client is still in ^1PREVIEW ^7only.");
	}

	return ticker;
}

void GamePatches::NewsTicker()
{
	// hook for getting the news ticker string
	*(WORD*) 0x6388BB = 0x9090; // skip the "if (item->text[0] == '@')" localize check

	// replace the localize function
	newsTickerGetTextHook.initialize(newsTickerGetTextHookLoc, NewsTicker_GetText);
	newsTickerGetTextHook.installHook();

	// make newsfeed (ticker) menu items not cut off based on safe area
	memset((void*) 0x63892D, 0x90, 5);
}