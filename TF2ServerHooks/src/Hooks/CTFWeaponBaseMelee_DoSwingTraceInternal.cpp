#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CTFWeaponBaseMelee_DoSwingTraceInternal, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 56 8B F1 89 75", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBaseMelee_DoSwingTraceInternal, "server.dll", "48 89 74 24 ? 55 57 41 55 41 56 41 57 48 8D AC 24", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFWeaponBaseMelee_Smack_DoSwingTraceInternal_Call, "server.dll", "84 C0 74 ? 85 F6 7E", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBaseMelee_Smack_DoSwingTraceInternal_Call, "server.dll", "48 8B 6C 24 ? 84 C0 74 ? 85 DB", 0x0);
#endif

#if x86
MAKE_HOOK(CTFWeaponBaseMelee_DoSwingTraceInternal, S::CTFWeaponBaseMelee_DoSwingTraceInternal(), bool, __fastcall,
	void* ecx, void* edx, trace_t& trace, bool bCleave, CUtlVector<trace_t>* pTargetTraceVector)
#else
MAKE_HOOK(CTFWeaponBaseMelee_DoSwingTraceInternal, S::CTFWeaponBaseMelee_DoSwingTraceInternal(), bool,
	void* rcx, trace_t& trace, bool bCleave, CUtlVector<trace_t>* pTargetTraceVector)
#endif
{
	static const auto dwDesired = S::CTFWeaponBaseMelee_Smack_DoSwingTraceInternal_Call();
	const auto dwRetAddr = uintptr_t(_ReturnAddress());

	if (G::DebugVisuals && dwRetAddr == dwDesired)
	{
#if x86
		auto pWeapon = reinterpret_cast<CTFWeaponBase*>(ecx);
#else
		auto pWeapon = reinterpret_cast<CTFWeaponBase*>(rcx);
#endif

		if (auto pPlayer = pWeapon->m_hOwner().Get()->As<CTFPlayer>())
		{
			G::DebugTarget = pPlayer;

			float flRange = SDK::AttribHookValue(pWeapon->GetSwingRange(), "melee_range_multiplier", pWeapon);
			float flHull = SDK::AttribHookValue(18, "melee_bounds_multiplier", pWeapon);

			Vec3 vForward; Math::AngleVectors(pPlayer->EyeAngles(), &vForward);
			Vec3 vStart; pPlayer->EyePosition(vStart);
			Vec3 vEnd = vStart + vForward * flRange;

			SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, 0, 0, 255, 0, 4.f).c_str(), G::DebugTarget);
			SDK::OutputClient("Box", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, -flHull, -flHull, -flHull, flHull, flHull, flHull, 0, 0, 0, 0, 0, 255, 0, 4).c_str(), G::DebugTarget);
			SDK::OutputClient("Box", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", vEnd.x, vEnd.y, vEnd.z, -flHull, -flHull, -flHull, flHull, flHull, flHull, 0, 0, 0, 0, 0, 255, 0, 4).c_str(), G::DebugTarget);
		}
	}

#if x86
	return CALL_ORIGINAL(ecx, edx, trace, bCleave, pTargetTraceVector);
#else
	return CALL_ORIGINAL(rcx, trace, bCleave, pTargetTraceVector);
#endif
}