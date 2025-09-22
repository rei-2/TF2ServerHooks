#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CTFPlayer_FireBullet, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 81 EC ? ? ? ? 56 8B F1 8B 4B ? 57", 0x0);
#else
MAKE_SIGNATURE(CTFPlayer_FireBullet, "server.dll", "48 8B C4 44 88 48 ? 4C 89 40 ? 48 89 50", 0x0);
#endif

#if x86
MAKE_SIGNATURE(UTIL_PlayerBulletTrace, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 81 EC ? ? ? ? 56 57 FF 73 ? 8D 8D", 0x0);
#else
MAKE_SIGNATURE(UTIL_PlayerBulletTrace, "server.dll", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 4C 89 6C 24 ? 55 41 56 41 57 48 8D AC 24", 0x0);
#endif

#if x86
MAKE_SIGNATURE(UTIL_TraceLine, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 83 EC ? 8B 43 ? 8B 4B ? 56 C6 45", 0x0);
#else
MAKE_SIGNATURE(UTIL_TraceLine, "server.dll", "48 8B C4 53 48 81 EC ? ? ? ? F3 0F 10 42 ? F3 0F 10 19", 0x0);
#endif

#if x86
MAKE_SIGNATURE(UTIL_PlayerBulletTrace_TraceLine_Call, "server.dll", "33 C0 83 C4 ? 89 45 ? 89 45", 0x0);
#else
MAKE_SIGNATURE(UTIL_PlayerBulletTrace_TraceLine_Call, "server.dll", "80 7B ? ? 0F 85 ? ? ? ? 48 8B CB", 0x0);
#endif

#if x86
MAKE_SIGNATURE(UTIL_ClipTraceToPlayers, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 81 EC ? ? ? ? 56 8B 73 ? 8D 8D", 0x0);
#else
MAKE_SIGNATURE(UTIL_ClipTraceToPlayers, "server.dll", "48 8B C4 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D 68", 0x0);
#endif

//static Vec3 vStart = {}, vEnd = {};
static CTFPlayer* s_pPlayer = nullptr;

#if x86
MAKE_HOOK(CTFPlayer_FireBullet, S::CTFPlayer_FireBullet(), void, __fastcall,
	void* ecx, void* edx, CTFWeaponBase* pWpn, const FireBulletsInfo_t& info, bool bDoEffects, int nDamageType, int nCustomDamageType)
#else
MAKE_HOOK(CTFPlayer_FireBullet, S::CTFPlayer_FireBullet(), void,
	void* rcx, CTFWeaponBase* pWpn, const FireBulletsInfo_t& info, bool bDoEffects, int nDamageType, int nCustomDamageType)
#endif
{
#if x86
	s_pPlayer = reinterpret_cast<CTFPlayer*>(ecx);
#else
	s_pPlayer = reinterpret_cast<CTFPlayer*>(rcx);
#endif

	/*
	Vec3 vStart = info.m_vecSrc;
	Vec3 vEnd = vStart + info.m_vecDirShooting * info.m_flDistance;
	if (G::DebugVisuals)
#if x86
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z - 1, vEnd.x, vEnd.y, vEnd.z - 1, 0, 0, 0, 0, G::DrawDuration ? G::DrawDuration : 4).c_str(), pPlayer);
#else
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z - 1, vEnd.x, vEnd.y, vEnd.z - 1, 0, 0, 0, 0, G::DrawDuration ? G::DrawDuration : 4).c_str(), pPlayer);
#endif
	*/

#if x86
	CALL_ORIGINAL(ecx, edx, pWpn, info, bDoEffects, nDamageType, nCustomDamageType);
#else
	CALL_ORIGINAL(rcx, pWpn, info, bDoEffects, nDamageType, nCustomDamageType);
#endif
}

#if x86
MAKE_HOOK(UTIL_PlayerBulletTrace, S::UTIL_PlayerBulletTrace(), void, __cdecl,
	const Vector& vecStart, const Vector& vecEnd, const Vector& vecDir, unsigned int mask, ITraceFilter* pFilter, trace_t* trace)
#else
MAKE_HOOK(UTIL_PlayerBulletTrace, S::UTIL_PlayerBulletTrace(), void,
	const Vector& vecStart, const Vector& vecEnd, const Vector& vecDir, unsigned int mask, ITraceFilter* pFilter, trace_t* trace)
#endif
{
	CALL_ORIGINAL(vecStart, vecEnd, vecDir, mask, pFilter, trace);

	if (G::DebugVisuals)
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vecStart.x, vecStart.y, vecStart.z, trace->endpos.x, trace->endpos.y, trace->endpos.z, 0, 0, 255, 0, G::DrawDuration ? G::DrawDuration : 4).c_str(), s_pPlayer);
}

#if x86
MAKE_HOOK(UTIL_TraceLine, S::UTIL_TraceLine(), void, __cdecl,
	const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter* pFilter, trace_t* ptr)
#else
MAKE_HOOK(UTIL_TraceLine, S::UTIL_TraceLine(), void,
	const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter* pFilter, trace_t* ptr)
#endif
{
	static const auto dwDesired = S::UTIL_PlayerBulletTrace_TraceLine_Call();
	const auto dwRetAddr = uintptr_t(_ReturnAddress());

	CALL_ORIGINAL(vecAbsStart, vecAbsEnd, mask, pFilter, ptr);

	if (G::DebugVisuals && dwDesired == dwRetAddr)
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vecAbsStart.x, vecAbsStart.y, vecAbsStart.z + 1, ptr->endpos.x, ptr->endpos.y, ptr->endpos.z + 1, 255, 0, 0, 0, G::DrawDuration ? G::DrawDuration : 4).c_str(), s_pPlayer);
}

#if x86
MAKE_HOOK(UTIL_ClipTraceToPlayers, S::UTIL_ClipTraceToPlayers(), void, __cdecl,
	const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr)
#else
MAKE_HOOK(UTIL_ClipTraceToPlayers, S::UTIL_ClipTraceToPlayers(), void,
	const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr)
#endif
{
	CALL_ORIGINAL(vecAbsStart, vecAbsEnd, mask, filter, tr);

	if (G::DebugVisuals)
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vecAbsStart.x, vecAbsStart.y, vecAbsStart.z - 1, tr->endpos.x, tr->endpos.y, tr->endpos.z - 1, 255, 0, 255, 0, G::DrawDuration ? G::DrawDuration : 4).c_str(), s_pPlayer);
}