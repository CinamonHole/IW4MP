/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 11-7-2013
Start hour: 1:05 PM (Pacific hour)

Purpose: Steam_API exports

*/

#include "stdafx.h"
#include "SteamInterfaces.h"

SteamFriends005*					SteamFriendsEmu =					new SteamFriends005;
SteamMasterServerUpdater001*		SteamMasterServerUpdaterEmu =		new SteamMasterServerUpdater001;
SteamUser012*						SteamUserEmu =						new SteamUser012;
SteamNetworking003*					SteamNetworkingEmu =				new SteamNetworking003;
SteamMatchmaking007*				SteamMatchmakingEmu =				new SteamMatchmaking007;
SteamRemoteStorage002*				SteamRemoteStorageEmu =				new SteamRemoteStorage002;
SteamUtils005*						SteamUtilsEmu =						new SteamUtils005;
SteamGameServer009*					SteamGameServerEmu =				new SteamGameServer009;

extern "C"
{
	__declspec(dllexport) HSteamPipe __cdecl GetHSteamPipe()
	{
		return 0;
	}

	__declspec(dllexport) HSteamUser __cdecl GetHSteamUser()
	{
		return 0;
	}

	__declspec(dllexport) HSteamPipe __cdecl SteamAPI_GetHSteamPipe()
	{
		return 0;
	}

	__declspec(dllexport) HSteamUser __cdecl SteamAPI_GetHSteamUser()
	{
		return 0;
	}

	__declspec(dllexport) const char *__cdecl SteamAPI_GetSteamInstallPath()
	{
		return 0;
	}

	__declspec(dllexport) bool __cdecl SteamAPI_Init()
	{
		return true;
	}

	__declspec(dllexport) bool __cdecl SteamAPI_InitSafe()
	{
		return true;
	}

	__declspec(dllexport) char __cdecl SteamAPI_RestartApp()
	{
		return 1;
	}

	__declspec(dllexport) char __cdecl SteamAPI_RestartAppIfNecessary()
	{
		return 0;
	}

	__declspec(dllexport) void __cdecl SteamAPI_RegisterCallResult(CCallbackBase* pResult, SteamAPICall_t APICall)
	{

	}

	__declspec(dllexport) void __cdecl SteamAPI_RegisterCallback(CCallbackBase *pCallback, int iCallback)
	{

	}

	static bool didRichPresence = false;

	__declspec(dllexport) void __cdecl SteamAPI_RunCallbacks()
	{
		
	}
	__declspec(dllexport) void __cdecl SteamAPI_SetMiniDumpComment(const char *pchMsg)
	{

	}

	__declspec(dllexport) bool __cdecl SteamAPI_SetTryCatchCallbacks(bool bUnknown)
	{
		return bUnknown;
	}

	__declspec(dllexport) void __cdecl SteamAPI_Shutdown()
	{

	}

	__declspec(dllexport) void __cdecl SteamAPI_UnregisterCallResult(CCallbackBase* pResult, SteamAPICall_t APICall)
	{

	}
	__declspec(dllexport) void __cdecl SteamAPI_UnregisterCallback(CCallbackBase *pCallback, int iCallback)
	{

	}

	__declspec(dllexport) void __cdecl SteamAPI_WriteMiniDump(uint32 uStructuredExceptionCode, void* pvExceptionInfo, uint32 uBuildID)
	{

	}

	__declspec(dllexport) void* __cdecl SteamApps()
	{
		return 0;
	}

	__declspec(dllexport) void* __cdecl SteamClient()
	{
		return 0;
	}

	__declspec(dllexport) void* __cdecl SteamContentServer()
	{
		return 0;
	}

	__declspec(dllexport) void* __cdecl SteamContentServerUtils()
	{
		return 0;
	}

	__declspec(dllexport) bool __cdecl SteamContentServer_Init(unsigned int uLocalIP, unsigned short usPort)
	{
		return 0;
	}

	__declspec(dllexport) void __cdecl SteamContentServer_RunCallbacks()
	{

	}

	__declspec(dllexport) void __cdecl SteamContentServer_Shutdown()
	{

	}

	__declspec(dllexport) void* __cdecl SteamFriends()
	{
		return SteamFriendsEmu;
	}

	__declspec(dllexport) void* __cdecl SteamGameServer()
	{
		return SteamGameServerEmu;
	}

	__declspec(dllexport) void* __cdecl SteamGameServerUtils()
	{
		return 0;
	}

	__declspec(dllexport) bool __cdecl SteamGameServer_BSecure()
	{
		return true;
	}

	__declspec(dllexport) HSteamPipe __cdecl SteamGameServer_GetHSteamPipe()
	{
		return 0;
	}

	__declspec(dllexport) HSteamUser __cdecl SteamGameServer_GetHSteamUser()
	{
		return 0;
	}

	__declspec(dllexport) int32 __cdecl SteamGameServer_GetIPCCallCount()
	{
		return 0;
	}

	__declspec(dllexport) uint64 __cdecl SteamGameServer_GetSteamID()
	{
		return 0;
	}

	__declspec(dllexport) bool __cdecl SteamGameServer_Init(uint32 unIP, uint16 usPort, uint16 usGamePort, EServerMode eServerMode, int nGameAppId, const char *pchGameDir, const char *pchVersionString)
	{
		return true;
	}

	__declspec(dllexport) bool __cdecl SteamGameServer_InitSafe(uint32 unIP, uint16 usPort, uint16 usGamePort, EServerMode eServerMode, int nGameAppId, const char *pchGameDir, const char *pchVersionString, unsigned long dongs)
	{
		return true;
	}

	__declspec(dllexport) void __cdecl SteamGameServer_RunCallbacks()
	{

	}

	__declspec(dllexport) void __cdecl SteamGameServer_Shutdown()
	{

	}

	__declspec(dllexport) void* __cdecl SteamMasterServerUpdater()
	{
		return SteamMasterServerUpdaterEmu;
	}

	__declspec(dllexport) void* __cdecl SteamMatchmaking()
	{
		return SteamMatchmakingEmu;
	}

	__declspec(dllexport) void* __cdecl SteamMatchmakingServers()
	{
		return 0;
	}

	__declspec(dllexport) void* __cdecl SteamNetworking()
	{
		return SteamNetworkingEmu;
	}

	__declspec(dllexport) void* __cdecl SteamRemoteStorage()
	{
		return SteamRemoteStorageEmu;
	}

	__declspec(dllexport) void* __cdecl SteamUser()
	{
		return SteamUserEmu;
	}

	__declspec(dllexport) void* __cdecl SteamUserStats()
	{
		return 0;
	}

	__declspec(dllexport) void* __cdecl SteamUtils()
	{
		return SteamUtilsEmu;
	}

	__declspec(dllexport) HSteamUser __cdecl Steam_GetHSteamUserCurrent()
	{
		return 0;
	}

	__declspec(dllexport) void __cdecl Steam_RegisterInterfaceFuncs(void *hModule)
	{

	}

	__declspec(dllexport) void __cdecl Steam_RunCallbacks(HSteamPipe hSteamPipe, bool bGameServerCallbacks)
	{

	}

	__declspec(dllexport) void *g_pSteamClientGameServer = 0;
}