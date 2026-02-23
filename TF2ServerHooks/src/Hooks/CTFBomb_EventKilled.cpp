#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CTFGenericBomb_EventKilled, "server.dll", "55 8B EC 81 EC ? ? ? ? 53 56 57 8B F9 80 BF ? ? ? ? ? 0F 85", 0x0);
#else
MAKE_SIGNATURE(CTFGenericBomb_EventKilled, "server.dll", "48 8B C4 55 57 41 56 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 80 B9", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFPumpkinBomb_EventKilled, "server.dll", "55 8B EC 81 EC ? ? ? ? 53 56 8B F1 57 89 75", 0x0);
#else
MAKE_SIGNATURE(CTFPumpkinBomb_EventKilled, "server.dll", "48 8B C4 55 57 41 55 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 80 B9", 0x0);
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

	Vector			m_vecDamageForce;
	Vector			m_vecDamagePosition;
	Vector			m_vecReportedPosition;	// Position players are told damage is coming from
	EHANDLE			m_hInflictor;
	EHANDLE			m_hAttacker;
	EHANDLE			m_hWeapon;
	float			m_flDamage;
	float			m_flMaxDamage;
	float			m_flBaseDamage;			// The damage amount before skill leve adjustments are made. Used to get uniform damage forces.
	int				m_bitsDamageType;
	int				m_iDamageCustom;
	int				m_iDamageStats;
	int				m_iAmmoType;			// AmmoType of the weapon used to cause this damage, if any
	int				m_iDamagedOtherPlayers;
	int				m_iPlayerPenetrationCount;
	float			m_flDamageBonus;		// Anything that increases damage (crit) - store the delta
	EHANDLE			m_hDamageBonusProvider;	// Who gave us the ability to do extra damage?
	bool			m_bForceFriendlyFire;	// Ideally this would be a dmg type, but we can't add more
	float			m_flDamageForForce;
	ECritType		m_eCritType;
};

#if x86
MAKE_HOOK(CTFGenericBomb_EventKilled, S::CTFGenericBomb_EventKilled(), void, __fastcall,
	void* ecx, void* edx, const CTakeDamageInfo& info)
#else
MAKE_HOOK(CTFGenericBomb_EventKilled, S::CTFGenericBomb_EventKilled(), void,
	void* rcx, const CTakeDamageInfo& info)
#endif
{
	if (G::DebugInfo)
#if x86
		SDK::Output("Radius", std::format("{}", *reinterpret_cast<float*>(uintptr_t(ecx) + 1240)).c_str());
#else
		SDK::Output("Radius", std::format("{}", *reinterpret_cast<float*>(uintptr_t(rcx) + 1568)).c_str());
#endif

#if x86
	CALL_ORIGINAL(ecx, edx, info);
#else
	CALL_ORIGINAL(rcx, info);
#endif
}

#if x86
MAKE_HOOK(CTFPumpkinBomb_EventKilled, S::CTFPumpkinBomb_EventKilled(), void, __fastcall,
	void* ecx, void* edx, const CTakeDamageInfo& info)
#else
MAKE_HOOK(CTFPumpkinBomb_EventKilled, S::CTFPumpkinBomb_EventKilled(), void,
	void* rcx, const CTakeDamageInfo& info)
#endif
{
	if (G::DebugInfo)
#if x86
		SDK::Output("Radius", std::format("{}", *reinterpret_cast<float*>(uintptr_t(ecx) + 1216)).c_str());
#else
		SDK::Output("Radius", std::format("{}", *reinterpret_cast<float*>(uintptr_t(rcx) + 1536)).c_str());
#endif

#if x86
	CALL_ORIGINAL(ecx, edx, info);
#else
	CALL_ORIGINAL(rcx, info);
#endif
}