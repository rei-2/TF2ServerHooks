#pragma once
#include "../../Definitions/Interfaces/IEngineTrace.h"
#include "../../Definitions/Main/CTFPlayer.h"
#include "../../Definitions/Main/CTFWeaponBase.h"

class CTraceFilterHitscan : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int nContentsMask) override;
	TraceType_t GetTraceType() const override;
	CBaseEntity* pSkip = nullptr;
	CTFPlayer* pPlayer = nullptr;
	CTFWeaponBase* pWeapon = nullptr;
};

class CTraceFilterProjectile : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int nContentsMask) override;
	TraceType_t GetTraceType() const override;
	CBaseEntity* pSkip = nullptr;
	CTFPlayer* pPlayer = nullptr;
	CTFWeaponBase* pWeapon = nullptr;
};

class CTraceFilterWorldAndPropsOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pServerEntity, int nContentsMask) override;
	TraceType_t GetTraceType() const override;
	CBaseEntity* pSkip = nullptr;
};