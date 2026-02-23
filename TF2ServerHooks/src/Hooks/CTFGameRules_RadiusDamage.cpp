#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CTFBaseRocket_Explode, "server.dll", "55 8B EC 81 EC ? ? ? ? 53 56 8B F1 57 8B 06 8B 80", 0x0);
#else
MAKE_SIGNATURE(CTFBaseRocket_Explode, "server.dll", "40 55 56 41 54 41 57 48 8D AC 24", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFWeaponBaseGrenadeProj_Detonate, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC D9 EE 81 EC ? ? ? ? 56 57 6A ? 51 D9 1C 24 6A ? 8B F9 E8 ? ? ? ? 8B 87 ? ? ? ? C1 E8 ? A8 ? 74 ? 8B CF E8 ? ? ? ? F3 0F 10 8F ? ? ? ? 8D 4D ? F3 0F 58 0D ? ? ? ? 6A ? 6A ? 57 C7 45 ? ? ? ? ? 0F 28 C1 C7 45 ? ? ? ? ? F3 0F 5C 05 ? ? ? ? 66 C7 45 ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? F3 0F 5C C1 C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? F3 0F 11 4D ? F3 0F 11 45 ? F3 0F 10 87 ? ? ? ? F3 0F 11 45 ? F3 0F 10 87 ? ? ? ? F3 0F 11 45 ? E8 ? ? ? ? 8B 0D ? ? ? ? 8D 95 ? ? ? ? 52 8D 55 ? 52 8B 01 8D 55 ? 68 ? ? ? ? 52 FF 50 ? A1 ? ? ? ? 83 78 ? ? 74 ? D9 05 ? ? ? ? 8D 85 ? ? ? ? 51 D9 1C 24 6A ? 6A ? 6A ? 68 ? ? ? ? 50 8D 85 ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? 8B 37 8B CF 8B 86 ? ? ? ? FF D0 50 8D 85 ? ? ? ? 8B CF 50 FF 96 ? ? ? ? 8B 07", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBaseGrenadeProj_Detonate, "server.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 45 33 C9", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFGameRules_RadiusDamage, "server.dll", "55 8B EC 81 EC ? ? ? ? 53 56 57 8B 7D ? C7 45", 0x0);
#else
MAKE_SIGNATURE(CTFGameRules_RadiusDamage, "server.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 F3 0F 10 52", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CBaseEntity_TraceAttackToTriggers, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 81 EC ? ? ? ? FF 73", 0x0);
#else
MAKE_SIGNATURE(CBaseEntity_TraceAttackToTriggers, "server.dll", "40 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? F3 41 0F 10 41", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFRadiusDamageInfo_ApplyToEntity_TraceAttackToTriggers_Call, "server.dll", "8B 07 8B CF 8B 80 ? ? ? ? FF D0 84 C0 74 ? 8B 36", 0x0);
#else
MAKE_SIGNATURE(CTFRadiusDamageInfo_ApplyToEntity_TraceAttackToTriggers_Call, "server.dll", "48 8B 17 48 8B CF FF 92 ? ? ? ? 84 C0 74 ? 49 8B 36", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFRadiusDamageInfo_ApplyToEntity_TraceRay_Call, "server.dll", "A1 ? ? ? ? 83 78 ? ? 74 ? D9 05 ? ? ? ? 8D 46 ? 51 D9 1C 24 6A ? 6A ? 6A ? 68 ? ? ? ? 50 56 E8 ? ? ? ? 83 C4 ? 5E 8B E5 5D 8B E3 5B C3 CC CC CC CC CC 55", 0x0);
#else
MAKE_SIGNATURE(CTFRadiusDamageInfo_ApplyToEntity_TraceRay_Call, "server.dll", "48 8B 05 ? ? ? ? 44 39 68 ? 74 ? F3 0F 10 05 ? ? ? ? 48 8D 55 ? F3 0F 11 44 24 ? 48 8D 4D ? C6 44 24 ? ? 45 33 C9 41 B8 ? ? ? ? 44 89 6C 24 ? E8 ? ? ? ? 48 8B 4D ? 44 38 6D", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFWeaponBaseGrenadeProj_Detonate_TraceRay_Call, "server.dll", "A1 ? ? ? ? 83 78 ? ? 74 ? D9 05 ? ? ? ? 8D 85 ? ? ? ? 51 D9 1C 24 6A ? 6A ? 6A ? 68 ? ? ? ? 50 8D 85 ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? 8B 37 8B CF 8B 86 ? ? ? ? FF D0 50 8D 85 ? ? ? ? 8B CF 50 FF 96 ? ? ? ? 8B 07", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBaseGrenadeProj_Detonate_TraceRay_Call, "server.dll", "48 8B 05 ? ? ? ? 83 78 ? ? 74 ? F3 0F 10 05 ? ? ? ? 48 8D 94 24 ? ? ? ? F3 0F 11 44 24 ? 48 8D 8C 24 ? ? ? ? C6 44 24 ? ? 45 33 C9 41 B8 ? ? ? ? C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B 1F", 0x0);
#endif

class CTakeDamageInfo
{
public:
	enum ECritType
	{
		CRIT_NONE = 0,
		CRIT_MINI,
		CRIT_FULL,
	};

	Vector m_vecDamageForce;
	Vector m_vecDamagePosition;
	Vector m_vecReportedPosition;
	EHANDLE m_hInflictor;
	EHANDLE m_hAttacker;
	EHANDLE m_hWeapon;
	float m_flDamage;
	float m_flMaxDamage;
	float m_flBaseDamage;
	int m_bitsDamageType;
	int m_iDamageCustom;
	int m_iDamageStats;
	int m_iAmmoType;
	int m_iDamagedOtherPlayers;
	int m_iPlayerPenetrationCount;
	float m_flDamageBonus;
	EHANDLE m_hDamageBonusProvider;
	bool m_bForceFriendlyFire;
	float m_flDamageForForce;
	ECritType m_eCritType;
};
class CTFRadiusDamageInfo
{
public:
	CTakeDamageInfo* dmgInfo;
	Vector vecSrc;
	float flRadius;
	CBaseEntity* pEntityIgnore;
	float flRJRadius;
	float m_flForceScale;
	CBaseEntity* m_pEntityTarget;
	float flFalloff;
};

#if x86
MAKE_HOOK(CTFBaseRocket_Explode, S::CTFBaseRocket_Explode(), void, __fastcall,
	void* ecx, void* edx, trace_t* pTrace, CBaseEntity* pOther)
#else
MAKE_HOOK(CTFBaseRocket_Explode, S::CTFBaseRocket_Explode(), void,
	void* rcx, trace_t* pTrace, CBaseEntity* pOther)
#endif
{
	if (G::DebugVisuals)
	{
#if x86
		auto pProjectile = reinterpret_cast<CTFBaseRocket*>(ecx);
#else
		auto pProjectile = reinterpret_cast<CTFBaseRocket*>(rcx);
#endif
		auto pWeapon = pProjectile->m_hLauncher()->As<CTFWeaponBase>();
		auto pOwner = pWeapon ? pWeapon->m_hOwner()->As<CTFPlayer>() : nullptr;
		if (!pOwner->IsPlayer())
#if x86
			return CALL_ORIGINAL(ecx, edx, pTrace, pOther);
#else
			return CALL_ORIGINAL(rcx, pTrace, pOther);
#endif

		G::DebugTarget = pOwner;

		Vec3 vOrigin = pProjectile->m_vecOrigin();
		Vec3 vMins = { -1, -1, -1 }, vMaxs = { 1, 1, 1 }, vAngles = {};
		SDK::OutputClient("Box", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vMins.x, vMins.y, vMins.z, vMaxs.x, vMaxs.y, vMaxs.z, vAngles.x, vAngles.y, vAngles.z, 255, 255, 255, 0, G::DrawDuration ? G::DrawDuration : 4.f).c_str(), G::DebugTarget);
	}

#if x86
	return CALL_ORIGINAL(ecx, edx, pTrace, pOther);
#else
	return CALL_ORIGINAL(rcx, pTrace, pOther);
#endif
}

#if x86
MAKE_HOOK(CTFWeaponBaseGrenadeProj_Detonate, S::CTFWeaponBaseGrenadeProj_Detonate(), void, __fastcall,
	void* ecx, void* edx)
#else
MAKE_HOOK(CTFWeaponBaseGrenadeProj_Detonate, S::CTFWeaponBaseGrenadeProj_Detonate(), void,
	void* rcx)
#endif
{
	if (G::DebugVisuals)
	{
#if x86
		auto pProjectile = reinterpret_cast<CTFWeaponBaseGrenadeProj*>(ecx);
#else
		auto pProjectile = reinterpret_cast<CTFWeaponBaseGrenadeProj*>(rcx);
#endif
		auto pAttacker = pProjectile->m_hThrower()->As<CTFPlayer>();
		if (!pAttacker->IsPlayer())
#if x86
			return CALL_ORIGINAL(ecx, edx);
#else
			return CALL_ORIGINAL(rcx);
#endif

		G::DebugTarget = pAttacker;

		Vec3 vOrigin = pProjectile->m_vecOrigin();
		Vec3 vMins = { -1, -1, -1 }, vMaxs = { 1, 1, 1 }, vAngles = {};
		SDK::OutputClient("Box", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vMins.x, vMins.y, vMins.z, vMaxs.x, vMaxs.y, vMaxs.z, vAngles.x, vAngles.y, vAngles.z, 255, 255, 255, 0, G::DrawDuration ? G::DrawDuration : 4.f).c_str(), G::DebugTarget);
	}

#if x86
	return CALL_ORIGINAL(ecx, edx);
#else
	return CALL_ORIGINAL(rcx);
#endif
}

#if x86
MAKE_HOOK(CTFGameRules_RadiusDamage, S::CTFGameRules_RadiusDamage(), void, __fastcall,
	void* ecx, void* edx, CTFRadiusDamageInfo& info)
#else
MAKE_HOOK(CTFGameRules_RadiusDamage, S::CTFGameRules_RadiusDamage(), void,
	void* rcx, CTFRadiusDamageInfo& info)
#endif
{
	if (G::DebugVisuals)
	{
		auto pAttacker = info.dmgInfo->m_hAttacker->As<CBasePlayer>();
		if (!pAttacker->IsPlayer())
#if x86
			return CALL_ORIGINAL(ecx, edx, info);
#else
			return CALL_ORIGINAL(rcx, info);
#endif

		G::DebugTarget = pAttacker;

		Vec3 vOrigin = info.dmgInfo->m_vecDamagePosition;
		Vec3 vMins = { -1, -1, -1 }, vMaxs = { 1, 1, 1 }, vAngles = {};
		SDK::OutputClient("Box", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vMins.x, vMins.y, vMins.z, vMaxs.x, vMaxs.y, vMaxs.z, vAngles.x, vAngles.y, vAngles.z, 255, 0, 0, 0, G::DrawDuration ? G::DrawDuration : 4.f).c_str(), G::DebugTarget);

		for (CBaseEntity* pEntity = I::GlobalEntityList->FirstEnt(); pEntity; pEntity = I::GlobalEntityList->NextEnt(pEntity))
		{
			auto pPlayer = pEntity->As<CTFPlayer>();
			if (!pEntity->IsPlayer())
				continue;

			vOrigin = pPlayer->m_vecOrigin();
			vMins = pPlayer->m_vecMins(), vMaxs = pPlayer->m_vecMaxs();
			SDK::OutputClient("Box", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vMins.x, vMins.y, vMins.z, vMaxs.x, vMaxs.y, vMaxs.z, vAngles.x, vAngles.y, vAngles.z, 0, 0, 0, 0, G::DrawDuration ? G::DrawDuration : 4.f).c_str(), G::DebugTarget);
		}
	}

#if x86
	return CALL_ORIGINAL(ecx, edx, info);
#else
	return CALL_ORIGINAL(rcx, info);
#endif
}

#if x86
MAKE_HOOK(CBaseEntity_TraceAttackToTriggers, S::CBaseEntity_TraceAttackToTriggers(), void, __fastcall,
	void* ecx, void* edx, const CTakeDamageInfo& info, const Vector& start, const Vector& end, const Vector& dir)
#else
MAKE_HOOK(CBaseEntity_TraceAttackToTriggers, S::CBaseEntity_TraceAttackToTriggers(), void,
	void* rcx, const CTakeDamageInfo& info, const Vector& start, const Vector& end, const Vector& dir)
#endif
{
	const auto dwRetAddr = uintptr_t(_ReturnAddress());
	const auto dwDesired = S::CTFRadiusDamageInfo_ApplyToEntity_TraceAttackToTriggers_Call();

	if (G::DebugVisuals)
	{
		auto pAttacker = info.m_hAttacker->As<CBasePlayer>();
		if (!pAttacker->IsPlayer())
#if x86
			return CALL_ORIGINAL(ecx, edx, info, start, end, dir);
#else
			return CALL_ORIGINAL(rcx, info, start, end, dir);
#endif

		G::DebugTarget = pAttacker;

#if x86
		auto pEntity = reinterpret_cast<CBaseEntity*>(ecx);
#else
		auto pEntity = reinterpret_cast<CBaseEntity*>(rcx);
#endif
		Vec3 vOrigin = pEntity->m_vecOrigin();
		Vec3 vMins = pEntity->m_vecMins(), vMaxs = pEntity->m_vecMaxs(), vAngles = {};
		SDK::OutputClient("Box", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vMins.x, vMins.y, vMins.z, vMaxs.x, vMaxs.y, vMaxs.z, vAngles.x, vAngles.y, vAngles.z, 255, 0, 0, 0, G::DrawDuration ? G::DrawDuration : 4.f).c_str(), G::DebugTarget);
	}

#if x86
	return CALL_ORIGINAL(ecx, edx, info, start, end, dir);
#else
	return CALL_ORIGINAL(rcx, info, start, end, dir);
#endif
}

#if x86
MAKE_HOOK(IEngineTrace_TraceRay, U::Memory.GetVirtual(I::EngineTrace, 4), void, __fastcall,
	void* ecx, void* edx, const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace)
#else
MAKE_HOOK(IEngineTrace_TraceRay, U::Memory.GetVirtual(I::EngineTrace, 4), void,
	void* rcx, const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace)
#endif
{
#if x86
	CALL_ORIGINAL(ecx, edx, ray, fMask, pTraceFilter, pTrace);
#else
	CALL_ORIGINAL(rcx, ray, fMask, pTraceFilter, pTrace);
#endif

	const auto dwRetAddr = uintptr_t(_ReturnAddress());
	const auto dwDesired1 = S::CTFRadiusDamageInfo_ApplyToEntity_TraceRay_Call();
	const auto dwDesired2 = S::CTFWeaponBaseGrenadeProj_Detonate_TraceRay_Call();

	if (G::DebugVisuals)
	{
		Vec3 vStart = pTrace->startpos;
		Vec3 vEnd = pTrace->endpos;
		if (dwRetAddr == dwDesired1)
			SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, 255, 0, 0, 0, G::DrawDuration ? G::DrawDuration : 4).c_str(), G::DebugTarget);
		else if (dwRetAddr == dwDesired2)
			SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, 255, 255, 255, 0, G::DrawDuration ? G::DrawDuration : 4).c_str(), G::DebugTarget);
	}
}