#pragma once
#include "CBaseEntity.h"
#include "../Misc/Studio.h"
#include "../../../Utils/Math/Math.h"

MAKE_SIGNATURE(CBaseAnimating_GetBonePosition, "server.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 B9 ? ? ? ? ? 49 8B F1", 0x0);

class CBaseAnimating : public CBaseEntity
{
public:
	NETVAR(m_nSequence, int, "CBaseAnimating", "m_nSequence");
	NETVAR(m_nForceBone, int, "CBaseAnimating", "m_nForceBone");
	NETVAR(m_vecForce, Vec3, "CBaseAnimating", "m_vecForce");
	NETVAR(m_nSkin, int, "CBaseAnimating", "m_nSkin");
	NETVAR(m_nBody, int, "CBaseAnimating", "m_nBody");
	NETVAR(m_nHitboxSet, int, "CBaseAnimating", "m_nHitboxSet");
	NETVAR(m_flModelScale, float, "CBaseAnimating", "m_flModelScale");
	NETVAR(m_flModelWidthScale, float, "CBaseAnimating", "m_flModelWidthScale");
	NETVAR(m_flPlaybackRate, float, "CBaseAnimating", "m_flPlaybackRate");
	NETVAR(m_flEncodedController, void*, "CBaseAnimating", "m_flEncodedController");
	NETVAR(m_bClientSideAnimation, bool, "CBaseAnimating", "m_bClientSideAnimation");
	NETVAR(m_bClientSideFrameReset, bool, "CBaseAnimating", "m_bClientSideFrameReset");
	NETVAR(m_nNewSequenceParity, int, "CBaseAnimating", "m_nNewSequenceParity");
	NETVAR(m_nResetEventsParity, int, "CBaseAnimating", "m_nResetEventsParity");
	NETVAR(m_nMuzzleFlashParity, int, "CBaseAnimating", "m_nMuzzleFlashParity");
	NETVAR(m_hLightingOrigin, EHANDLE, "CBaseAnimating", "m_hLightingOrigin");
	NETVAR(m_hLightingOriginRelative, EHANDLE, "CBaseAnimating", "m_hLightingOriginRelative");
	NETVAR(m_flCycle, float, "CBaseAnimating", "m_flCycle");
	NETVAR(m_fadeMinDist, float, "CBaseAnimating", "m_fadeMinDist");
	NETVAR(m_fadeMaxDist, float, "CBaseAnimating", "m_fadeMaxDist");
	NETVAR(m_flFadeScale, float, "CBaseAnimating", "m_flFadeScale");

	NETVAR_OFF(GetModelPtr, CStudioHdr*, "CBaseAnimating", "m_nMuzzleFlashParity", 12);

	inline void SetupBones(matrix3x4* pBoneToWorld, int boneMask)
	{
		reinterpret_cast<void(*)(void*, matrix3x4*, int)>(U::Memory.GetVFunc(this, 210))(this, pBoneToWorld, boneMask);
	}

	inline int GetHitboxGroup(int nHitbox)
	{
		auto pModel = I::ModelInfoServer->GetModel(GetModelIndex());
		if (!pModel) return -1;
		auto pHDR = I::ModelInfoServer->GetStudiomodel(pModel);
		if (!pHDR) return -1;
		auto pSet = pHDR->pHitboxSet(m_nHitboxSet());
		if (!pSet) return -1;
		auto pBox = pSet->pHitbox(nHitbox);
		if (!pBox) return -1;

		return pBox->group;
	}

	inline int GetNumOfHitboxes()
	{
		auto pModel = I::ModelInfoServer->GetModel(GetModelIndex());
		if (!pModel) return 0;
		auto pHDR = I::ModelInfoServer->GetStudiomodel(pModel);
		if (!pHDR) return 0;
		auto pSet = pHDR->pHitboxSet(m_nHitboxSet());
		if (!pSet) return 0;

		return pSet->numhitboxes;
	}

	inline Vec3 GetHitboxOrigin(int nHitbox, Vec3 vOffset = {})
	{
		auto pModel = I::ModelInfoServer->GetModel(GetModelIndex());
		if (!pModel) return {};
		auto pHDR = I::ModelInfoServer->GetStudiomodel(pModel);
		if (!pHDR) return {};
		auto pSet = pHDR->pHitboxSet(m_nHitboxSet());
		if (!pSet) return {};
		auto pBox = pSet->pHitbox(nHitbox);
		if (!pBox) return {};

		matrix3x4 aBones[MAXSTUDIOBONES] = {};
		SetupBones(aBones, BONE_USED_BY_ANYTHING);

		Vec3 vOut = {};
		Math::VectorTransform(vOffset, aBones[pBox->bone], vOut);
		return vOut;
	}

	inline Vec3 GetHitboxCenter(int nHitbox, Vec3 vOffset = {})
	{
		auto pModel = I::ModelInfoServer->GetModel(GetModelIndex());
		if (!pModel) return {};
		auto pHDR = I::ModelInfoServer->GetStudiomodel(pModel);
		if (!pHDR) return {};
		auto pSet = pHDR->pHitboxSet(m_nHitboxSet());
		if (!pSet) return {};
		auto pBox = pSet->pHitbox(nHitbox);
		if (!pBox) return {};

		matrix3x4 aBones[MAXSTUDIOBONES] = {};
		SetupBones(aBones, BONE_USED_BY_ANYTHING);

		Vec3 vOut = {};
		Math::VectorTransform((pBox->bbmin + pBox->bbmax) / 2 + vOffset, aBones[pBox->bone], vOut);
		return vOut;
	}

	inline void GetHitboxInfo(int nHitbox, Vec3* pCenter = nullptr, Vec3* pMins = nullptr, Vec3* pMaxs = nullptr, matrix3x4* pMatrix = nullptr, Vec3 vOffset = {})
	{
		auto pModel = I::ModelInfoServer->GetModel(GetModelIndex());
		if (!pModel) return;
		auto pHDR = I::ModelInfoServer->GetStudiomodel(pModel);
		if (!pHDR) return;
		auto pSet = pHDR->pHitboxSet(m_nHitboxSet());
		if (!pSet) return;
		auto pBox = pSet->pHitbox(nHitbox);
		if (!pBox) return;

		matrix3x4 aBones[MAXSTUDIOBONES] = {};
		SetupBones(aBones, BONE_USED_BY_ANYTHING);

		if (pMins)
			*pMins = pBox->bbmin;

		if (pMaxs)
			*pMaxs = pBox->bbmax;

		if (pCenter)
			Math::VectorTransform(vOffset, aBones[pBox->bone], *pCenter);

		if (pMatrix)
			memcpy(*pMatrix, aBones[pBox->bone], sizeof(matrix3x4));
	}

	inline std::array<float, 24>& m_flPoseParameter()
	{
		static int nOffset = U::NetVars.GetNetVar("CBaseAnimating", "m_flPoseParameter");
		return *reinterpret_cast<std::array<float, 24>*>(uintptr_t(this) + nOffset);
	}

	inline CUtlVector<matrix3x4>* GetCachedBoneData()
	{
		static int nOffset = U::NetVars.GetNetVar("CBaseAnimating", "m_hLightingOrigin") - 88;
		return reinterpret_cast<CUtlVector<matrix3x4>*>(uintptr_t(this) + nOffset);
	}

	inline void GetBonePosition(int iBone, Vector& origin, QAngle& angles)
	{
		S::CBaseAnimating_GetBonePosition.Call<void>(this, iBone, std::ref(origin), std::ref(angles));
	}

	inline bool GetAttachment(int number, Vec3& origin)
	{
		return reinterpret_cast<bool(*)(void*, int, Vec3&)>(U::Memory.GetVFunc(this, 71))(this, number, origin);
	}
};

class CBaseAnimatingOverlay : public CBaseAnimating
{
public:

};

class CCurrencyPack : public CBaseAnimating
{
public:
	NETVAR(m_bDistributed, bool, "CCurrencyPack", "m_bDistributed");
};