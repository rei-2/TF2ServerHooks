#pragma once
#include "Interface.h"
#include "../Main/CBaseEntity.h"
#include "../Misc/ChecksumCRC.h"
#include "../Main/UtlVector.h"
#include "../Misc/edict_t.h"
#include "../Misc/String.h"

class IEntityListener;
class CBaseNetworkable;
class IEntityFindFilter;
class CEntInfo
{
public:
	IHandleEntity* m_pEntity;
	int				m_SerialNumber;
	CEntInfo* m_pPrev;
	CEntInfo* m_pNext;

	void			ClearLinks();
};

class CBaseEntityList
{
public:
	CBaseEntityList();
	~CBaseEntityList();

	CBaseHandle AddNetworkableEntity(IHandleEntity* pEnt, int index, int iForcedSerialNum = -1);
	CBaseHandle AddNonNetworkableEntity(IHandleEntity* pEnt);
	void RemoveEntity(CBaseHandle handle);

	CBaseHandle GetNetworkableHandle(int iEntity) const;

	IHandleEntity* LookupEntity(const CBaseHandle& handle) const;
	IHandleEntity* LookupEntityByNetworkIndex(int edictIndex) const;

	CBaseHandle FirstHandle() const;
	CBaseHandle NextHandle(CBaseHandle hEnt) const;
	static CBaseHandle InvalidHandle();

	const CEntInfo* FirstEntInfo() const;
	const CEntInfo* NextEntInfo(const CEntInfo* pInfo) const;
	const CEntInfo* GetEntInfoPtr(const CBaseHandle& hEnt) const;
	const CEntInfo* GetEntInfoPtrByIndex(int index) const;

	virtual void OnAddEntity(IHandleEntity* pEnt, CBaseHandle handle);

	virtual void OnRemoveEntity(IHandleEntity* pEnt, CBaseHandle handle);

	CBaseHandle AddEntityAtSlot(IHandleEntity* pEnt, int iSlot, int iForcedSerialNum);
	void RemoveEntityAtSlot(int iSlot);

	class CEntInfoList
	{
	public:
		CEntInfoList();

		const CEntInfo* Head() const { return m_pHead; }
		const CEntInfo* Tail() const { return m_pTail; }
		CEntInfo* Head() { return m_pHead; }
		CEntInfo* Tail() { return m_pTail; }
		void			AddToHead(CEntInfo* pElement) { LinkAfter(NULL, pElement); }
		void			AddToTail(CEntInfo* pElement) { LinkBefore(NULL, pElement); }

		void LinkBefore(CEntInfo* pBefore, CEntInfo* pElement);
		void LinkAfter(CEntInfo* pBefore, CEntInfo* pElement);
		void Unlink(CEntInfo* pElement);
		bool IsInList(CEntInfo* pElement);

		CEntInfo* m_pHead;
		CEntInfo* m_pTail;
	};

	int GetEntInfoIndex(const CEntInfo* pEntInfo) const;

	CEntInfo m_EntPtrArray[NUM_ENT_ENTRIES * 2]; // don't know why the x2 is necessary but it religns the offsets of later member properties
	CEntInfoList	m_activeList;
	CEntInfoList	m_freeNonNetworkableList;
};
inline int CBaseEntityList::GetEntInfoIndex(const CEntInfo* pEntInfo) const
{
	int index = (int)(pEntInfo - m_EntPtrArray);
	return index;
}
inline CBaseHandle CBaseEntityList::GetNetworkableHandle(int iEntity) const
{
	if (m_EntPtrArray[iEntity].m_pEntity)
		return CBaseHandle(iEntity, m_EntPtrArray[iEntity].m_SerialNumber);
	else
		return CBaseHandle();
}
inline IHandleEntity* CBaseEntityList::LookupEntity(const CBaseHandle& handle) const
{
	if (handle.m_Index == INVALID_EHANDLE_INDEX)
		return NULL;

	const CEntInfo* pInfo = &m_EntPtrArray[handle.GetEntryIndex()];
	if (pInfo->m_SerialNumber == handle.GetSerialNumber())
		return (IHandleEntity*)pInfo->m_pEntity;
	else
		return NULL;
}
inline IHandleEntity* CBaseEntityList::LookupEntityByNetworkIndex(int edictIndex) const
{
	// (Legacy support).
	if (edictIndex < 0)
		return NULL;

	return (IHandleEntity*)m_EntPtrArray[edictIndex].m_pEntity;
}
inline CBaseHandle CBaseEntityList::FirstHandle() const
{
	if (!m_activeList.Head())
		return INVALID_EHANDLE_INDEX;

	int index = GetEntInfoIndex(m_activeList.Head());
	return CBaseHandle(index, m_EntPtrArray[index].m_SerialNumber);
}
inline CBaseHandle CBaseEntityList::NextHandle(CBaseHandle hEnt) const
{
	int iSlot = hEnt.GetEntryIndex();
	CEntInfo* pNext = m_EntPtrArray[iSlot].m_pNext;
	if (!pNext)
		return INVALID_EHANDLE_INDEX;

	int index = GetEntInfoIndex(pNext);

	return CBaseHandle(index, m_EntPtrArray[index].m_SerialNumber);
}
inline CBaseHandle CBaseEntityList::InvalidHandle()
{
	return INVALID_EHANDLE_INDEX;
}
inline const CEntInfo* CBaseEntityList::FirstEntInfo() const
{
	return m_activeList.Head();
}
inline const CEntInfo* CBaseEntityList::NextEntInfo(const CEntInfo* pInfo) const
{
	return pInfo->m_pNext;
}
inline const CEntInfo* CBaseEntityList::GetEntInfoPtr(const CBaseHandle& hEnt) const
{
	int iSlot = hEnt.GetEntryIndex();
	return &m_EntPtrArray[iSlot];
}
inline const CEntInfo* CBaseEntityList::GetEntInfoPtrByIndex(int index) const
{
	return &m_EntPtrArray[index];
}

class CGlobalEntityList : public CBaseEntityList
{
public:
	virtual void OnAddEntity(IHandleEntity* pEnt, CBaseHandle handle) = 0;
	virtual void OnRemoveEntity(IHandleEntity* pEnt, CBaseHandle handle) = 0;

	CBaseEntity* NextEnt(CBaseEntity* pCurrentEnt);
	CBaseEntity* FirstEnt() { return NextEnt(NULL); }

	template< class T >
	T* NextEntByClass(T* start)
	{
		for (CBaseEntity* x = NextEnt(start); x; x = NextEnt(x))
		{
			start = dynamic_cast<T*>(x);
			if (start)
				return start;
		}
		return NULL;
	}

	int m_iHighestEnt;
	int m_iNumEnts;
	int m_iNumEdicts;
	bool m_bClearingEntities;
	CUtlVector<IEntityListener*>	m_entityListeners;
};

MAKE_INTERFACE_SIGNATURE(CGlobalEntityList, GlobalEntityList, "server.dll", "48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B D8 48 85 C0 74 ? 0F 1F 40 ? 66 0F 1F 84 00", 0x0, 0);