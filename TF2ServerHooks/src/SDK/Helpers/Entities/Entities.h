#pragma once
#include "../../../Utils/Feature/Feature.h"
#include "../../Definitions/Classes.h"
#include <unordered_map>

enum struct EGroupType
{
	PLAYERS, BUILDINGS,
	PICKUPS_HEALTH, PICKUPS_AMMO, PICKUPS_MONEY, PICKUPS_POWERUP, PICKUPS_SPELLBOOK,
	WORLD_PROJECTILES, WORLD_OBJECTIVE, WORLD_NPC, WORLD_BOMBS
};

struct DormantData
{
	Vec3 Location;
	float LastUpdate = 0.f;
};

class CEntities
{
	CTFPlayerResource* m_pPlayerResource = nullptr;

	std::unordered_map<EGroupType, std::vector<CBaseEntity*>> m_mGroups = {};

	std::unordered_map<int, float> m_mSimTimes, m_mOldSimTimes, m_mDeltaTimes;
	std::unordered_map<int, int> m_mChokes, m_mSetTicks;
	std::unordered_map<int, std::pair<bool, matrix3x4[MAXSTUDIOBONES]>> m_mBones;

	bool m_bSettingUpBones = false;

public:
	void Store();
	void Clear(bool bShutdown = false);

	bool IsHealth(CBaseEntity* pEntity);
	bool IsAmmo(CBaseEntity* pEntity);
	bool IsPowerup(CBaseEntity* pEntity);
	bool IsSpellbook(CBaseEntity* pEntity);

	CTFPlayerResource* GetPR();

	const std::vector<CBaseEntity*>& GetGroup(const EGroupType& Group);

	float GetSimTime(CBaseEntity* pEntity);
	float GetOldSimTime(CBaseEntity* pEntity);
	float GetDeltaTime(int iIndex);
	int GetChoke(int iIndex);
	matrix3x4* GetBones(int iIndex);

	bool IsSettingUpBones();
};

ADD_FEATURE_CUSTOM(CEntities, Entities, H);