#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFPlayer_FireBullet, "server.dll", "48 8B C4 44 88 48 ? 4C 89 40 ? 48 89 50", 0x0);
MAKE_SIGNATURE(UTIL_PlayerBulletTrace, "server.dll", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 4C 89 6C 24 ? 55 41 56 41 57 48 8D AC 24", 0x0);

static Vec3 vStart = {}, vEnd = {};

MAKE_HOOK(CTFPlayer_FireBullet, S::CTFPlayer_FireBullet(), void,
	void* rcx, CTFWeaponBase* pWpn, const FireBulletsInfo_t& info, bool bDoEffects, int nDamageType, int nCustomDamageType)
{
	vStart = info.m_vecSrc;
	vEnd = vStart + info.m_vecDirShooting * info.m_flDistance;

	CALL_ORIGINAL(rcx, pWpn, info, bDoEffects, nDamageType, nCustomDamageType);

	if (G::DebugVisuals)
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, 0, 0, 255, 0, 4.f).c_str(), reinterpret_cast<CTFPlayer*>(rcx));
}

MAKE_HOOK(UTIL_PlayerBulletTrace, S::UTIL_PlayerBulletTrace(), void,
	const Vector& vecAbsStart, const Vector& vecAbsEnd, void* unknown, unsigned int mask, ITraceFilter* pFilter, trace_t* ptr)
{
	CALL_ORIGINAL(vecAbsStart, vecAbsEnd, unknown, mask, pFilter, ptr);

	vEnd = ptr->endpos;
}