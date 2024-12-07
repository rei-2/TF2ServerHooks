#include "ConVars.h"

#include "../../SDK/Definitions/Interfaces/ICVar.h"

ConVar* CConVars::FindVar(const char* cvarname)
{
	if (!mCVarMap.contains(FNV1A::Hash32Const(cvarname)))
		mCVarMap[FNV1A::Hash32Const(cvarname)] = I::CVar->FindVar(cvarname);
	return mCVarMap[FNV1A::Hash32Const(cvarname)];
}