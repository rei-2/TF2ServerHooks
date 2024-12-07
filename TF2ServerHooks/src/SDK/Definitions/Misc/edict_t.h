#pragma once

class IServerNetworkable;
class IServerUnknown;

class CBaseEdict
{
public:
#ifdef _XBOX
	unsigned short m_fStateFlags;
#else
	int	m_fStateFlags;
#endif	

#if VALVE_LITTLE_ENDIAN
	short m_NetworkSerialNumber;
	short m_EdictIndex;
#else
	short m_EdictIndex;
	short m_NetworkSerialNumber;
#endif

	IServerNetworkable* m_pNetworkable;
	IServerUnknown* m_pUnk;
};
struct edict_t : public CBaseEdict
{
public:
	float		freetime;
};