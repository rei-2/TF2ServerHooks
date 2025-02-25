#pragma once
#include "CGameTrace.h"
#include "../Types.h"
#include "../../../Utils/Signatures/Signatures.h"

#if x86
MAKE_SIGNATURE(CCollisionProperty_SetCollisionBounds, "server.dll", "55 8B EC 83 EC ? 53 8B 5D ? 56 8B F1 F3 0F 10 4E", 0x0);
#else
MAKE_SIGNATURE(CCollisionProperty_SetCollisionBounds, "server.dll", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 81 EC ? ? ? ? F3 0F 10 0A", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CCollisionProperty_CalcNearestPoint, "server.dll", "55 8B EC 83 EC ? 8D 45 ? 56 50 FF 75 ? 8B F1 E8 ? ? ? ? 8D 45", 0x0);
#else
MAKE_SIGNATURE(CCollisionProperty_CalcNearestPoint, "server.dll", "48 89 5C 24 ? 57 48 83 EC ? 49 8B D8 48 8B F9 4C 8D 44 24", 0x0);
#endif

struct model_t;

class ICollideable
{
public:
	virtual void* GetEntityHandle() = 0;
	virtual const Vec3& OBBMinsPreScaled() const = 0;
	virtual const Vec3& OBBMaxsPreScaled() const = 0;
	virtual const Vec3& OBBMins() const = 0;
	virtual const Vec3& OBBMaxs() const = 0;
	virtual void			WorldSpaceTriggerBounds(Vec3* pVecWorldMins, Vec3* pVecWorldMaxs) const = 0;
	virtual bool			TestCollision(const Ray_t& ray, unsigned int fContentsMask, CGameTrace& tr) = 0;
	virtual bool			TestHitboxes(const Ray_t& ray, unsigned int fContentsMask, CGameTrace& tr) = 0;
	virtual int				GetCollisionModelIndex() = 0;
	virtual const model_t* GetCollisionModel() = 0;
	virtual const Vec3& GetCollisionOrigin() const = 0;
	virtual const Vec3& GetCollisionAngles() const = 0;
	virtual const matrix3x4& CollisionToWorldTransform() const = 0;
	virtual SolidType_t		GetSolid() const = 0;
	virtual int				GetSolidFlags() const = 0;
	virtual void* GetIClientUnknown() = 0;
	virtual int				GetCollisionGroup() const = 0;
	virtual void			WorldSpaceSurroundingBounds(Vec3* pVecMins, Vec3* pVecMaxs) = 0;
	virtual bool			ShouldTouchTrigger(int triggerSolidFlags) const = 0;
	virtual const matrix3x4* GetRootParentToWorldTransform() const = 0;
};

class CCollisionProperty : public ICollideable
{
public:
	inline void SetCollisionBounds(const Vec3& mins, const Vec3& maxs)
	{
#if x86
		reinterpret_cast<void(__fastcall*)(CCollisionProperty*, const Vec3&, const Vec3&)>(S::CCollisionProperty_SetCollisionBounds())(this, mins, maxs);
#else
		S::CCollisionProperty_SetCollisionBounds.Call<void>(this, std::ref(mins), std::ref(maxs));
#endif
	}

	inline void CalcNearestPoint(const Vec3& vecWorldPt, Vec3* pVecNearestWorldPt)
	{
#if x86
		reinterpret_cast<void(__fastcall*)(CCollisionProperty*, const Vec3&, Vec3*)>(S::CCollisionProperty_CalcNearestPoint())(this, vecWorldPt, pVecNearestWorldPt);
#else
		S::CCollisionProperty_CalcNearestPoint.Call<void>(this, std::ref(vecWorldPt), pVecNearestWorldPt);
#endif
	}
};