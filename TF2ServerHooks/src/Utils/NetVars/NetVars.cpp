#include "NetVars.h"

#include "../../SDK/Definitions/Interfaces/IServerGameDLL.h"
#include "../Hash/FNV1A.h"

int CNetVars::GetOffset(SendTable* pTable, const char* szNetVar)
{
	auto uHash = FNV1A::Hash32(szNetVar);
	for (int i = 0; i < pTable->m_nProps; i++)
	{
		SendProp Prop = pTable->m_pProps[i];

		if (uHash == FNV1A::Hash32(Prop.m_pVarName))
			return Prop.GetOffset();

		if (auto DataTable = Prop.GetDataTable())
		{
			if (auto nOffset = GetOffset(DataTable, szNetVar))
				return nOffset + Prop.GetOffset();
		}
	}

	return 0;
}

int CNetVars::GetNetVar(const char* szClass, const char* szNetVar)
{
	ServerClass* pClasses = I::ServerGameDLL->GetAllServerClasses();

	auto uHash = FNV1A::Hash32(szClass);
	for (auto pCurrNode = pClasses; pCurrNode; pCurrNode = pCurrNode->m_pNext)
	{
		if (uHash == FNV1A::Hash32(pCurrNode->m_pNetworkName))
			return GetOffset(pCurrNode->m_pTable, szNetVar);
	}

	return 0;
}