#include "Interfaces.h"

#include "../../Utils/Assert/Assert.h"

#define Validate(x) AssertCustom(x, std::format("H::Interfaces.Initialize() Failed to initialize {}", #x).c_str())

//MAKE_SIGNATURE(Get_SteamNetworkingUtils, "client.dll", "40 53 48 83 EC ? 48 8B D9 48 8D 15 ? ? ? ? 33 C9 FF 15 ? ? ? ? 33 C9", 0x0);

void CNullInterfaces::Initialize()
{
	/*
	const HSteamPipe hsNewPipe = I::SteamClient->CreateSteamPipe();
	Validate(hsNewPipe);

	const HSteamPipe hsNewUser = I::SteamClient->ConnectToGlobalUser(hsNewPipe);
	Validate(hsNewUser);

	I::SteamFriends = I::SteamClient->GetISteamFriends(hsNewUser, hsNewPipe, STEAMFRIENDS_INTERFACE_VERSION);
	Validate(I::SteamFriends);

	I::SteamUtils = I::SteamClient->GetISteamUtils(hsNewUser, STEAMUTILS_INTERFACE_VERSION);
	Validate(I::SteamUtils);

	I::SteamApps = I::SteamClient->GetISteamApps(hsNewUser, hsNewPipe, STEAMAPPS_INTERFACE_VERSION);
	Validate(I::SteamApps);

	I::SteamUserStats = I::SteamClient->GetISteamUserStats(hsNewUser, hsNewPipe, STEAMUSERSTATS_INTERFACE_VERSION);
	Validate(I::SteamUserStats);

	I::SteamUser = I::SteamClient->GetISteamUser(hsNewUser, hsNewPipe, STEAMUSER_INTERFACE_VERSION);
	Validate(I::SteamUser);

	S::Get_SteamNetworkingUtils.Call<ISteamNetworkingUtils*>(&I::SteamNetworkingUtils);
	Validate(I::SteamNetworkingUtils);
	*/
}