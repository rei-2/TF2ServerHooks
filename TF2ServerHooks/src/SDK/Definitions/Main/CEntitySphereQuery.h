#pragma once
#include "../../../Utils/Signatures/Signatures.h"
#include "../Definitions.h"
#include "CBaseEntity.h"

#define MAX_SPHERE_QUERY	512

#pragma warning (disable : 26495)

#if x86
MAKE_SIGNATURE(CEntitySphereQuery, "server.dll", "55 8B EC 83 EC ? D9 45 ? 8D 55", 0x0);
#else
MAKE_SIGNATURE(CEntitySphereQuery, "server.dll", "40 53 48 83 EC ? 48 8B D9 C7 44 24 ? ? ? ? ? 33 C9", 0x0);
#endif

//credits to KGB
class CEntitySphereQuery
{
public:
	CEntitySphereQuery(const Vec3& center, const float radius, const int flagMask = 0, const int partitionMask = PARTITION_CLIENT_NON_STATIC_EDICTS)
	{
#if x86
		reinterpret_cast<void(__fastcall*)(CEntitySphereQuery*, const Vec3&, const float, const int, const int)>(S::CEntitySphereQuery())(this, center, radius, flagMask, partitionMask);
#else
		S::CEntitySphereQuery.Call<void>(this, std::ref(center), radius, flagMask, partitionMask);
#endif
	}

	inline CBaseEntity* GetCurrentEntity()
	{
		return (m_nListIndex < m_nListCount) ? m_pList[m_nListIndex] : nullptr;
	}

	inline void NextEntity()
	{
		m_nListIndex++;
	}

private:
	int m_nListIndex, m_nListCount;
	CBaseEntity* m_pList[MAX_SPHERE_QUERY];
};