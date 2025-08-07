#pragma once
#include "CBaseHandle.h"
#include "IServerEntity.h"
#include "CCollisionProperty.h"
#include "CParticleProperty.h"
#include "../Main/UtlVector.h"
#include "../Definitions.h"
#include "../../../Utils/NetVars/NetVars.h"
#include "../../../Utils/Signatures/Signatures.h"
#include "../../../Utils/Memory/Memory.h"

#if x86
MAKE_SIGNATURE(CBaseEntity_SetAbsOrigin, "server.dll", "55 8B EC 83 EC ? 56 57 8B 7D ? 8B F1 E8", 0x0);
#else
MAKE_SIGNATURE(CBaseEntity_SetAbsOrigin, "server.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B FA 48 8B D9 E8 ? ? ? ? F3 0F 10 83", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CBaseEntity_SetAbsAngles, "server.dll", "55 8B EC 83 EC ? 53 8B 5D ? 56 8B F1 E8", 0x0);
#else
MAKE_SIGNATURE(CBaseEntity_SetAbsAngles, "server.dll", "40 53 56 48 81 EC ? ? ? ? 48 8B F2", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CBaseEntity_SetAbsVelocity, "server.dll", "55 8B EC 83 EC ? 53 56 8B 75 ? 8B D9 F3 0F 10 06", 0x0);
#else
MAKE_SIGNATURE(CBaseEntity_SetAbsVelocity, "server.dll", "48 89 74 24 ? 57 48 83 EC ? F3 0F 10 81 ? ? ? ? 48 8B F2 0F 2E 02", 0x0);
#endif

enum CollideType_t
{
	ENTITY_SHOULD_NOT_COLLIDE = 0,
	ENTITY_SHOULD_COLLIDE,
	ENTITY_SHOULD_RESPOND
};

typedef CHandle<CBaseEntity> EHANDLE;

#define MULTIPLAYER_BACKUP 90

class IInterpolatedVar;

class VarMapEntry_t
{
public:
	unsigned short type;
	unsigned short m_bNeedsToInterpolate;
	void* data;
	IInterpolatedVar* watcher;
};

struct VarMapping_t
{
	CUtlVector<VarMapEntry_t> m_Entries;
	int m_nInterpolatedEntries;
	float m_lastInterpolationTime;
};

class CBaseEntity : public IServerEntity
{
public:
	NETVAR(m_flAnimTime, float, "CBaseEntity", "m_flAnimTime");
	NETVAR(m_flSimulationTime, float, "CBaseEntity", "m_flSimulationTime");
	NETVAR(m_ubInterpolationFrame, int, "CBaseEntity", "m_ubInterpolationFrame");
	NETVAR(m_vecOrigin, Vec3, "CBaseEntity", "m_vecOrigin");
	NETVAR(m_angRotation, Vec3, "CBaseEntity", "m_angRotation");
	NETVAR(m_nModelIndex, int, "CBaseEntity", "m_nModelIndex");
	NETVAR(m_fEffects, int, "CBaseEntity", "m_fEffects");
	NETVAR(m_nRenderMode, int, "CBaseEntity", "m_nRenderMode");
	NETVAR(m_nRenderFX, int, "CBaseEntity", "m_nRenderFX");
	NETVAR(m_clrRender, Color_t, "CBaseEntity", "m_clrRender");
	NETVAR(m_iTeamNum, int, "CBaseEntity", "m_iTeamNum");
	NETVAR(m_CollisionGroup, int, "CBaseEntity", "m_CollisionGroup");
	NETVAR(m_flElasticity, float, "CBaseEntity", "m_flElasticity");
	NETVAR(m_flShadowCastDistance, float, "CBaseEntity", "m_flShadowCastDistance");
	NETVAR(m_hOwnerEntity, EHANDLE, "CBaseEntity", "m_hOwnerEntity");
	NETVAR(m_hEffectEntity, EHANDLE, "CBaseEntity", "m_hEffectEntity");
	NETVAR(moveparent, int, "CBaseEntity", "moveparent");
	NETVAR(m_iParentAttachment, int, "CBaseEntity", "m_iParentAttachment");
	NETVAR(m_Collision, CCollisionProperty*, "CBaseEntity", "m_Collision");
	NETVAR(m_vecMinsPreScaled, Vec3, "CBaseEntity", "m_vecMinsPreScaled");
	NETVAR(m_vecMaxsPreScaled, Vec3, "CBaseEntity", "m_vecMaxsPreScaled");
	NETVAR(m_vecMins, Vec3, "CBaseEntity", "m_vecMins");
	NETVAR(m_vecMaxs, Vec3, "CBaseEntity", "m_vecMaxs");
	NETVAR(m_nSolidType, int, "CBaseEntity", "m_nSolidType");
	NETVAR(m_usSolidFlags, int, "CBaseEntity", "m_usSolidFlags");
	NETVAR(m_nSurroundType, int, "CBaseEntity", "m_nSurroundType");
	NETVAR(m_triggerBloat, int, "CBaseEntity", "m_triggerBloat");
	NETVAR(m_bUniformTriggerBloat, bool, "CBaseEntity", "m_bUniformTriggerBloat");
	NETVAR(m_vecSpecifiedSurroundingMinsPreScaled, Vec3, "CBaseEntity", "m_vecSpecifiedSurroundingMinsPreScaled");
	NETVAR(m_vecSpecifiedSurroundingMaxsPreScaled, Vec3, "CBaseEntity", "m_vecSpecifiedSurroundingMaxsPreScaled");
	NETVAR(m_vecSpecifiedSurroundingMins, Vec3, "CBaseEntity", "m_vecSpecifiedSurroundingMins");
	NETVAR(m_vecSpecifiedSurroundingMaxs, Vec3, "CBaseEntity", "m_vecSpecifiedSurroundingMaxs");
	NETVAR(m_iTextureFrameIndex, int, "CBaseEntity", "m_iTextureFrameIndex");
	NETVAR(m_PredictableID, int, "CBaseEntity", "m_PredictableID");
	NETVAR(m_bIsPlayerSimulated, bool, "CBaseEntity", "m_bIsPlayerSimulated");
	NETVAR(m_bSimulatedEveryTick, bool, "CBaseEntity", "m_bSimulatedEveryTick");
	NETVAR(m_bAnimatedEveryTick, bool, "CBaseEntity", "m_bAnimatedEveryTick");
	NETVAR(m_bAlternateSorting, bool, "CBaseEntity", "m_bAlternateSorting");
	NETVAR(m_nModelIndexOverrides, void*, "CBaseEntity", "m_nModelIndexOverrides");
	NETVAR(movetype, int, "CBaseEntity", "movetype");
	
	NETVAR_OFF(m_flOldSimulationTime, float, "CBaseEntity", "m_flSimulationTime", 4);
	NETVAR_OFF(m_Particles, CParticleProperty*, "CBaseEntity", "m_flElasticity", -56);

	VIRTUAL_ARGS(EyePosition, Vec3&, Vec3&(*)(void*, Vec3&), 137, this, (Vec3& vPosition), this, vPosition);
	VIRTUAL(EyeAngles, Vec3&, Vec3&(*)(void*), 138, this);
	VIRTUAL(UpdateVisibility, void, void(*)(CBaseEntity*), 91, this);

	inline int entindex()
	{
#if x86
		void* m_Network = *reinterpret_cast<void**>(uintptr_t(this) + 24);
#else
		void* m_Network = *reinterpret_cast<void**>(uintptr_t(this) + 48);
#endif
		if (m_Network)
			return *reinterpret_cast<short*>(uintptr_t(m_Network) + 6);
		return 0;
	}

	inline Vec3 GetCenter()
	{
		return m_vecOrigin() + (m_vecMins() + m_vecMaxs()) / 2;
	}

	inline bool IsInValidTeam(int* pTeamNumOut = nullptr)
	{
		int nTeamNum = m_iTeamNum();

		switch (nTeamNum)
		{
		case TF_TEAM_RED:
		case TF_TEAM_BLUE:
		{
			if (pTeamNumOut)
				*pTeamNumOut = nTeamNum;

			return true;
		}

		default: return false;
		}
	}

	inline CBaseEntity* GetMoveParent()
	{
		static int nOffset = U::NetVars.GetNetVar("CBaseEntity", "moveparent") - 8;
		auto m_pMoveParent = reinterpret_cast<EHANDLE*>(uintptr_t(this) + nOffset);

		if (!m_pMoveParent)
			return nullptr;

		return m_pMoveParent->Get();
	}

	inline CBaseEntity* NextMovePeer()
	{
		static int nOffset = U::NetVars.GetNetVar("CBaseEntity", "moveparent") - 16;
		auto m_pMovePeer = reinterpret_cast<EHANDLE*>(uintptr_t(this) + nOffset);

		if (!m_pMovePeer)
			return nullptr;

		return m_pMovePeer->Get();
	}

	inline CBaseEntity* FirstMoveChild()
	{
		static int nOffset = U::NetVars.GetNetVar("CBaseEntity", "moveparent") - 24;
		auto m_pMoveChild = reinterpret_cast<EHANDLE*>(uintptr_t(this) + nOffset);

		if (!m_pMoveChild)
			return nullptr;

		return m_pMoveChild->Get();
	}

	inline void SetAbsOrigin(const Vec3& absOrigin)
	{
#if x86
		reinterpret_cast<void(__fastcall*)(CBaseEntity*, const Vec3&)>(S::CBaseEntity_SetAbsOrigin())(this, absOrigin);
#else
		S::CBaseEntity_SetAbsOrigin.Call<void>(this, std::ref(absOrigin));
#endif
	}

	inline void SetAbsAngles(const Vec3& absAngles)
	{
#if x86
		reinterpret_cast<void(__fastcall*)(CBaseEntity*, const Vec3&)>(S::CBaseEntity_SetAbsAngles())(this, absAngles);
#else
		S::CBaseEntity_SetAbsAngles.Call<void>(this, std::ref(absAngles));
#endif
	}

	inline void SetAbsVelocity(const Vec3& vecAbsVelocity)
	{
#if x86
		reinterpret_cast<void(__fastcall*)(CBaseEntity*, const Vec3&)>(S::CBaseEntity_SetAbsVelocity())(this, vecAbsVelocity);
#else
		S::CBaseEntity_SetAbsVelocity.Call<void>(this, std::ref(vecAbsVelocity));
#endif
	}
};