#pragma once

#include "../../Utils/Feature/Feature.h"

#include "Interfaces/CEntityList.h"
#include "Interfaces/CGlobalVarsBase.h"
#include "Interfaces/CTFGameRules.h"
#include "Interfaces/ICVar.h"
#include "Interfaces/IEngineTrace.h"
#include "Interfaces/IEngineVGui.h"
#include "Interfaces/IGameEvents.h"
#include "Interfaces/IGameMovement.h"
#include "Interfaces/IMaterialSystem.h"
#include "Interfaces/IMoveHelper.h"
#include "Interfaces/IServerGameDLL.h"
#include "Interfaces/IUniformRandomStream.h"
#include "Interfaces/IVEngineServer.h"
#include "Interfaces/IVModelInfo.h"
#include "Interfaces/SteamInterfaces.h"
#include "Interfaces/VPhysics.h"

class CNullInterfaces
{
public:
	void Initialize();
};

ADD_FEATURE_CUSTOM(CNullInterfaces, Interfaces, H);