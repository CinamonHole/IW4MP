/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 11-7-2013
Start hour: 10:47 PM (Pacific hour)

Purpose: UI scripts modifications

*/

#include "stdafx.h"
#include "Hooking.h"
#include "GamePatches.h"
#include "UIScripts.h"

std::vector<UIFeeder_t> UIFeeders;
std::vector<UIFeeder_t>::iterator it_feed;
std::vector<UIScript_t> UIScripts;
std::vector<UIScript_t>::iterator it_script;
std::vector<UIClickHandler_t> UIClickHandlers;
std::vector<UIClickHandler_t>::iterator it_clck;

StompHook uiFeederCountHook;
DWORD uiFeederCountHookLoc = 0x41A0D0;
DWORD uiFeederCountHookRet = 0x41A0D7;

StompHook uiFeederItemTextHook;
DWORD uiFeederItemTextHookLoc = 0x4CE9E0;
DWORD uiFeederItemTextHookRet = 0x4CE9E7;

float currentFeeder;
bool activeFeeder;

float fl737C28 = 4.0f;

char* uiS_name;
char* uiS_args;
DWORD uiS_continue = 0x45ED00;

bool Int_Parse(char* p, int* i)
{
	char* token;
	//token = Com_ParseExt(p);
	token = "1";

	if (token && token[0] != 0)
	{
		*i = atoi(token);
		return true;
	}

	return false;
}

int UIFeederCountHookFunc()
{
	for (it_feed = UIFeeders.begin(); it_feed < UIFeeders.end(); it_feed++)
	{
		if (it_feed->feeder == currentFeeder)
		{
			return it_feed->GetItemCount();
		}
	}

	return 0;
}

void __declspec(naked) UIFeederCountHookStub()
{
	__asm
	{
		mov eax, [esp + 8h]
			mov currentFeeder, eax
			call UIFeederCountHookFunc
			test eax, eax
			jz continueRunning
			retn

		continueRunning :
		push ecx
			fld fl737C28
			jmp uiFeederCountHookRet;
	}

}

int index;
int column;

const char* UIFeederItemTextHookFunc()
{
	for (it_feed = UIFeeders.begin(); it_feed < UIFeeders.end(); it_feed++)
	{
		if (it_feed->feeder == currentFeeder)
		{
			return it_feed->GetItemText(index, column);
		}
	}

	return 0;
}

void __declspec(naked) UIFeederItemTextHookStub()
{
	__asm
	{
		mov eax, [esp + 0Ch]
			mov currentFeeder, eax
			mov eax, [esp + 10h]
			mov index, eax
			mov eax, [esp + 14h]
			mov column, eax
			call UIFeederItemTextHookFunc
			test eax, eax
			jz continueRunning
			push ebx
			mov ebx, [esp + 4 + 28h]
			mov dword ptr[ebx], 0
			pop ebx
			retn

		continueRunning :
		push ecx
			fld fl737C28
			jmp uiFeederItemTextHookRet
	}

}
StompHook uiFeederSelectionHook;
DWORD uiFeederSelectionHookLoc = 0x4C25D0;
DWORD uiFeederSelectionHookRet = 0x4C25D6;


bool UIFeederSelectionHookFunc()
{
	std::vector<UIFeeder_t>::iterator it;

	for (it = UIFeeders.begin(); it < UIFeeders.end(); it++)
	{
		if (it->feeder == currentFeeder)
		{
			it->Select(index);
			return true;
		}
	}
	return false;
}

void __declspec(naked) UIFeederSelectionHookStub()
{
	__asm
	{
		mov eax, [esp + 08h]
			mov currentFeeder, eax
			mov eax, [esp + 0Ch]
			mov index, eax
			call UIFeederSelectionHookFunc
			test eax, eax
			jz continueRunning
			retn

		continueRunning :
		fld fl737C28
			jmp uiFeederSelectionHookRet
	}

}

StompHook mouseEnterHook;
DWORD mouseEnterHookLoc = 0x639D6E;
DWORD mouseEnterHookRet = 0x639D75;
void MouseEnterHookFunc()
{
	activeFeeder = false;

	if (currentFeeder == 15.0f)
	{
		return;
	}

	for (it_feed = UIFeeders.begin(); it_feed < UIFeeders.end(); it_feed++)
	{
		if (it_feed->feeder == currentFeeder)
		{
			activeFeeder = true;
			break;
		}
	}
}
void __declspec(naked) MouseEnterHookStub()
{
	__asm
	{
		mov eax, [edi + 12Ch]
			mov currentFeeder, eax
	}

	MouseEnterHookFunc();


	if (!activeFeeder)
	{
		__asm
		{
			mov[edi + 130h], esi
		}
	}

	__asm
	{
		jmp mouseEnterHookRet
	}
}

typedef struct columnInfo_s
{
	int pos;
	int width;
	int maxChars;
	int unknown;
} columnInfo_t;

typedef struct
{
	void* data;
	int type;
} menuStatement_t;

typedef struct
{
	int numStatements;
	menuStatement_t** statements;
} menuScript_t;

typedef struct listBoxDef_s
{
	int cursorPos;
	int unk;
	int startPos;
	int endPos;
	float elementWidth;
	float elementHeight;
	int elementStyle;
	int numColumns;
	columnInfo_t columnInfo[16];
	menuScript_t* doubleClick;
	int notselectable;
	int noscrollbars;
	int usepaging;
} listBoxDef_t;

typedef float vec4_t[4];

typedef struct
{
	char* name;
	vec4_t rect;
	char rectAlignX;
	char rectAlignY;
	// 22
	char pad[2];
	// 24
	float originX;
	float originY;
	// 32
	char pad2[12];
	// 44
	char* group;
	// 48
	int style;
	int border;
	int ownerDraw;
	int ownerDrawFlags;
	float borderSize;
	// 68
	int flags1;
	int flags2;
	int unknown1;
	// 80
	vec4_t foreColor;
	vec4_t backColor;
	vec4_t borderColor;
	vec4_t outlineColor;
	// 144
	vec4_t unknownColor;
	// 160
	//Material* background;
} windowDef_t;

typedef windowDef_t Window;

typedef struct execKey_s
{
	union
	{
		char key[4];
		int keyInt;
	};
	menuScript_t* script;
	execKey_s* next;
} execKey_t;

typedef struct
{
	int type;
	int id;
	void* extraData;
} menuExpToken_t;

typedef struct
{
	int count;
	menuExpToken_t* tokens;
} menuExpression_t;

typedef struct
{
	int type;
	menuExpression_t* expression;
} componentExpression_t;

typedef struct
{
	Window window;
	// 164
	char pad1[20];
	// 184
	int type;
	int unknownType;
	int align;
	int textFont;
	int textAlign;
	float textAlignX;
	float textAlignY;
	float textScale;
	int textStyle;
	int unknown;
	int unknown2;
	char* text;
	int unknown3;
	int unknown4;
	menuScript_t* mouseEnterText;
	menuScript_t* mouseExitText;
	menuScript_t* mouseEnter;
	menuScript_t* mouseExit;
	menuScript_t* action;
	menuScript_t* accept;
	menuScript_t* onFocus;
	menuScript_t* leaveFocus;
	char* dvar;
	char* dvarTest;
	execKey_t* execKeys;
	void* testDvarValue;
	char* localVar;
	int testDvarType;
	char** focusSound;
	float feeder;
	int cursorPos;
	void* typeData;
	char pad2[4];
	int numExpressions;
	componentExpression_t* expressions;
	menuExpression_t* visibleExp;
	menuExpression_t* disabledExp;
	menuExpression_t* textExp;
	menuExpression_t* materialExp;
} itemDef_t;

CallHook handleKeyHook;
DWORD handleKeyHookLoc = 0x63C5BC;

DWORD lastListBoxClickTime;
listBoxDef_t* listPtr;

static itemDef_t* item;

void __declspec(naked) HandleKeyHookStub()
{
	__asm
	{
		mov item, ebp
			mov eax, [ebp + 12Ch]
			mov currentFeeder, eax
	}

	activeFeeder = false;
	for (it_feed = UIFeeders.begin(); it_feed < UIFeeders.end(); it_feed++)
	{
		if (it_feed->feeder == currentFeeder)
		{
			activeFeeder = true;
			break;
		}
	}
	if (!activeFeeder || currentFeeder == 15.0f)
	{
		__asm jmp handleKeyHook.pOriginal
	}

	/*if (Com_Milliseconds() < (int) lastListBoxClickTime)
	{
		__asm
		{
			jmp handleKeyHook.pOriginal
		}
	}*/

	//lastListBoxClickTime = Com_Milliseconds() + 300;

	listPtr = (listBoxDef_t*) item->typeData;

	if (item->cursorPos != listPtr->cursorPos)
	{
		item->cursorPos = listPtr->cursorPos;
		index = item->cursorPos;

		UIFeederSelectionHookFunc();
	}

	__asm
	{
		retn
	}
}

CallHook selectOnMouseHook;
DWORD selectOnMouseHookLoc = 0x639D31;

void SelectOnMouseHookFunc()
{
	activeFeeder = false;

	if (currentFeeder == 15.0f)
	{
		return;
	}

	for (it_feed = UIFeeders.begin(); it_feed < UIFeeders.end(); it_feed++)
	{
		if (it_feed->feeder == currentFeeder)
		{
			activeFeeder = true;
			break;
		}
	}
}
void __declspec(naked) SelectOnMouseHookStub()
{
	__asm
	{
		mov eax, [esp + 08h]
			mov currentFeeder, eax
	}

	SelectOnMouseHookFunc();

	if (!activeFeeder)
	{
		__asm jmp selectOnMouseHook.pOriginal
	}

	__asm
	{
		retn
	}
}

CallHook playSoundOnMouseHook;
DWORD playSoundOnMouseHookLoc = 0x639D66;

void __declspec(naked) PlaySoundOnMouseHookStub()
{
	__asm
	{
		mov eax, [edi + 12Ch]
			mov currentFeeder, eax
	}

	SelectOnMouseHookFunc();

	if (!activeFeeder)
	{
		__asm jmp playSoundOnMouseHook.pOriginal
	}

	__asm
	{
		retn
	}
}

CallHook uiOwnerDrawHandleKeyHook;
DWORD uiOwnerDrawHandleKeyHookLoc = 0x63D233;

void UI_OwnerDrawHandleKey(int ownerDraw, int a2, int a3, int key)
{
	if (key == 200 || key == 201) //mouse buttons
	{
		for (it_clck = UIClickHandlers.begin(); it_clck < UIClickHandlers.end(); it_clck++)
		{
			if (it_clck->function && it_clck->owner == ownerDraw)
			{
				it_clck->function();
			}
		}
	}
}

void __declspec(naked) UI_OwnerDrawHandleKeyHookStub()
{
	__asm
	{
		push ebp
			push ecx
			push edx
			push eax
			call UI_OwnerDrawHandleKey
			add esp, 10h

			jmp uiOwnerDrawHandleKeyHook.pOriginal
	}
}

// returns true if handled, and false if not
bool UI_RunMenuScriptFunc()
{
	bool handled = false;
	for (it_script = UIScripts.begin(); it_script < UIScripts.end(); it_script++)
	{
		if (it_script->function && !_stricmp(it_script->script, uiS_name))
		{
			it_script->function(uiS_args);
			handled = true;
		}
	}
	return handled;
}

void __declspec(naked) UI_RunMenuScriptStub()
{
	__asm
	{
		mov eax, esp
			add eax, 8h
			mov uiS_name, eax
			mov eax, [esp + 0C10h]
			mov uiS_args, eax
			call UI_RunMenuScriptFunc
			test eax, eax
			jz continue_uis

			// if returned
			pop edi
			pop esi
			add esp, 0C00h
			retn

		continue_uis :
		jmp uiS_continue
	}
}

void AddUIClickHandler(int owner, UIClickHandlerFunc_t function)
{
	UIClickHandler_t h;
	h.owner = owner;
	h.function = function;
	UIClickHandlers.push_back(h);
}

void AddUIScript(char* script, UIScriptFunc_t function)
{
	UIScript_t h;
	h.script = script;
	h.function = function;
	UIScripts.push_back(h);
}

void GamePatches::UIScripts()
{
	uiFeederCountHook.initialize(uiFeederCountHookLoc, UIFeederCountHookStub, 7);
	uiFeederCountHook.installHook();

	uiFeederItemTextHook.initialize(uiFeederItemTextHookLoc, UIFeederItemTextHookStub, 7);
	uiFeederItemTextHook.installHook();

	uiFeederSelectionHook.initialize(uiFeederSelectionHookLoc, UIFeederSelectionHookStub, 6);
	uiFeederSelectionHook.installHook();

	mouseEnterHook.initialize(mouseEnterHookLoc, MouseEnterHookStub, 7);
	mouseEnterHook.installHook();

	handleKeyHook.initialize(handleKeyHookLoc, HandleKeyHookStub);
	handleKeyHook.installHook();

	selectOnMouseHook.initialize(selectOnMouseHookLoc, SelectOnMouseHookStub);
	selectOnMouseHook.installHook();

	playSoundOnMouseHook.initialize(playSoundOnMouseHookLoc, PlaySoundOnMouseHookStub);
	playSoundOnMouseHook.installHook();

	uiOwnerDrawHandleKeyHook.initialize(uiOwnerDrawHandleKeyHookLoc, UI_OwnerDrawHandleKeyHookStub);
	uiOwnerDrawHandleKeyHook.installHook();

	// some thing overwriting feeder 2's data
	*(BYTE*) 0x4A06A9 = 0xEB;

	// ui script stuff
	*(int*) 0x45EC5B = ((DWORD) UI_RunMenuScriptStub) - 0x45EC59 - 6;
}