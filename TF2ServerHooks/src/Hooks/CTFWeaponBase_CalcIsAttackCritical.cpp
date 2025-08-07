#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CTFWeaponBase_CalcIsAttackCritical, "server.dll", "53 57 6A ? 68 ? ? ? ? 68 ? ? ? ? 6A ? 8B F9 E8 ? ? ? ? 50 E8 ? ? ? ? 8B D8 83 C4 ? 85 DB", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBase_CalcIsAttackCritical, "server.dll", "48 89 74 24 ? 57 48 83 EC ? 48 8B F9 E8 ? ? ? ? 48 8B C8 C7 44 24", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFGameStats_FindPlayerStats, "server.dll", "55 8B EC 8B 45 ? 85 C0 75 ? 5D C2 ? ? 8B 40", 0x0);
#else
MAKE_SIGNATURE(CTFGameStats_FindPlayerStats, "server.dll", "4C 8B C1 48 85 D2 75", 0x0);
#endif

static void* pCTFGameStats = nullptr;

#if x86
MAKE_HOOK(CTFWeaponBase_CalcIsAttackCritical, S::CTFWeaponBase_CalcIsAttackCritical(), void, __fastcall,
	void* ecx, void* edx)
#else
MAKE_HOOK(CTFWeaponBase_CalcIsAttackCritical, S::CTFWeaponBase_CalcIsAttackCritical(), void,
	void* rcx)
#endif
{
	if (!G::CritInfo)
#if x86
		return CALL_ORIGINAL(ecx, edx);
#else
		return CALL_ORIGINAL(rcx);
#endif


#if x86
	auto pWeapon = reinterpret_cast<CTFWeaponBase*>(ecx);
#else
	auto pWeapon = reinterpret_cast<CTFWeaponBase*>(rcx);
#endif

	float flOldCritTokenBucket = pWeapon->m_flCritTokenBucket();
	int nOldCritChecks = pWeapon->m_nCritChecks();
	int nOldCritSeedRequests = pWeapon->m_nCritSeedRequests();
	float flOldLastRapidFireCritCheckTime = pWeapon->m_flLastRapidFireCritCheckTime();
	float flOldCritTime = pWeapon->m_flCritTime();
	//int iOldCurrentSeed = pWeapon->m_iCurrentSeed();

#if x86
	CALL_ORIGINAL(ecx, edx);
#else
	CALL_ORIGINAL(rcx);
#endif

	G::DebugTarget = pWeapon->m_hOwner()->As<CBasePlayer>();
	SDK::OutputClient(std::format(
		"[CritTokenBucket] {} -> {}"
		"\n[CritChecks] {} -> {}"
		"\n[CritSeedRequests] {} -> {}"
		"\n[LastRapidFireCritCheckTime] {} -> {}"
		"\n[CritTime] {} -> {}"
		//"\n[CurrentSeed] {} -> {}"
		/*"\n[Critting] {}"
		"\n[Waiting] {}"*/,
		flOldCritTokenBucket, pWeapon->m_flCritTokenBucket(),
		nOldCritChecks, pWeapon->m_nCritChecks(),
		nOldCritSeedRequests, pWeapon->m_nCritSeedRequests(),
		flOldLastRapidFireCritCheckTime, pWeapon->m_flLastRapidFireCritCheckTime(),
		flOldCritTime, pWeapon->m_flCritTime()/*,
		iOldCurrentSeed, pWeapon->m_iCurrentSeed(),
		pWeapon->m_flCritTime() > I::GlobalVars->curtime,
		I::GlobalVars->curtime < pWeapon->m_flLastRapidFireCritCheckTime() + 1.f*/
	).c_str(), nullptr, G::DebugTarget, HUD_PRINTTALK);

	/*
	if (pCTFGameStats)
	{
		if (auto pPlayerStats = S::CTFGameStats_FindPlayerStats.Call<PlayerStats_t*>(pCTFGameStats, G::DebugTarget))
		{
			SDK::OutputClient(std::format(
				"[RangedDamage] {}"
				"\n[CritDamage] {}"
				"\n[AllDamage] {} ({})",
				pPlayerStats->statsCurrentRound.m_iStat[TFSTAT_DAMAGE_RANGED],
				pPlayerStats->statsCurrentRound.m_iStat[TFSTAT_DAMAGE_RANGED_CRIT_RANDOM],
				pPlayerStats->statsCurrentRound.m_iStat[TFSTAT_DAMAGE], pPlayerStats->statsCurrentRound.m_iStat[TFSTAT_DAMAGE] - pPlayerStats->statsCurrentRound.m_iStat[TFSTAT_DAMAGE_RANGED]
			).c_str(), nullptr, G::DebugTarget, HUD_PRINTTALK);
		}
	}
	*/
}

#if x86
MAKE_HOOK(CTFGameStats_FindPlayerStats, S::CTFGameStats_FindPlayerStats(), void*, __fastcall,
	void* ecx, void* edx, CBasePlayer* pPlayer)
#else
MAKE_HOOK(CTFGameStats_FindPlayerStats, S::CTFGameStats_FindPlayerStats(), void*,
	void* rcx, CBasePlayer* pPlayer)
#endif
{
#if x86
	pCTFGameStats = ecx;
	return CALL_ORIGINAL(ecx, edx, pPlayer);
#else
	pCTFGameStats = rcx;
	return CALL_ORIGINAL(rcx, pPlayer);
#endif
}