#pragma once
#include "CEconEntity.h"

class CEconWearable : public CEconEntity
{
public:
	VIRTUAL_ARGS(Equip, void, void(*)(void*, CBasePlayer*), 229, this, (CBasePlayer* pOwner), this, pOwner);
	VIRTUAL_ARGS(UnEquip, void, void(*)(void*, CBasePlayer*), 230, this, (CBasePlayer* pOwner), this, pOwner);
};