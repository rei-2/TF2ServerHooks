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

static Vec3 vStart = {}, vEnd = {};

#if x86
MAKE_HOOK(CTFPlayer_FireBullet, S::CTFPlayer_FireBullet(), void, __fastcall,
	void* ecx, void* edx, CTFWeaponBase* pWpn, const FireBulletsInfo_t& info, bool bDoEffects, int nDamageType, int nCustomDamageType)
#else
MAKE_HOOK(CTFPlayer_FireBullet, S::CTFPlayer_FireBullet(), void,
	void* rcx, CTFWeaponBase* pWpn, const FireBulletsInfo_t& info, bool bDoEffects, int nDamageType, int nCustomDamageType)
#endif
{
	vStart = info.m_vecSrc;
	vEnd = vStart + info.m_vecDirShooting * info.m_flDistance;
#if x86
	CALL_ORIGINAL(ecx, edx, pWpn, info, bDoEffects, nDamageType, nCustomDamageType);
#else
	CALL_ORIGINAL(rcx, pWpn, info, bDoEffects, nDamageType, nCustomDamageType);
#endif

	if (G::DebugVisuals)
#if x86
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, 0, 0, 255, 0, 4.f).c_str(), reinterpret_cast<CTFPlayer*>(ecx));
#else
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, 0, 0, 255, 0, 4.f).c_str(), reinterpret_cast<CTFPlayer*>(rcx));
#endif
}

#if x86
MAKE_HOOK(UTIL_PlayerBulletTrace, S::UTIL_PlayerBulletTrace(), void, __cdecl,
	const Vector& vecAbsStart, const Vector& vecAbsEnd, void* unknown, unsigned int mask, ITraceFilter* pFilter, trace_t* ptr)
#else
MAKE_HOOK(UTIL_PlayerBulletTrace, S::UTIL_PlayerBulletTrace(), void,
	const Vector& vecAbsStart, const Vector& vecAbsEnd, void* unknown, unsigned int mask, ITraceFilter* pFilter, trace_t* ptr)
#endif
{
	CALL_ORIGINAL(vecAbsStart, vecAbsEnd, unknown, mask, pFilter, ptr);

	vEnd = ptr->endpos;
}