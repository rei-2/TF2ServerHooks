#pragma once

#include "Globals.h"
#include "Helpers/Entities/Entities.h"
#include "Helpers/TraceFilters/TraceFilters.h"
#include "Definitions/Types.h"
#include "Definitions/Interfaces.h"
#include "Definitions/Classes.h"
#include "../Utils/Signatures/Signatures.h"
#include "../Utils/Interfaces/Interfaces.h"
#include "../Utils/Hooks/Hooks.h"
#include "../Utils/Memory/Memory.h"
#include "../Utils/ConVars/ConVars.h"
#include "../Utils/Hash/FNV1A.h"
#include "../Utils/Timer/Timer.h"
#include "../Utils/Macros/Macros.h"
#include <intrin.h>

template <typename T> int sign(T val)
{
	return (val > T(0)) - (val < T(0));
}

#define OUTPUT_CONSOLE 1 << 0
#define OUTPUT_DEBUG 1 << 1

namespace SDK
{
	void Output(const char* cFunction, const char* cLog = nullptr, Color_t tColor = { 255, 255, 255, 255 },
		int iTo = OUTPUT_CONSOLE, int iMessageBox = -1,
		const char* sLeft = "[", const char* sRight = "]");
	void OutputClient(const char* cFunction, const char* cLog = nullptr,
		CBasePlayer* pPlayer = nullptr, int iMessageType = HUD_PRINTCONSOLE,
		const char* sLeft = "[", const char* sRight = "]");

	std::wstring ConvertUtf8ToWide(const std::string& source);
	std::string ConvertWideToUTF8(const std::wstring& source);

	double PlatFloatTime();
	int StdRandomInt(int min, int max);
	float StdRandomFloat(float min, float max);

	int SeedFileLineHash(int seedvalue, const char* sharedname, int additionalSeed);
	int SharedRandomInt(unsigned iseed, const char* sharedname, int iMinVal, int iMaxVal, int additionalSeed);
	void RandomSeed(int iSeed);
	int RandomInt(int iMinVal = 0, int iMaxVal = 0x7FFF);
	float RandomFloat(float flMinVal = 0.f, float flMaxVal = 1.f);
	
	int HandleToIDX(unsigned int pHandle);

	void Trace(const Vec3& vecStart, const Vec3& vecEnd, unsigned int nMask, ITraceFilter* pFilter, CGameTrace* pTrace);
	void TraceHull(const Vec3& vecStart, const Vec3& vecEnd, const Vec3& vecHullMin, const Vec3& vecHullMax, unsigned int nMask, ITraceFilter* pFilter, CGameTrace* pTrace);

	bool VisPos(CBaseEntity* pSkip, const CBaseEntity* pEntity, const Vec3& from, const Vec3& to, unsigned int nMask = MASK_SHOT | CONTENTS_GRATE);
	bool VisPosProjectile(CBaseEntity* pSkip, const CBaseEntity* pEntity, const Vec3& from, const Vec3& to, unsigned int nMask = MASK_SHOT | CONTENTS_GRATE);
	bool VisPosWorld(CBaseEntity* pSkip, const CBaseEntity* pEntity, const Vec3& from, const Vec3& to, unsigned int nMask = MASK_SHOT | CONTENTS_GRATE);
}