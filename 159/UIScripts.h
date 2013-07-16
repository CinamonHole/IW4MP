/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 11-7-2013
Start hour: 10:52 PM (Pacific hour)

Purpose: UI scripts modifications

*/

#include "stdafx.h"

typedef bool qboolean;

typedef void (__cdecl * UIScriptFunc_t)(char* args);
typedef void (__cdecl * UIClickHandlerFunc_t)();

typedef int (__cdecl * GetItemCount_t)();
typedef const char* (__cdecl * GetItemText_t)(int index, int column);
typedef void (__cdecl * Select_t)(int index);

struct UIScript_t
{
	char* script;
	UIScriptFunc_t function;
};

struct UIClickHandler_t
{
	int owner;
	UIClickHandlerFunc_t function;
};

struct UIFeeder_t
{
	float feeder;
	GetItemCount_t GetItemCount;
	GetItemText_t GetItemText;
	Select_t Select;
};

extern std::vector<UIClickHandler_t> UIClickHandlers;
extern std::vector<UIScript_t> UIScripts;
extern std::vector<UIFeeder_t> UIFeeders;

extern bool Int_Parse(char* p, int* i);
extern void AddUIClickHandler(int owner, UIClickHandlerFunc_t function);
extern void AddUIScript(char* script, UIScriptFunc_t function);