#pragma once
#include "../../../Utils/Macros/Macros.h"
#include "../../Definitions/Classes.h"
#include <unordered_map>

enum struct EGroupType
{
	PLAYERS, BUILDINGS,
	PICKUPS_HEALTH, PICKUPS_AMMO, PICKUPS_MONEY, PICKUPS_POWERUP, PICKUPS_SPELLBOOK,
	WORLD_PROJECTILES, WORLD_OBJECTIVE, WORLD_NPC, WORLD_BOMBS
};

class CEntities
{
private:
	CTFPlayerResource* m_pPlayerResource = nullptr;

	std::unordered_map<EGroupType, std::vector<CBaseEntity*>> m_mGroups = {};
	std::unordered_map<int, uint32_t> m_mModels = {};

public:
	void Store();
	void Clear(bool bShutdown = false);

	bool IsHealth(uint32_t uHash);
	bool IsAmmo(uint32_t uHash);
	bool IsPowerup(uint32_t uHash);
	bool IsSpellbook(uint32_t uHash);

	CTFPlayerResource* GetPR();
	const std::vector<CBaseEntity*>& GetGroup(const EGroupType& Group);
	uint32_t GetModel(int iIndex);
};

ADD_FEATURE_CUSTOM(CEntities, Entities, H);