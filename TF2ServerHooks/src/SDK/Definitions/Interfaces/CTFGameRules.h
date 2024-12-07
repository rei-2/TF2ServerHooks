#pragma once
#include "Interface.h"
#include "../Definitions.h"
#include "../../../Utils/NetVars/NetVars.h"
#include "../../../Utils/Memory/Memory.h"

MAKE_SIGNATURE(CTFGameRules_Get, "server.dll", "48 8B 0D ? ? ? ? 49 8B D6 44 8B 4F", 0x0);

class CTeamplayRules
{
public:
};

class CTeamplayRoundBasedRules : public CTeamplayRules
{
public:
	NETVAR(m_iRoundState, int, "CTeamplayRoundBasedRulesProxy", "m_iRoundState");
	NETVAR(m_bInOvertime, bool, "CTeamplayRoundBasedRulesProxy", "m_bInOvertime");
	NETVAR(m_bInSetup, bool, "CTeamplayRoundBasedRulesProxy", "m_bInSetup");
	NETVAR(m_bSwitchedTeamsThisRound, bool, "CTeamplayRoundBasedRulesProxy", "m_bSwitchedTeamsThisRound");
	NETVAR(m_iWinningTeam, int, "CTeamplayRoundBasedRulesProxy", "m_iWinningTeam");
	NETVAR(m_iWinReason, int, "CTeamplayRoundBasedRulesProxy", "m_iWinReason");
	NETVAR(m_bInWaitingForPlayers, bool, "CTeamplayRoundBasedRulesProxy", "m_bInWaitingForPlayers");
	NETVAR(m_bAwaitingReadyRestart, bool, "CTeamplayRoundBasedRulesProxy", "m_bAwaitingReadyRestart");
	NETVAR(m_flRestartRoundTime, float, "CTeamplayRoundBasedRulesProxy", "m_flRestartRoundTime");
	NETVAR(m_flMapResetTime, float, "CTeamplayRoundBasedRulesProxy", "m_flMapResetTime");
	NETVAR(m_flNextRespawnWave, void*, "CTeamplayRoundBasedRulesProxy", "m_flNextRespawnWave");
	NETVAR(m_bTeamReady, void*, "CTeamplayRoundBasedRulesProxy", "m_bTeamReady");
	NETVAR(m_bStopWatch, bool, "CTeamplayRoundBasedRulesProxy", "m_bStopWatch");
	NETVAR(m_bMultipleTrains, bool, "CTeamplayRoundBasedRulesProxy", "m_bMultipleTrains");
	NETVAR(m_bPlayerReady, void*, "CTeamplayRoundBasedRulesProxy", "m_bPlayerReady");
	NETVAR(m_bCheatsEnabledDuringLevel, bool, "CTeamplayRoundBasedRulesProxy", "m_bCheatsEnabledDuringLevel");
	NETVAR(m_nRoundsPlayed, int, "CTeamplayRoundBasedRulesProxy", "m_nRoundsPlayed");
	NETVAR(m_flCountdownTime, float, "CTeamplayRoundBasedRulesProxy", "m_flCountdownTime");
	NETVAR(m_flStateTransitionTime, float, "CTeamplayRoundBasedRulesProxy", "m_flStateTransitionTime");
	NETVAR(m_TeamRespawnWaveTimes, void*, "CTeamplayRoundBasedRulesProxy", "m_TeamRespawnWaveTimes");
};

class CTFGameRules : public CTeamplayRoundBasedRules
{
public:
	CTFGameRules* Get()
	{
		return *reinterpret_cast<CTFGameRules**>(U::Memory.RelToAbs(S::CTFGameRules_Get()));
	}

public:
	__inline CViewVectors* GetViewVectors()
	{
		return reinterpret_cast<CViewVectors*(*)()>(U::Memory.GetVFunc(this, 31))();
	}

public:
	NETVAR(m_nGameType, int, "CTFGameRulesProxy", "m_nGameType");
	NETVAR(m_nStopWatchState, int, "CTFGameRulesProxy", "m_nStopWatchState");
	NETVAR(m_pszTeamGoalStringRed, const char*, "CTFGameRulesProxy", "m_pszTeamGoalStringRed");
	NETVAR(m_pszTeamGoalStringBlue, const char*, "CTFGameRulesProxy", "m_pszTeamGoalStringBlue");
	NETVAR(m_flCapturePointEnableTime, float, "CTFGameRulesProxy", "m_flCapturePointEnableTime");
	NETVAR(m_iGlobalAttributeCacheVersion, int, "CTFGameRulesProxy", "m_iGlobalAttributeCacheVersion");
	NETVAR(m_nHudType, int, "CTFGameRulesProxy", "m_nHudType");
	NETVAR(m_bIsInTraining, bool, "CTFGameRulesProxy", "m_bIsInTraining");
	NETVAR(m_bAllowTrainingAchievements, bool, "CTFGameRulesProxy", "m_bAllowTrainingAchievements");
	NETVAR(m_bIsWaitingForTrainingContinue, bool, "CTFGameRulesProxy", "m_bIsWaitingForTrainingContinue");
	NETVAR(m_bIsTrainingHUDVisible, bool, "CTFGameRulesProxy", "m_bIsTrainingHUDVisible");
	NETVAR(m_bIsInItemTestingMode, bool, "CTFGameRulesProxy", "m_bIsInItemTestingMode");
	NETVAR(m_hBonusLogic, int /*EHANDLE CBonusRoundLogic*/, "CTFGameRulesProxy", "m_hBonusLogic");
	NETVAR(m_bPlayingKoth, bool, "CTFGameRulesProxy", "m_bPlayingKoth");
	NETVAR(m_bPowerupMode, bool, "CTFGameRulesProxy", "m_bPowerupMode");
	NETVAR(m_bPlayingRobotDestructionMode, bool, "CTFGameRulesProxy", "m_bPlayingRobotDestructionMode");
	NETVAR(m_bPlayingMedieval, bool, "CTFGameRulesProxy", "m_bPlayingMedieval");
	NETVAR(m_bPlayingHybrid_CTF_CP, bool, "CTFGameRulesProxy", "m_bPlayingHybrid_CTF_CP");
	NETVAR(m_bPlayingSpecialDeliveryMode, bool, "CTFGameRulesProxy", "m_bPlayingSpecialDeliveryMode");
	NETVAR(m_bPlayingMannVsMachine, bool, "CTFGameRulesProxy", "m_bPlayingMannVsMachine");
	NETVAR(m_bMannVsMachineAlarmStatus, bool, "CTFGameRulesProxy", "m_bMannVsMachineAlarmStatus");
	NETVAR(m_bHaveMinPlayersToEnableReady, bool, "CTFGameRulesProxy", "m_bHaveMinPlayersToEnableReady");
	NETVAR(m_bBountyModeEnabled, bool, "CTFGameRulesProxy", "m_bBountyModeEnabled");
	NETVAR(m_bCompetitiveMode, bool, "CTFGameRulesProxy", "m_bCompetitiveMode");
	NETVAR(m_flGravityMultiplier, float, "CTFGameRulesProxy", "m_flGravityMultiplier");
	NETVAR(m_nMatchGroupType, int, "CTFGameRulesProxy", "m_nMatchGroupType");
	NETVAR(m_bMatchEnded, bool, "CTFGameRulesProxy", "m_bMatchEnded");
	NETVAR(m_bHelltowerPlayersInHell, bool, "CTFGameRulesProxy", "m_bHelltowerPlayersInHell");
	NETVAR(m_bIsUsingSpells, bool, "CTFGameRulesProxy", "m_bIsUsingSpells");
	NETVAR(m_bTruceActive, bool, "CTFGameRulesProxy", "m_bTruceActive");
	NETVAR(m_bTeamsSwitched, bool, "CTFGameRulesProxy", "m_bTeamsSwitched");
	NETVAR(m_hRedKothTimer, int /*EHANDLE*/, "CTFGameRulesProxy", "m_hRedKothTimer");
	NETVAR(m_hBlueKothTimer, int /*EHANDLE*/, "CTFGameRulesProxy", "m_hBlueKothTimer");
	NETVAR(m_nMapHolidayType, int, "CTFGameRulesProxy", "m_nMapHolidayType");
	NETVAR(m_pszCustomUpgradesFile, const char*, "CTFGameRulesProxy", "m_pszCustomUpgradesFile");
	NETVAR(m_bShowMatchSummary, bool, "CTFGameRulesProxy", "m_bShowMatchSummary");
	NETVAR(m_bMapHasMatchSummaryStage, bool, "CTFGameRulesProxy", "m_bMapHasMatchSummaryStage");
	NETVAR(m_bPlayersAreOnMatchSummaryStage, bool, "CTFGameRulesProxy", "m_bPlayersAreOnMatchSummaryStage");
	NETVAR(m_bStopWatchWinner, bool, "CTFGameRulesProxy", "m_bStopWatchWinner");
	NETVAR(m_ePlayerWantsRematch, void*, "CTFGameRulesProxy", "m_ePlayerWantsRematch");
	NETVAR(m_eRematchState, int, "CTFGameRulesProxy", "m_eRematchState");
	NETVAR(m_nNextMapVoteOptions, void*, "CTFGameRulesProxy", "m_nNextMapVoteOptions");
	NETVAR(m_nBossHealth, int, "CTFGameRulesProxy", "m_nBossHealth");
	NETVAR(m_nMaxBossHealth, int, "CTFGameRulesProxy", "m_nMaxBossHealth");
	NETVAR(m_fBossNormalizedTravelDistance, int, "CTFGameRulesProxy", "m_fBossNormalizedTravelDistance");
	NETVAR(m_itHandle, int, "CTFGameRulesProxy", "m_itHandle");
	NETVAR(m_hBirthdayPlayer, int, "CTFGameRulesProxy", "m_hBirthdayPlayer");
	NETVAR(m_nHalloweenEffect, int, "CTFGameRulesProxy", "m_nHalloweenEffect");
	NETVAR(m_fHalloweenEffectStartTime, float, "CTFGameRulesProxy", "m_fHalloweenEffectStartTime");
	NETVAR(m_fHalloweenEffectDuration, float, "CTFGameRulesProxy", "m_fHalloweenEffectDuration");
	NETVAR(m_halloweenScenario, int, "CTFGameRulesProxy", "m_halloweenScenario");
	NETVAR(m_nForceUpgrades, int, "CTFGameRulesProxy", "m_nForceUpgrades");
	NETVAR(m_nForceEscortPushLogic, int, "CTFGameRulesProxy", "m_nForceEscortPushLogic");
	NETVAR(m_bRopesHolidayLightsAllowed, bool, "CTFGameRulesProxy", "m_bRopesHolidayLightsAllowed");

	inline bool IsPlayerReady(int playerIndex)
	{
		if (playerIndex > 101)
			return false;
		
		static int nOffset = U::NetVars.GetNetVar("CTeamplayRoundBasedRulesProxy", "m_bPlayerReady");
		bool* ReadyStatus = reinterpret_cast<bool*>(uintptr_t(this) + nOffset);
		if (!ReadyStatus)
			return false;

		return ReadyStatus[playerIndex];
	}
};

MAKE_INTERFACE_NULL(CTFGameRules, TFGameRules);