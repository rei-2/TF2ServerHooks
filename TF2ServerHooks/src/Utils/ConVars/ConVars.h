#pragma once
#include "../Feature/Feature.h"
#include "../../SDK/Definitions/Misc/ConVar.h"
#include "../Hash/FNV1A.h"
#include <unordered_map>

class CConVars
{
private:
	std::unordered_map<uint32_t, ConVar*> mCVarMap;

public:
	ConVar* FindVar(const char* cvarname);
};

ADD_FEATURE_CUSTOM(CConVars, ConVars, U);