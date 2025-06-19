#include "../SDK/SDK.h"

class CFlaggedEntitiesEnum : public IPartitionEnumerator
{
public:
	CBaseEntity** m_pList;
	int m_listMax;
	int m_flagMask;
	int m_count;
};

#if x86
MAKE_SIGNATURE(UTIL_EntitiesInSphere, "server.dll", "55 8B EC 8B 0D ? ? ? ? D9 45 ? 56 8B 75", 0x0);
#else
MAKE_SIGNATURE(UTIL_EntitiesInSphere, "server.dll", "40 53 48 83 EC ? 48 8B 05 ? ? ? ? 49 8B D8 4C 8B C1", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFWeaponBase_DeflectProjectiles, "server.dll", "55 8B EC 81 EC ? ? ? ? 53 57 6A ? 68", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBase_DeflectProjectiles, "server.dll", "40 57 41 56 48 81 EC ? ? ? ? 4C 8B F1", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFWeaponBase_DeflectProjectiles_EntitiesInSphere_Call, "server.dll", "83 C4 ? 89 45 ? 8B CF C6 45", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBase_DeflectProjectiles_EntitiesInSphere_Call, "server.dll", "48 8B CF 48 63 D8", 0x0);
#endif

#if x86
MAKE_HOOK(UTIL_EntitiesInSphere, S::UTIL_EntitiesInSphere(), int, __fastcall,
	const Vector& center, float radius, CFlaggedEntitiesEnum* pEnum)
#else
MAKE_HOOK(UTIL_EntitiesInSphere, S::UTIL_EntitiesInSphere(), int,
	const Vector& center, float radius, CFlaggedEntitiesEnum* pEnum)
#endif
{
	static const auto dwDesired = S::CTFWeaponBase_DeflectProjectiles_EntitiesInSphere_Call();
	const auto dwRetAddr = uintptr_t(_ReturnAddress());

	if (dwRetAddr != dwDesired || !G::DebugVisuals)
		return CALL_ORIGINAL(center, radius, pEnum);

	int iReturn = CALL_ORIGINAL(center, radius, pEnum);

	SDK::OutputClient("Box", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", center.x, center.y, center.z, -radius, -radius, -radius, radius, radius, radius, 0, 0, 0, 0, 0, 255, 0, 4).c_str(), G::DebugTarget);
	std::unordered_map<CBaseEntity*, bool> mEntities = {};
	for (int i = 0; i < iReturn; i++)
	{
		auto pEntity = pEnum->m_pList[i];
		if (!pEntity->IsProjectile())
			continue;

		mEntities[pEntity] = true;

		Vec3 vOrigin = pEntity->m_vecOrigin();
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vOrigin.x + 10, vOrigin.y, vOrigin.z, 0, 255, 255, 0, 4.f).c_str(), G::DebugTarget);
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vOrigin.x, vOrigin.y + 10, vOrigin.z, 255, 0, 255, 0, 4.f).c_str(), G::DebugTarget);
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vOrigin.x, vOrigin.y, vOrigin.z + 10, 255, 255, 0, 0, 4.f).c_str(), G::DebugTarget);
	}
	for (CBaseEntity* pEntity = I::GlobalEntityList->FirstEnt(); pEntity; pEntity = I::GlobalEntityList->NextEnt(pEntity))
	{
		if (!pEntity->IsProjectile() || mEntities.contains(pEntity))
			continue;

		Vec3 vOrigin = pEntity->m_vecOrigin();
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vOrigin.x - 10, vOrigin.y, vOrigin.z, 0, 0, 0, 0, 4.f).c_str(), G::DebugTarget);
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vOrigin.x, vOrigin.y - 10, vOrigin.z, 0, 0, 0, 0, 4.f).c_str(), G::DebugTarget);
		SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vOrigin.x, vOrigin.y, vOrigin.z, vOrigin.x, vOrigin.y, vOrigin.z - 10, 0, 0, 0, 0, 4.f).c_str(), G::DebugTarget);
	}

	return iReturn;
}

#if x86
MAKE_HOOK(CTFWeaponBase_DeflectProjectiles, S::CTFWeaponBase_DeflectProjectiles(), bool, __fastcall,
	void* ecx, void* edx)
#else
MAKE_HOOK(CTFWeaponBase_DeflectProjectiles, S::CTFWeaponBase_DeflectProjectiles(), bool,
	void* rcx)
#endif
{
#if x86
	G::DebugTarget = reinterpret_cast<CTFPlayer*>(ecx);
#else
	G::DebugTarget = reinterpret_cast<CTFPlayer*>(rcx);
#endif

#if x86
	return CALL_ORIGINAL(ecx, edx);
#else
	return CALL_ORIGINAL(rcx);
#endif
}