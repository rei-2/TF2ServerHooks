#pragma once
#include "CEconEntity.h"
#include "../../../Utils/Signatures/Signatures.h"

#if x86
MAKE_SIGNATURE(CBaseCombatWeapon_HasAmmo, "server.dll", "56 8B F1 83 BE ? ? ? ? ? 75 ? 83 BE ? ? ? ? ? 74", 0x0);
#else
MAKE_SIGNATURE(CBaseCombatWeapon_HasAmmo, "server.dll", "40 53 48 83 EC ? 83 B9 ? ? ? ? ? 48 8B D9 75 ? 83 B9 ? ? ? ? ? 74", 0x0);
#endif

class CBaseCombatWeapon : public CEconEntity
{
public:
	NETVAR(m_iClip1, int, "CBaseCombatWeapon", "m_iClip1");
	NETVAR(m_iClip2, int, "CBaseCombatWeapon", "m_iClip2");
	NETVAR(m_iPrimaryAmmoType, int, "CBaseCombatWeapon", "m_iPrimaryAmmoType");
	NETVAR(m_iSecondaryAmmoType, int, "CBaseCombatWeapon", "m_iSecondaryAmmoType");
	NETVAR(m_nViewModelIndex, int, "CBaseCombatWeapon", "m_nViewModelIndex");
	NETVAR(m_bFlipViewModel, bool, "CBaseCombatWeapon", "m_bFlipViewModel");
	NETVAR(m_flNextPrimaryAttack, float, "CBaseCombatWeapon", "m_flNextPrimaryAttack");
	NETVAR(m_flNextSecondaryAttack, float, "CBaseCombatWeapon", "m_flNextSecondaryAttack");
	NETVAR(m_nNextThinkTick, int, "CBaseCombatWeapon", "m_nNextThinkTick");
	NETVAR(m_flTimeWeaponIdle, float, "CBaseCombatWeapon", "m_flTimeWeaponIdle");
	NETVAR(m_iViewModelIndex, int, "CBaseCombatWeapon", "m_iViewModelIndex");
	NETVAR(m_iWorldModelIndex, int, "CBaseCombatWeapon", "m_iWorldModelIndex");
	NETVAR(m_iState, int, "CBaseCombatWeapon", "m_iState");
	NETVAR(m_hOwner, EHANDLE, "CBaseCombatWeapon", "m_hOwner");

	NETVAR_OFF(m_bInReload, bool, "CBaseCombatWeapon", "m_flNextPrimaryAttack", 12);

	VIRTUAL(GetName, const char*, const char*(*)(void*), this, 332);

	inline bool HasAmmo()
	{
#if x86
		return reinterpret_cast<bool(__fastcall*)(CBaseCombatWeapon*)>(S::CBaseCombatWeapon_HasAmmo())(this);
#else
		return S::CBaseCombatWeapon_HasAmmo.Call<bool>(this);
#endif
	}
};