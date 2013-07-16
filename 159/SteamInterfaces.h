/*

Project: MW2Client
Game: COD MW2
Version: 1.0.159

Start date: 11-7-2013
Start hour: 12:34 PM (Pacific hour)

Purpose: Definitions of all steam interfaces needed.

*/

#include "stdafx.h"

unsigned int hSteamID = 1337;

unsigned int StringHash(char* key, size_t len)
{
	unsigned int hash, i;

	for (hash = i = 0; i < len; ++i)
	{
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash;
}

unsigned int GetPlayerSteamID()
{
	if (hSteamID)
	{
		return hSteamID;
	}

	//char* serial = GetHardwareSerialNumber();
	//hSteamID = StringHash(serial, strlen(serial));
	
	return hSteamID;
}

class SteamFriends005 : public ISteamFriends005
{
	const char *GetPersonaName()
	{
		return "Convery's boyfriend";
	}

	void SetPersonaName(const char *pchPersonaName)
	{

	}

	EPersonaState GetPersonaState()
	{
		return k_EPersonaStateOnline;
	}

	int GetFriendCount(EFriendFlags eFriendFlags)
	{
		return 0;
	}

	CSteamID GetFriendByIndex(int iFriend, int iFriendFlags)
	{
		return CSteamID();
	}

	EFriendRelationship GetFriendRelationship(CSteamID steamIDFriend)
	{
		return k_EFriendRelationshipNone;
	}

	EPersonaState GetFriendPersonaState(CSteamID steamIDFriend)
	{
		return k_EPersonaStateOffline;
	}

	const char *GetFriendPersonaName(CSteamID steamIDFriend)
	{
		return "UnnamedFriend";
	}

	int GetFriendAvatar(CSteamID steamIDFriend, int eAvatarSize)
	{
		return 0;
	}

	bool GetFriendGamePlayed(CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo)
	{
		return false;
	}

	const char *GetFriendPersonaNameHistory(CSteamID steamIDFriend, int iPersonaName)
	{
		return "UnnamedFriend";
	}

	bool HasFriend(CSteamID steamIDFriend, EFriendFlags eFriendFlags)
	{
		return false;
	}

	int GetClanCount()
	{
		return 0;
	}

	CSteamID GetClanByIndex(int iClan)
	{
		return CSteamID();
	}

	const char *GetClanName(CSteamID steamIDClan)
	{
		return "dNZ";
	}

	int GetFriendCountFromSource(CSteamID steamIDSource)
	{
		return 0;
	}

	CSteamID GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend )
	{
		return CSteamID();
	}

	bool IsUserInSource(CSteamID steamIDUser, CSteamID steamIDSource)
	{
		return false;
	}

	void SetInGameVoiceSpeaking(CSteamID steamIDUser, bool bSpeaking)
	{
		
	}

	void ActivateGameOverlay(const char *pchDialog)
	{

	}

	void ActivateGameOverlayToUser(const char *pchDialog, CSteamID steamID)
	{

	}

	void ActivateGameOverlayToWebPage(const char *pchURL)
	{

	}

	void ActivateGameOverlayToStore(AppId_t nAppID)
	{

	}

	void SetPlayedWith(CSteamID steamIDUserPlayedWith)
	{

	}
};

class SteamUser012 : public ISteamUser012
{
	HSteamUser GetHSteamUser()
	{
		return 0;
	}

	bool LoggedOn()
	{
		return true;
	}

	CSteamID GetSteamID()
	{
		return CSteamID(1254351, 0x40000, k_EUniversePublic, k_EAccountTypeAnonUser);
	}

	int InitiateGameConnection(void *pAuthBlob, int cbMaxAuthBlob, CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer, bool bSecure)
	{
		return 0;
	}

	void TerminateGameConnection(uint32 unIPServer, uint16 usPortServer)
	{

	}

	void TrackAppUsageEvent(CGameID gameID, EAppUsageEvent eAppUsageEvent, const char *pchExtraInfo)
	{

	}

	bool GetUserDataFolder(char *pchBuffer, int cubBuffer)
	{
		return false;
	}

	void StartVoiceRecording()
	{

	}

	void StopVoiceRecording()
	{

	}

	EVoiceResult GetCompressedVoice(void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten)
	{
		return k_EVoiceResultOK;
	}

	EVoiceResult DecompressVoice(void *pCompressed, uint32 cbCompressed, void *pDestBuffer, uint32 cbDestBufferSize, uint32 *nBytesWritten)
	{
		return k_EVoiceResultOK;
	}

	HAuthTicket GetAuthSessionTicket(void *pTicket, int cbMaxTicket, uint32 *pcbTicket)
	{
		return 0;
	}

	EBeginAuthSessionResult BeginAuthSession(const void *pAuthTicket, int cbAuthTicket, CSteamID steamID)
	{
		return k_EBeginAuthSessionResultOK;
	}

	void EndAuthSession(CSteamID steamID)
	{

	}

	void CancelAuthTicket(HAuthTicket hAuthTicket)
	{

	}

	uint32 UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
	{
		return k_EUserHasLicenseResultHasLicense;
	}
};

class SteamGameServer009 : public ISteamGameServer009
{
	void LogOn()
	{

	}

	void LogOff()
	{

	}

	bool LoggedOn()
	{
		return true;
	}

	bool Secure()
	{
		return true;
	}

	CSteamID GetSteamID()
	{
		return CSteamID(929824, 0x40000, k_EUniversePublic, k_EAccountTypeAnonGameServer);
	}

	bool SendUserConnectAndAuthenticate(uint32 unIPClient, const void *pvAuthBlob, uint32 cubAuthBlobSize, CSteamID *pSteamIDUser)
	{
		return false;
	}

	CSteamID CreateUnauthenticatedUserConnection()
	{
		return CSteamID(929824, 0x40000, k_EUniversePublic, k_EAccountTypeAnonGameServer);
	}

	void SendUserDisconnect(CSteamID steamIDUser)
	{

	}

	bool UpdateUserData(CSteamID steamIDUser, const char *pchPlayerName, uint32 uScore)
	{
		return false;
	}

	bool SetServerType(uint32 unServerFlags, uint32 unGameIP, uint16 unGamePort, uint16 unSpectatorPort, uint16 usQueryPort, const char *pchGameDir, const char *pchVersion, bool bLANMode)
	{
		return false;
	}

	void UpdateServerStatus(int cPlayers, int cPlayersMax, int cBotPlayers, const char *pchServerName, const char *pSpectatorServerName, const char *pchMapName)
	{

	}

	void UpdateSpectatorPort(uint16 unSpectatorPort)
	{

	}

	void SetGameType(const char *pchGameType)
	{

	}

	bool GetUserAchievementStatus(CSteamID steamID, const char *pchAchievementName)
	{
		return false;
	}

	void GetGameplayStats()
	{

	}

	bool RequestUserGroupStatus(CSteamID steamIDUser, CSteamID steamIDGroup)
	{
		return false;
	}

	uint32 GetPublicIP()
	{
		return 0;
	}

	void SetGameData(const char *pchGameData)
	{

	}

	EUserHasLicenseForAppResult UserHasLicenseForApp(CSteamID steamID, AppId_t appID)
	{
		return k_EUserHasLicenseResultHasLicense;
	}
};

class SteamNetworking003 : public ISteamNetworking003
{
	bool SendP2PPacket(CSteamID steamIDRemote, const void *pubData, uint32 cubData, EP2PSend eP2PSendType)
	{
		return false;
	}

	bool IsP2PPacketAvailable(uint32 *pcubMsgSize)
	{
		return false;
	}

	bool ReadP2PPacket(void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, CSteamID *psteamIDRemote)
	{
		return false;
	}

	bool AcceptP2PSessionWithUser(CSteamID steamIDRemote)
	{
		return false;
	}

	bool CloseP2PSessionWithUser(CSteamID steamIDRemote)
	{
		return false;
	}

	bool GetP2PSessionState(CSteamID steamIDRemote, P2PSessionState_t *pConnectionState)
	{
		return false;
	}

	SNetListenSocket_t CreateListenSocket(int nVirtualP2PPort, uint32 nIP, uint16 nPort, bool bAllowUseOfPacketRelay)
	{
		return 0;
	}

	SNetSocket_t CreateP2PConnectionSocket(CSteamID steamIDTarget, int nVirtualPort, int nTimeoutSec, bool bAllowUseOfPacketRelay)
	{
		return 0;
	}

	SNetSocket_t CreateConnectionSocket(uint32 nIP, uint16 nPort, int nTimeoutSec)
	{
		return 0;
	}

	bool DestroySocket(SNetSocket_t hSocket, bool bNotifyRemoteEnd)
	{
		return false;
	}

	bool DestroyListenSocket(SNetListenSocket_t hSocket, bool bNotifyRemoteEnd)
	{
		return false;
	}

	bool SendDataOnSocket(SNetSocket_t hSocket, void *pubData, uint32 cubData, bool bReliable)
	{
		return false;
	}

	bool IsDataAvailableOnSocket(SNetSocket_t hSocket, uint32 *pcubMsgSize)
	{
		return false;
	}

	bool RetrieveDataFromSocket(SNetSocket_t hSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize)
	{
		return false;
	}

	bool IsDataAvailable(SNetListenSocket_t hListenSocket, uint32 *pcubMsgSize, SNetSocket_t *phSocket)
	{
		return false;
	}

	bool RetrieveData(SNetListenSocket_t hListenSocket, void *pubDest, uint32 cubDest, uint32 *pcubMsgSize, SNetSocket_t *phSocket)
	{
		return false;
	}

	bool GetSocketInfo(SNetSocket_t hSocket, CSteamID *pSteamIDRemote, int *peSocketStatus, uint32 *punIPRemote, uint16 *punPortRemote)
	{
		return false;
	}

	bool GetListenSocketInfo(SNetListenSocket_t hListenSocket, uint32 *pnIP, uint16 *pnPort)
	{
		return false;
	}

	ESNetSocketConnectionType GetSocketConnectionType(SNetSocket_t hSocket)
	{
		return k_ESNetSocketConnectionTypeUDP;
	}

	int GetMaxPacketSize(SNetSocket_t hSocket)
	{
		return 0;
	}
};

class SteamMatchmaking007 : public ISteamMatchmaking007
{
	int GetFavoriteGameCount()
	{
		return 0;
	}

	bool GetFavoriteGame(int iGame, AppId_t *pnAppID, uint32 *pnIP, uint16 *pnConnPort, uint16 *pnQueryPort, uint32 *punFlags, uint32 *pRTime32LastPlayedOnServer)
	{
		return false;
	}

	int AddFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags, uint32 rTime32LastPlayedOnServer)
	{
		return 0;
	}

	bool RemoveFavoriteGame(AppId_t nAppID, uint32 nIP, uint16 nConnPort, uint16 nQueryPort, uint32 unFlags)
	{
		return false;
	}

	SteamAPICall_t RequestLobbyList()
	{
		return 0;
	}

	void AddRequestLobbyListStringFilter(const char *pchKeyToMatch, const char *pchValueToMatch, ELobbyComparison eComparisonType)
	{

	}

	void AddRequestLobbyListNumericalFilter(const char *pchKeyToMatch, int nValueToMatch, ELobbyComparison eComparisonType)
	{

	}

	void AddRequestLobbyListNearValueFilter(const char *pchKeyToMatch, int nValueToBeCloseTo)
	{

	}

	void AddRequestLobbyListFilterSlotsAvailable(int nSlotsAvailable)
	{

	}
	
	CSteamID GetLobbyByIndex(int iLobby)
	{
		return CSteamID();
	}

	SteamAPICall_t CreateLobby(ELobbyType eLobbyType, int cMaxMembers)
	{
		return 0;
	}

	SteamAPICall_t JoinLobby(CSteamID steamIDLobby)
	{
		return 0;
	}

	void LeaveLobby(CSteamID steamIDLobby)
	{

	}

	bool InviteUserToLobby(CSteamID steamIDLobby, CSteamID steamIDInvitee)
	{
		return false;
	}

	int GetNumLobbyMembers(CSteamID steamIDLobby)
	{
		return 0;
	}
	
	CSteamID GetLobbyMemberByIndex(CSteamID steamIDLobby, int iMember)
	{
		return CSteamID();
	}

	const char *GetLobbyData(CSteamID steamIDLobby, const char *pchKey)
	{
		return "";
	}

	bool SetLobbyData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue)
	{
		return false;
	}

	int GetLobbyDataCount(CSteamID steamIDLobby)
	{
		return 0;
	}

	bool GetLobbyDataByIndex(CSteamID steamIDLobby, int iLobbyData, char *pchKey, int cchKeyBufferSize, char *pchValue, int cchValueBufferSize)
	{
		return false;
	}

	bool DeleteLobbyData(CSteamID steamIDLobby, const char *pchKey)
	{
		return false;
	}

	const char *GetLobbyMemberData(CSteamID steamIDLobby, CSteamID steamIDUser, const char *pchKey)
	{
		return "";
	}

	void SetLobbyMemberData(CSteamID steamIDLobby, const char *pchKey, const char *pchValue)
	{

	}

	bool SendLobbyChatMsg(CSteamID steamIDLobby, const void *pvMsgBody, int cubMsgBody)
	{
		return false;
	}

	int GetLobbyChatEntry(CSteamID steamIDLobby, int iChatID, CSteamID *pSteamIDUser, void *pvData, int cubData, EChatEntryType *peChatEntryType)
	{
		return 0;
	}

	bool RequestLobbyData(CSteamID steamIDLobby)
	{
		return false;
	}

	void SetLobbyGameServer(CSteamID steamIDLobby, uint32 unGameServerIP, uint16 unGameServerPort, CSteamID steamIDGameServer)
	{

	}

	bool GetLobbyGameServer(CSteamID steamIDLobby, uint32 *punGameServerIP, uint16 *punGameServerPort, CSteamID *psteamIDGameServer)
	{
		return false;
	}

	bool SetLobbyMemberLimit(CSteamID steamIDLobby, int cMaxMembers)
	{
		return false;
	}

	int GetLobbyMemberLimit(CSteamID steamIDLobby)
	{
		return 0;
	}

	bool SetLobbyType(CSteamID steamIDLobby, ELobbyType eLobbyType)
	{
		return false;
	}

	bool SetLobbyJoinable(CSteamID steamIDLobby, bool bLobbyJoinable)
	{
		return false;
	}
	
	CSteamID GetLobbyOwner(CSteamID steamIDLobby)
	{
		return CSteamID();
	}

	bool SetLobbyOwner(CSteamID steamIDLobby, CSteamID steamIDNewOwner)
	{
		return false;
	}
};

class SteamRemoteStorage002 : public ISteamRemoteStorage002
{
	bool FileWrite(const char *pchFile, const void *pvData, int32 cubData)
	{
		return false;
	}

	int32 GetFileSize(const char *pchFile)
	{
		return 0;
	}

	int32 FileRead(const char *pchFile, void *pvData, int32 cubDataToRead)
	{
		return 0;
	}

	bool FileExists(const char *pchFile)
	{
		return false;
	}

	int32 GetFileCount()
	{
		return 0;
	}

	const char *GetFileNameAndSize(int iFile, int32 *pnFileSizeInBytes)
	{
		return "";
	}

	bool GetQuota(int32 *pnTotalBytes, int32 *puAvailableBytes)
	{
		return false;
	}
};

class SteamUtils005 : public ISteamUtils005
{
	uint32 GetSecondsSinceAppActive()
	{
		return 0;
	}

	uint32 GetSecondsSinceComputerActive()
	{
		return 0;
	}

	EUniverse GetConnectedUniverse()
	{
		return k_EUniversePublic;
	}

	uint32 GetServerRealTime()
	{
		return 0;
	}

	const char *GetIPCountry()
	{
		return "";
	}

	bool GetImageSize(int iImage, uint32 *pnWidth, uint32 *pnHeight)
	{
		return false;
	}

	bool GetImageRGBA(int iImage, uint8 *pubDest, int nDestBufferSize)
	{
		return false;
	}

	bool GetCSERIPPort(uint32 *unIP, uint16 *usPort)
	{
		return false;
	}

	uint8 GetCurrentBatteryPower()
	{
		return 255;
	}

	uint32 GetAppID()
	{
		return 10190;
	}

	void SetOverlayNotificationPosition(ENotificationPosition eNotificationPosition)
	{

	}

	bool IsAPICallCompleted(SteamAPICall_t hSteamAPICall, bool *pbFailed)
	{
		return false;
	}

	ESteamAPICallFailure GetAPICallFailureReason(SteamAPICall_t hSteamAPICall)
	{
		return k_ESteamAPICallFailureNone;
	}

	bool GetAPICallResult(SteamAPICall_t hSteamAPICall, void *pCallback, int cubCallback, int iCallbackExpected, bool *pbFailed)
	{
		return false;
	}

	void RunFrame()
	{

	}

	uint32 GetIPCCallCount()
	{
		return 0;
	}

	void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction)
	{

	}

	bool IsOverlayEnabled()
	{
		return false;
	}

	bool BOverlayNeedsPresent()
	{
		return false;
	}

	SteamAPICall_t CheckFileSignature(const char *szFileName)
	{
		return 0;
	}

	uint32 GetEnteredGamepadTextLength()
	{
		return 0;
	}

	bool GetEnteredGamepadTextInput(char *pchValue, uint32 cchValueMax)
	{
		return false;
	}
};

class SteamMasterServerUpdater001 : public ISteamMasterServerUpdater001
{
	void SetActive(bool bActive)
	{

	}

	void SetHeartbeatInterval(int iHeartbeatInterval)
	{

	}

	bool HandleIncomingPacket(const void *pData, int cbData, uint32 srcIP, uint16 srcPort)
	{
		return false;
	}

	int GetNextOutgoingPacket(void *pOut, int cbMaxOut, uint32 *pNetAdr, uint16 *pPort)
	{
		return 0;
	}

	void SetBasicServerData(unsigned short nProtocolVersion, bool bDedicatedServer, const char *pRegionName, const char *pProductName, unsigned short nMaxReportedClients, bool bPasswordProtected, const char *pGameDescription)
	{

	}

	void ClearAllKeyValues()
	{

	}

	void SetKeyValue(const char *pKey, const char *pValue)
	{

	}

	void NotifyShutdown()
	{

	}

	bool WasRestartRequested()
	{
		return false;
	}

	void ForceHeartbeat()
	{

	}

	bool AddMasterServer(const char *pServerAddress)
	{
		return false;
	}

	bool RemoveMasterServer(const char *pServerAddress)
	{
		return false;
	}

	int GetNumMasterServers()
	{
		return 0;
	}

	int GetMasterServerAddress(int iServer, char *pOut, int outBufferSize)
	{
		return 0;
	}
};