#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CTFProjectile_Arrow_ArrowTouch, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 56 57 8B F9 F3 0F 10 40", 0x0);
#else
MAKE_SIGNATURE(CTFProjectile_Arrow_ArrowTouch, "server.dll", "48 89 4C 24 ? 55 56 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05", 0x0);
#endif

#if x86
MAKE_HOOK(CTFProjectile_Arrow_ArrowTouch, S::CTFProjectile_Arrow_ArrowTouch(), void, __fastcall,
	void* ecx, void* edx, CBaseEntity* pOther)
#else
MAKE_HOOK(CTFProjectile_Arrow_ArrowTouch, S::CTFProjectile_Arrow_ArrowTouch(), void,
	void* rcx, CBaseEntity* pOther)
#endif
{
#if !x86
	if (G::DebugVisuals && pOther && pOther->IsPlayer())
	{
		auto pArrow = reinterpret_cast<CBaseEntity*>(rcx);
		auto pWeapon = reinterpret_cast<CTFBaseRocket*>(rcx)->m_hLauncher().Get();
		auto pOwner = pWeapon ? pWeapon->As<CTFWeaponBase>()->m_hOwner().Get() : nullptr;

		if (pOwner && pOwner->IsPlayer())
		{
			G::DrawBoundingBox = true, G::DrawHeadOnly = true;
			G::DebugTarget = pOwner->As<CBasePlayer>();
			pOther->As<CTFPlayer>()->DrawServerHitboxes(5.f);
			G::NoBoxAngles = true;
			pOther->As<CTFPlayer>()->DrawServerHitboxes(5.f);
			G::NoBoxAngles = false;
			G::DrawBoundingBox = false, G::DrawHeadOnly = false;

			Vec3 origin = pArrow->m_vecOrigin();
			Vec3 mins = pArrow->m_vecMins();
			Vec3 maxs = pArrow->m_vecMaxs();
			Vec3 angles = {};
			int r = 255, g = 127, b = 127, a = 0;
			float duration = 5.f;

			SDK::OutputClient("Box", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", origin.x, origin.y, origin.z, mins.x, mins.y, mins.z, maxs.x, maxs.y, maxs.z, angles.x, angles.y, angles.z, r, g, b, a, duration).c_str(), G::DebugTarget);
		}
	}
#endif

#if x86
	CALL_ORIGINAL(ecx, edx, pOther);
#else
	CALL_ORIGINAL(rcx, pOther);
#endif
}