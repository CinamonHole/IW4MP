/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 10-7-2013
Start hour: 10:13 PM (Pacific hour)

Purpose: Hooking stuff from aIW.

*/

#include "stdafx.h"

#pragma once

#define CALL_NEAR32 0xE8U
#define JMP_NEAR32 0xE9U
#define NOP 0x90U

struct CallHook 
{
	BYTE bOriginalCode[5];
	PBYTE pPlace;
	void* pOriginal;
	void* hook;

	void initialize(DWORD place, void *hookToInstall = NULL);
	void installHook(void* hookToInstall = NULL);
	void releaseHook();
};

struct StompHook 
{
	BYTE bOriginalCode[15];
	BYTE bCountBytes;
	PBYTE pPlace;
	void* hook;
	bool jump;

	void initialize(DWORD place, void *hookToInstall = NULL, BYTE countBytes = 5, bool useJump = true);
	void installHook(void* hookToInstall = NULL);
	void releaseHook();
};

void HookInstall(DWORD address, DWORD hookToInstall, int bCountBytes = 5);

enum eCallPatcher
{
	PATCH_CALL,
	PATCH_JUMP,
	PATCH_NOTHING
};

void _patch(void* pAddress, DWORD data, DWORD iSize);
void _nop(void* pAddress, DWORD size);
void _call(void* pAddress, DWORD data, eCallPatcher bPatchType);

#define patch(a, v, s) _patch((void*)(a), (DWORD)(v), (s))
#define nop(a, v) _nop((void*)(a), (v))
#define call(a, v, bAddCall) _call((void*)(a), (DWORD)(v), (bAddCall))