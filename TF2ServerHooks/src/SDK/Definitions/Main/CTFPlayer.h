#pragma once
#include "CBasePlayer.h"
#include "CMultiPlayerAnimState.h"
#include "CTFWeaponBase.h"
#include "../../../Utils/Signatures/Signatures.h"

#if x86
MAKE_SIGNATURE(TeamFortress_CalculateMaxSpeed, "server.dll", "55 8B EC 83 EC ? 56 8B F1 8B 0D ? ? ? ? 57 85 C9", 0x0);
#else
MAKE_SIGNATURE(TeamFortress_CalculateMaxSpeed, "server.dll", "88 54 24 ? 53", 0x0);
#endif

class CTFPlayer : public CBasePlayer
{
public:
	NETVAR(m_bSaveMeParity, bool, "CTFPlayer", "m_bSaveMeParity");
	NETVAR(m_bIsMiniBoss, bool, "CTFPlayer", "m_bIsMiniBoss");
	NETVAR(m_bIsABot, bool, "CTFPlayer", "m_bIsABot");
	NETVAR(m_nBotSkill, int, "CTFPlayer", "m_nBotSkill");
	NETVAR(m_nWaterLevel, byte, "CTFPlayer", "m_nWaterLevel");
	NETVAR(m_hRagdoll, EHANDLE, "CTFPlayer", "m_hRagdoll");
	NETVAR(m_PlayerClass, void*, "CTFPlayer", "m_PlayerClass");
	NETVAR(m_iClass, int, "CTFPlayer", "m_iClass");
	NETVAR(m_iszClassIcon, const char*, "CTFPlayer", "m_iszClassIcon");
	NETVAR(m_iszCustomModel, const char*, "CTFPlayer", "m_iszCustomModel");
	NETVAR(m_vecCustomModelOffset, Vec3, "CTFPlayer", "m_vecCustomModelOffset");
	NETVAR(m_angCustomModelRotation, Vec3, "CTFPlayer", "m_angCustomModelRotation");
	NETVAR(m_bCustomModelRotates, bool, "CTFPlayer", "m_bCustomModelRotates");
	NETVAR(m_bCustomModelRotationSet, bool, "CTFPlayer", "m_bCustomModelRotationSet");
	NETVAR(m_bCustomModelVisibleToSelf, bool, "CTFPlayer", "m_bCustomModelVisibleToSelf");
	NETVAR(m_bUseClassAnimations, bool, "CTFPlayer", "m_bUseClassAnimations");
	NETVAR(m_iClassModelParity, int, "CTFPlayer", "m_iClassModelParity");
	NETVAR(m_Shared, void*, "CTFPlayer", "m_Shared");
	NETVAR(m_nPlayerCond, int, "CTFPlayer", "m_nPlayerCond");
	NETVAR(m_bJumping, bool, "CTFPlayer", "m_bJumping");
	NETVAR(m_nNumHealers, int, "CTFPlayer", "m_nNumHealers");
	NETVAR(m_iCritMult, int, "CTFPlayer", "m_iCritMult");
	NETVAR(m_iAirDash, int, "CTFPlayer", "m_iAirDash");
	NETVAR(m_nAirDucked, int, "CTFPlayer", "m_nAirDucked");
	NETVAR(m_flDuckTimer, float, "CTFPlayer", "m_flDuckTimer");
	NETVAR(m_nPlayerState, int, "CTFPlayer", "m_nPlayerState");
	NETVAR(m_iDesiredPlayerClass, int, "CTFPlayer", "m_iDesiredPlayerClass");
	NETVAR(m_flMovementStunTime, float, "CTFPlayer", "m_flMovementStunTime");
	NETVAR(m_iMovementStunAmount, int, "CTFPlayer", "m_iMovementStunAmount");
	NETVAR(m_iMovementStunParity, int, "CTFPlayer", "m_iMovementStunParity");
	NETVAR(m_hStunner, EHANDLE, "CTFPlayer", "m_hStunner");
	NETVAR(m_iStunFlags, int, "CTFPlayer", "m_iStunFlags");
	NETVAR(m_nArenaNumChanges, int, "CTFPlayer", "m_nArenaNumChanges");
	NETVAR(m_bArenaFirstBloodBoost, bool, "CTFPlayer", "m_bArenaFirstBloodBoost");
	NETVAR(m_iWeaponKnockbackID, int, "CTFPlayer", "m_iWeaponKnockbackID");
	NETVAR(m_bLoadoutUnavailable, bool, "CTFPlayer", "m_bLoadoutUnavailable");
	NETVAR(m_iItemFindBonus, int, "CTFPlayer", "m_iItemFindBonus");
	NETVAR(m_bShieldEquipped, bool, "CTFPlayer", "m_bShieldEquipped");
	NETVAR(m_bParachuteEquipped, bool, "CTFPlayer", "m_bParachuteEquipped");
	NETVAR(m_iNextMeleeCrit, int, "CTFPlayer", "m_iNextMeleeCrit");
	NETVAR(m_iDecapitations, int, "CTFPlayer", "m_iDecapitations");
	NETVAR(m_iRevengeCrits, int, "CTFPlayer", "m_iRevengeCrits");
	NETVAR(m_iDisguiseBody, int, "CTFPlayer", "m_iDisguiseBody");
	NETVAR(m_hCarriedObject, EHANDLE, "CTFPlayer", "m_hCarriedObject");
	NETVAR(m_bCarryingObject, bool, "CTFPlayer", "m_bCarryingObject");
	NETVAR(m_flNextNoiseMakerTime, float, "CTFPlayer", "m_flNextNoiseMakerTime");
	NETVAR(m_iSpawnRoomTouchCount, int, "CTFPlayer", "m_iSpawnRoomTouchCount");
	NETVAR(m_iKillCountSinceLastDeploy, int, "CTFPlayer", "m_iKillCountSinceLastDeploy");
	NETVAR(m_flFirstPrimaryAttack, float, "CTFPlayer", "m_flFirstPrimaryAttack");
	NETVAR(m_flEnergyDrinkMeter, float, "CTFPlayer", "m_flEnergyDrinkMeter");
	NETVAR(m_flHypeMeter, float, "CTFPlayer", "m_flHypeMeter");
	NETVAR(m_flChargeMeter, float, "CTFPlayer", "m_flChargeMeter");
	NETVAR(m_flInvisChangeCompleteTime, float, "CTFPlayer", "m_flInvisChangeCompleteTime");
	NETVAR(m_nDisguiseTeam, int, "CTFPlayer", "m_nDisguiseTeam");
	NETVAR(m_nDisguiseClass, int, "CTFPlayer", "m_nDisguiseClass");
	NETVAR(m_nDisguiseSkinOverride, int, "CTFPlayer", "m_nDisguiseSkinOverride");
	NETVAR(m_nMaskClass, int, "CTFPlayer", "m_nMaskClass");
	NETVAR(m_iDisguiseTargetIndex, int, "CTFPlayer", "m_iDisguiseTargetIndex");
	NETVAR(m_iDisguiseHealth, int, "CTFPlayer", "m_iDisguiseHealth");
	NETVAR(m_bFeignDeathReady, bool, "CTFPlayer", "m_bFeignDeathReady");
	NETVAR(m_hDisguiseWeapon, EHANDLE, "CTFPlayer", "m_hDisguiseWeapon");
	NETVAR(m_nTeamTeleporterUsed, int, "CTFPlayer", "m_nTeamTeleporterUsed");
	NETVAR(m_flCloakMeter, float, "CTFPlayer", "m_flCloakMeter");
	NETVAR(m_flSpyTranqBuffDuration, float, "CTFPlayer", "m_flSpyTranqBuffDuration");
	NETVAR(m_nDesiredDisguiseTeam, int, "CTFPlayer", "m_nDesiredDisguiseTeam");
	NETVAR(m_nDesiredDisguiseClass, int, "CTFPlayer", "m_nDesiredDisguiseClass");
	NETVAR(m_flStealthNoAttackExpire, float, "CTFPlayer", "m_flStealthNoAttackExpire");
	NETVAR(m_flStealthNextChangeTime, float, "CTFPlayer", "m_flStealthNextChangeTime");
	NETVAR(m_bLastDisguisedAsOwnTeam, bool, "CTFPlayer", "m_bLastDisguisedAsOwnTeam");
	NETVAR(m_flRageMeter, float, "CTFPlayer", "m_flRageMeter");
	NETVAR(m_bRageDraining, bool, "CTFPlayer", "m_bRageDraining");
	NETVAR(m_flNextRageEarnTime, float, "CTFPlayer", "m_flNextRageEarnTime");
	NETVAR(m_bInUpgradeZone, bool, "CTFPlayer", "m_bInUpgradeZone");
	NETVAR(m_flItemChargeMeter, void*, "CTFPlayer", "m_flItemChargeMeter");
	NETVAR(m_bPlayerDominated, void*, "CTFPlayer", "m_bPlayerDominated");
	NETVAR(m_bPlayerDominatingMe, void*, "CTFPlayer", "m_bPlayerDominatingMe");
	NETVAR(m_ScoreData, void*, "CTFPlayer", "m_ScoreData");
	NETVAR(m_iCaptures, int, "CTFPlayer", "m_iCaptures");
	NETVAR(m_iDefenses, int, "CTFPlayer", "m_iDefenses");
	NETVAR(m_iKills, int, "CTFPlayer", "m_iKills");
	NETVAR(m_iDeaths, int, "CTFPlayer", "m_iDeaths");
	NETVAR(m_iSuicides, int, "CTFPlayer", "m_iSuicides");
	NETVAR(m_iDominations, int, "CTFPlayer", "m_iDominations");
	NETVAR(m_iRevenge, int, "CTFPlayer", "m_iRevenge");
	NETVAR(m_iBuildingsBuilt, int, "CTFPlayer", "m_iBuildingsBuilt");
	NETVAR(m_iBuildingsDestroyed, int, "CTFPlayer", "m_iBuildingsDestroyed");
	NETVAR(m_iHeadshots, int, "CTFPlayer", "m_iHeadshots");
	NETVAR(m_iBackstabs, int, "CTFPlayer", "m_iBackstabs");
	NETVAR(m_iHealPoints, int, "CTFPlayer", "m_iHealPoints");
	NETVAR(m_iInvulns, int, "CTFPlayer", "m_iInvulns");
	NETVAR(m_iTeleports, int, "CTFPlayer", "m_iTeleports");
	NETVAR(m_iResupplyPoints, int, "CTFPlayer", "m_iResupplyPoints");
	NETVAR(m_iKillAssists, int, "CTFPlayer", "m_iKillAssists");
	NETVAR(m_iPoints, int, "CTFPlayer", "m_iPoints");
	NETVAR(m_iBonusPoints, int, "CTFPlayer", "m_iBonusPoints");
	NETVAR(m_iDamageDone, int, "CTFPlayer", "m_iDamageDone");
	NETVAR(m_iCrits, int, "CTFPlayer", "m_iCrits");
	NETVAR(m_RoundScoreData, void*, "CTFPlayer", "m_RoundScoreData");
	NETVAR(m_ConditionList, void*, "CTFPlayer", "m_ConditionList");
	NETVAR(_condition_bits, int, "CTFPlayer", "_condition_bits");
	NETVAR(m_iTauntIndex, int, "CTFPlayer", "m_iTauntIndex");
	NETVAR(m_iTauntConcept, int, "CTFPlayer", "m_iTauntConcept");
	NETVAR(m_nPlayerCondEx, int, "CTFPlayer", "m_nPlayerCondEx");
	NETVAR(m_iStunIndex, int, "CTFPlayer", "m_iStunIndex");
	NETVAR(m_nHalloweenBombHeadStage, int, "CTFPlayer", "m_nHalloweenBombHeadStage");
	NETVAR(m_nPlayerCondEx2, int, "CTFPlayer", "m_nPlayerCondEx2");
	NETVAR(m_nPlayerCondEx3, int, "CTFPlayer", "m_nPlayerCondEx3");
	NETVAR(m_nStreaks, void*, "CTFPlayer", "m_nStreaks");
	NETVAR(m_unTauntSourceItemID_Low, int, "CTFPlayer", "m_unTauntSourceItemID_Low");
	NETVAR(m_unTauntSourceItemID_High, int, "CTFPlayer", "m_unTauntSourceItemID_High");
	NETVAR(m_flRuneCharge, float, "CTFPlayer", "m_flRuneCharge");
	NETVAR(m_bHasPasstimeBall, bool, "CTFPlayer", "m_bHasPasstimeBall");
	NETVAR(m_bIsTargetedForPasstimePass, bool, "CTFPlayer", "m_bIsTargetedForPasstimePass");
	NETVAR(m_hPasstimePassTarget, EHANDLE, "CTFPlayer", "m_hPasstimePassTarget");
	NETVAR(m_askForBallTime, float, "CTFPlayer", "m_askForBallTime");
	NETVAR(m_bKingRuneBuffActive, bool, "CTFPlayer", "m_bKingRuneBuffActive");
	NETVAR(m_nPlayerCondEx4, int, "CTFPlayer", "m_nPlayerCondEx4");
	NETVAR(m_flHolsterAnimTime, float, "CTFPlayer", "m_flHolsterAnimTime");
	NETVAR(m_hSwitchTo, EHANDLE, "CTFPlayer", "m_hSwitchTo");
	NETVAR(m_hItem, EHANDLE, "CTFPlayer", "m_hItem");
	NETVAR(m_bIsCoaching, bool, "CTFPlayer", "m_bIsCoaching");
	NETVAR(m_hCoach, EHANDLE, "CTFPlayer", "m_hCoach");
	NETVAR(m_hStudent, EHANDLE, "CTFPlayer", "m_hStudent");
	NETVAR(m_nCurrency, int, "CTFPlayer", "m_nCurrency");
	NETVAR(m_nExperienceLevel, int, "CTFPlayer", "m_nExperienceLevel");
	NETVAR(m_nExperienceLevelProgress, int, "CTFPlayer", "m_nExperienceLevelProgress");
	NETVAR(m_bMatchSafeToLeave, bool, "CTFPlayer", "m_bMatchSafeToLeave");
	NETVAR(m_vecOrigin, Vec3, "CTFPlayer", "m_vecOrigin");
	NETVAR(m_angEyeAnglesX, float, "CTFPlayer", "m_angEyeAngles[0]");
	NETVAR(m_angEyeAnglesY, float, "CTFPlayer", "m_angEyeAngles[1]");
	NETVAR(m_bAllowMoveDuringTaunt, bool, "CTFPlayer", "m_bAllowMoveDuringTaunt");
	NETVAR(m_bIsReadyToHighFive, bool, "CTFPlayer", "m_bIsReadyToHighFive");
	NETVAR(m_hHighFivePartner, EHANDLE, "CTFPlayer", "m_hHighFivePartner");
	NETVAR(m_nForceTauntCam, int, "CTFPlayer", "m_nForceTauntCam");
	NETVAR(m_flTauntYaw, float, "CTFPlayer", "m_flTauntYaw");
	NETVAR(m_nActiveTauntSlot, int, "CTFPlayer", "m_nActiveTauntSlot");
	NETVAR(m_iTauntItemDefIndex, int, "CTFPlayer", "m_iTauntItemDefIndex");
	NETVAR(m_flCurrentTauntMoveSpeed, float, "CTFPlayer", "m_flCurrentTauntMoveSpeed");
	NETVAR(m_flVehicleReverseTime, float, "CTFPlayer", "m_flVehicleReverseTime");
	NETVAR(m_flMvMLastDamageTime, float, "CTFPlayer", "m_flMvMLastDamageTime");
	NETVAR(m_flLastDamageTime, float, "CTFPlayer", "m_flLastDamageTime");
	NETVAR(m_bInPowerPlay, bool, "CTFPlayer", "m_bInPowerPlay");
	NETVAR(m_iSpawnCounter, int, "CTFPlayer", "m_iSpawnCounter");
	NETVAR(m_bArenaSpectator, bool, "CTFPlayer", "m_bArenaSpectator");
	NETVAR(m_AttributeManager, void*, "CTFPlayer", "m_AttributeManager");
	NETVAR(m_hOuter, EHANDLE, "CTFPlayer", "m_hOuter");
	NETVAR(m_ProviderType, int, "CTFPlayer", "m_ProviderType");
	NETVAR(m_iReapplyProvisionParity, int, "CTFPlayer", "m_iReapplyProvisionParity");
	NETVAR(m_flHeadScale, float, "CTFPlayer", "m_flHeadScale");
	NETVAR(m_flTorsoScale, float, "CTFPlayer", "m_flTorsoScale");
	NETVAR(m_flHandScale, float, "CTFPlayer", "m_flHandScale");
	NETVAR(m_bUseBossHealthBar, bool, "CTFPlayer", "m_bUseBossHealthBar");
	NETVAR(m_bUsingVRHeadset, bool, "CTFPlayer", "m_bUsingVRHeadset");
	NETVAR(m_bForcedSkin, bool, "CTFPlayer", "m_bForcedSkin");
	NETVAR(m_nForcedSkin, int, "CTFPlayer", "m_nForcedSkin");
	NETVAR(m_bGlowEnabled, bool, "CTFPlayer", "m_bGlowEnabled");
	NETVAR(m_nActiveWpnClip, int, "CTFPlayer", "m_nActiveWpnClip");
	NETVAR(m_flKartNextAvailableBoost, float, "CTFPlayer", "m_flKartNextAvailableBoost");
	NETVAR(m_iKartHealth, int, "CTFPlayer", "m_iKartHealth");
	NETVAR(m_iKartState, int, "CTFPlayer", "m_iKartState");
	NETVAR(m_hGrapplingHookTarget, EHANDLE, "CTFPlayer", "m_hGrapplingHookTarget");
	NETVAR(m_hSecondaryLastWeapon, EHANDLE, "CTFPlayer", "m_hSecondaryLastWeapon");
	NETVAR(m_bUsingActionSlot, bool, "CTFPlayer", "m_bUsingActionSlot");
	NETVAR(m_flInspectTime, float, "CTFPlayer", "m_flInspectTime");
	NETVAR(m_flHelpmeButtonPressTime, float, "CTFPlayer", "m_flHelpmeButtonPressTime");
	NETVAR(m_iCampaignMedals, int, "CTFPlayer", "m_iCampaignMedals");
	NETVAR(m_iPlayerSkinOverride, int, "CTFPlayer", "m_iPlayerSkinOverride");
	NETVAR(m_bViewingCYOAPDA, bool, "CTFPlayer", "m_bViewingCYOAPDA");

	NETVAR_OFF(m_flGravity, float, "CTFPlayer", "m_nWaterLevel", -24);
	NETVAR_OFF(m_MoveType, byte, "CTFPlayer", "m_nWaterLevel", -4);
	NETVAR_OFF(m_MoveCollide, byte, "CTFPlayer", "m_nWaterLevel", -3);
	NETVAR_OFF(m_nWaterType, byte, "CTFPlayer", "m_nWaterLevel", 1);
	NETVAR_OFF(m_flInvisibility, float, "CTFPlayer", "m_flInvisChangeCompleteTime", -8);
	NETVAR_OFF(m_flTankPressure, float, "CTFPlayer", "m_Shared", 636);
	NETVAR_OFF(GetAnimState, CTFPlayerAnimState*, "CTFPlayer", "m_hItem", -88);
	NETVAR_OFF(m_flPrevTauntYaw, float, "CTFPlayer", "m_flTauntYaw", 4);
	NETVAR_OFF(m_flLastMovementStunChange, float, "CTFPlayer", "m_hItem", -180);
	NETVAR_OFF(m_flStunLerpTarget, float, "CTFPlayer", "m_hItem", -184);
	NETVAR_OFF(m_bStunNeedsFadeOut, bool, "CTFPlayer", "m_hItem", -188);
	NETVAR_OFF(m_bTauntForceMoveForward, bool, "CTFPlayer", "m_bAllowMoveDuringTaunt", 1);

	VIRTUAL(GetMaxHealth, int, int(*)(void*), 107, this);

	CONDGET(IsSlowed, m_nPlayerCond(), TFCond_Slowed);
	CONDGET(IsScoped, m_nPlayerCond(), TFCond_Zoomed);
	CONDGET(IsDisguised, m_nPlayerCond(), TFCond_Disguised);
	CONDGET(IsCloaked, m_nPlayerCond(), TFCond_Stealthed);
	CONDGET(IsUberedCond, m_nPlayerCond(), TFCond_Ubercharged);
	CONDGET(IsTaunting, m_nPlayerCond(), TFCond_Taunting);
	CONDGET(IsBonked, m_nPlayerCond(), TFCond_Bonked);
	CONDGET(IsStunned, m_nPlayerCond(), TFCond_Stunned);
	CONDGET(IsCharging, m_nPlayerCond(), TFCond_Charging);
	CONDGET(IsOnFire, m_nPlayerCond(), TFCond_OnFire);
	CONDGET(IsInJarate, m_nPlayerCond(), TFCond_Jarated);
	CONDGET(IsBleeding, m_nPlayerCond(), TFCond_Bleeding);
	CONDGET(IsInMilk, m_nPlayerCond(), TFCond_Milked);
	CONDGET(IsMegaHealed, m_nPlayerCond(), TFCond_MegaHeal);
	CONDGET(IsPhlogUbered, m_nPlayerCondEx(), TFCondEx_PyroCrits);
	CONDGET(IsBulletResist, m_nPlayerCondEx(), TFCondEx_BulletCharge);
	CONDGET(IsBlastResist, m_nPlayerCondEx(), TFCondEx_ExplosiveCharge);
	CONDGET(IsFireResist, m_nPlayerCondEx(), TFCondEx_FireCharge);
	CONDGET(IsBulletImmune, m_nPlayerCondEx2(), TFCondEx2_BulletImmune);
	CONDGET(IsBlastImmune, m_nPlayerCondEx2(), TFCondEx2_BlastImmune);
	CONDGET(IsFireImmune, m_nPlayerCondEx2(), TFCondEx2_FireImmune);
	CONDGET(IsAGhost, m_nPlayerCondEx2(), TFCondEx2_HalloweenGhostMode);
	CONDGET(IsInBumperKart, m_nPlayerCondEx2(), TFCondEx2_InKart);
	CONDGET(IsStrengthRune, m_nPlayerCondEx2(), TFCondEx2_StrengthRune);
	CONDGET(IsHasteRune, m_nPlayerCondEx2(), TFCondEx2_HasteRune);
	CONDGET(IsRegenRune, m_nPlayerCondEx2(), TFCondEx2_RegenRune);
	CONDGET(IsResistRune, m_nPlayerCondEx2(), TFCondEx2_ResistRune);
	CONDGET(IsVampireRune, m_nPlayerCondEx2(), TFCondEx2_VampireRune);
	CONDGET(IsReflectRune, m_nPlayerCondEx2(), TFCondEx2_ReflectRune);
	CONDGET(IsPrecisionRune, m_nPlayerCondEx3(), TFCondEx3_PrecisionRune);
	CONDGET(IsAgilityRune, m_nPlayerCondEx3(), TFCondEx3_AgilityRune);
	CONDGET(IsKnockoutRune, m_nPlayerCondEx3(), TFCondEx3_KnockoutRune);
	CONDGET(IsImbalanceRune, m_nPlayerCondEx3(), TFCondEx3_ImbalanceRune);
	CONDGET(IsCritTempRune, m_nPlayerCondEx3(), TFCondEx3_CritboostedTempRune);
	CONDGET(IsKingRune, m_nPlayerCondEx3(), TFCondEx3_KingRune);
	CONDGET(IsPlagueRune, m_nPlayerCondEx3(), TFCondEx3_PlagueRune);
	CONDGET(IsSupernovaRune, m_nPlayerCondEx3(), TFCondEx3_SupernovaRune);
	CONDGET(IsBuffedByKing, m_nPlayerCondEx3(), TFCondEx3_KingBuff);

	inline Vec3 GetEyeAngles()
	{
		return { m_angEyeAnglesX(), m_angEyeAnglesY(), 0.f };
	}

	inline bool InCond(const ETFCond cond)
	{
		const int iCond = static_cast<int>(cond);
		switch (iCond / 32)
		{
		case 0:
		{
			const int bit = (1 << iCond);
			if ((m_nPlayerCond() & bit) == bit || (_condition_bits() & bit) == bit)
				return true;
			break;
		}
		case 1:
		{
			const int bit = 1 << (iCond - 32);
			if ((m_nPlayerCondEx() & bit) == bit)
				return true;
			break;
		}
		case 2:
		{
			const int bit = 1 << (iCond - 64);
			if ((m_nPlayerCondEx2() & bit) == bit)
				return true;
			break;
		}
		case 3:
		{
			const int bit = 1 << (iCond - 96);
			if ((m_nPlayerCondEx3() & bit) == bit)
				return true;
			break;
		}
		case 4:
		{
			const int bit = 1 << (iCond - 128);
			if ((m_nPlayerCondEx4() & bit) == bit)
				return true;
			break;
		}
		}

		return false;
	}

	inline bool IsInvisible()
	{
		if (InCond(TF_COND_BURNING)
			|| InCond(TF_COND_BURNING_PYRO)
			|| InCond(TF_COND_MAD_MILK)
			|| InCond(TF_COND_URINE))
			return false;

		return m_flInvisibility() >= 1.f;
	}

	inline bool IsZoomed()
	{
		return InCond(TF_COND_ZOOMED);
	}

	inline bool IsInvulnerable()
	{
		return InCond(TF_COND_INVULNERABLE)
			|| InCond(TF_COND_INVULNERABLE_CARD_EFFECT)
			|| InCond(TF_COND_INVULNERABLE_HIDE_UNLESS_DAMAGED)
			|| InCond(TF_COND_INVULNERABLE_USER_BUFF)
			|| InCond(TF_COND_PHASE);
	}

	inline bool IsUbered()
	{
		return InCond(TF_COND_INVULNERABLE)
			|| InCond(TF_COND_INVULNERABLE_CARD_EFFECT)
			|| InCond(TF_COND_INVULNERABLE_HIDE_UNLESS_DAMAGED)
			|| InCond(TF_COND_INVULNERABLE_USER_BUFF);
	}

	inline bool IsCritBoosted()
	{
		return InCond(TF_COND_CRITBOOSTED)
			|| InCond(TF_COND_CRITBOOSTED_BONUS_TIME)
			|| InCond(TF_COND_CRITBOOSTED_CARD_EFFECT)
			|| InCond(TF_COND_CRITBOOSTED_CTF_CAPTURE)
			|| InCond(TF_COND_CRITBOOSTED_FIRST_BLOOD)
			|| InCond(TF_COND_CRITBOOSTED_ON_KILL)
			|| InCond(TF_COND_CRITBOOSTED_PUMPKIN)
			|| InCond(TF_COND_CRITBOOSTED_RAGE_BUFF)
			|| InCond(TF_COND_CRITBOOSTED_RUNE_TEMP)
			|| InCond(TF_COND_CRITBOOSTED_USER_BUFF);
	}

	inline bool IsMiniCritBoosted()
	{
		return InCond(TF_COND_MINICRITBOOSTED_ON_KILL)
			|| InCond(TF_COND_NOHEALINGDAMAGEBUFF)
			|| InCond(TF_COND_ENERGY_BUFF)
			/*|| InCond(TF_COND_CRITBOOSTED_DEMO_CHARGE)*/;
	}

	inline bool IsMarked()
	{
		return InCond(TF_COND_URINE)
			|| InCond(TF_COND_MARKEDFORDEATH)
			|| InCond(TF_COND_MARKEDFORDEATH_SILENT);
	}

	inline bool CanAttack(bool bCloak)
	{
		if (!IsAlive() || IsAGhost() || IsTaunting() || m_bViewingCYOAPDA()
			|| InCond(TF_COND_PHASE) || InCond(TF_COND_HALLOWEEN_KART) || InCond(TF_COND_STUNNED) && m_iStunFlags() & (TF_STUN_CONTROLS | TF_STUN_LOSER_STATE))
			return false;

		if (bCloak)
		{
			if ((m_flStealthNoAttackExpire() > TICKS_TO_TIME(m_nTickBase()) && !InCond(TF_COND_STEALTHED_USER_BUFF)) || InCond(TF_COND_STEALTHED))
			{
				auto pWeapon = m_hActiveWeapon()->As<CTFWeaponBase>();
				if (!pWeapon || pWeapon->GetWeaponID() != TF_WEAPON_GRAPPLINGHOOK)
					return false;
			}

			if (m_bFeignDeathReady())
				return false;
		}

		auto pGameRules = I::TFGameRules();
		if (pGameRules)
		{
			switch (pGameRules->m_iRoundState())
			{
			case GR_STATE_TEAM_WIN:
				if (m_iTeamNum() != pGameRules->m_iWinningTeam())
					return false;
				break;
			case GR_STATE_BETWEEN_RNDS:
				if (m_fFlags() & FL_FROZEN)
					return false;
				break;
			case GR_STATE_GAME_OVER:
				if (m_fFlags() & FL_FROZEN || m_iTeamNum() != pGameRules->m_iWinningTeam())
					return false;
				break;
			}
		}

		if (SDK::AttribHookValue(0, "no_attack", this))
			return false;

		return true;
	}

	inline float TeamFortress_CalculateMaxSpeed(bool bIgnoreSpecialAbility = false)
	{
#if x86
		return reinterpret_cast<float(__fastcall*)(CTFPlayer*, bool)>(S::TeamFortress_CalculateMaxSpeed())(this, bIgnoreSpecialAbility);
#else
		return S::TeamFortress_CalculateMaxSpeed.Call<float>(this, bIgnoreSpecialAbility);
#endif
	}

	inline float GetCritMult()
	{
		return Math::RemapVal(static_cast<float>(m_iCritMult()), 0.f, 255.f, 1.f, 4.f);
	}
};

class CTFRagdoll : public CBaseFlex
{
public:
	NETVAR(m_hPlayer, EHANDLE, "CTFRagdoll", "m_hPlayer")
	NETVAR(m_vecRagdollOrigin, Vec3, "CTFRagdoll", "m_vecRagdollOrigin");
	NETVAR(m_iPlayerIndex, int, "CTFRagdoll", "m_iPlayerIndex");
	NETVAR(m_vecForce, Vec3, "CTFRagdoll", "m_vecForce");
	NETVAR(m_vecRagdollVelocity, Vec3, "CTFRagdoll", "m_vecRagdollVelocity");
	NETVAR(m_nForceBone, int, "CTFRagdoll", "m_nForceBone");
	NETVAR(m_bGib, bool, "CTFRagdoll", "m_bGib");
	NETVAR(m_bBurning, bool, "CTFRagdoll", "m_bBurning");
	NETVAR(m_bElectrocuted, bool, "CTFRagdoll", "m_bElectrocuted");
	NETVAR(m_bFeignDeath, bool, "CTFRagdoll", "m_bFeignDeath");
	NETVAR(m_bWasDisguised, bool, "CTFRagdoll", "m_bWasDisguised");
	NETVAR(m_bOnGround, bool, "CTFRagdoll", "m_bOnGround");
	NETVAR(m_bCloaked, bool, "CTFRagdoll", "m_bCloaked");
	NETVAR(m_bBecomeAsh, bool, "CTFRagdoll", "m_bBecomeAsh");
	NETVAR(m_iDamageCustom, int, "CTFRagdoll", "m_iDamageCustom");
	NETVAR(m_iTeam, int, "CTFRagdoll", "m_iTeam");
	NETVAR(m_iClass, int, "CTFRagdoll", "m_iClass");
	NETVAR(m_bGoldRagdoll, bool, "CTFRagdoll", "m_bGoldRagdoll");
	NETVAR(m_bIceRagdoll, bool, "CTFRagdoll", "m_bIceRagdoll");
	NETVAR(m_bCritOnHardHit, bool, "CTFRagdoll", "m_bCritOnHardHit");
	NETVAR(m_flHeadScale, float, "CTFRagdoll", "m_flHeadScale");
	NETVAR(m_flTorsoScale, float, "CTFRagdoll", "m_flTorsoScale");
	NETVAR(m_flHandScale, float, "CTFRagdoll", "m_flHandScale");

	NETVAR_OFF(m_bDissolving, bool, "CTFRagdoll", "m_bFeignDeath", -1);
};