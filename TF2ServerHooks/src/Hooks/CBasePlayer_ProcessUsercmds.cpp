#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CBasePlayer_ProcessUsercmds, "server.dll", "55 8B EC 83 EC ? 53 8B D9 56 57 FF B3", 0x0);
#else
MAKE_SIGNATURE(CBasePlayer_ProcessUsercmds, "server.dll", "40 53 55 56 57 41 54 48 83 EC ? 4C 89 6C 24", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFWeaponBase_IncrementAmmo, "server.dll", "55 8B EC 83 EC ? 56 57 6A ? 68 ? ? ? ? 68 ? ? ? ? 6A ? 8B F1 E8 ? ? ? ? 50 E8 ? ? ? ? 83 C4", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBase_IncrementAmmo, "server.dll", "40 53 57 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 8B C8", 0x0);
#endif

namespace MoveEnum
{
	enum MoveEnum
	{
		Ground, Air, Swim, Max
	};
}

struct MoveData
{
	Vec3 m_vDirection = {};
	float m_flSimTime = 0.f;
	int m_iMode = 0;
	Vec3 m_vVelocity = {};
	Vec3 m_vOrigin = {};
};

std::unordered_map<int, std::deque<MoveData>> s_mRecords = {};
static CUserCmd s_tDummyCmd = {};
static float s_flTime = 0.f;

// proof of concepts that didn't really work out (most notably due to the origin compression and lag)
// there is probably a way to implement ground movement in a way that's beneficial, but i didn't care enough to fiddle around with it

static inline void CalculateMovement(CTFPlayer* pPlayer, MoveData* pLastRecord, MoveData& tCurRecord, std::deque<MoveData>& vRecords)
{
	if (pLastRecord)
	{
		/*
		if (tRecord.m_iMode != pLastRecord->m_iMode)
		{
			pLastRecord = nullptr;
			vRecords.clear();
		}
		else // does this eat up fps? i can't tell currently
		{
			CGameTrace trace = {};
			CTraceFilterWorldAndPropsOnly filter = {};
			SDK::TraceHull(pLastRecord->m_vOrigin, pLastRecord->m_vOrigin + pLastRecord->m_vVelocity * TICK_INTERVAL, pPlayer->m_vecMins() + 0.125f, pPlayer->m_vecMaxs() - 0.125f, pPlayer->SolidMask(), &filter, &trace);
			if (trace.DidHit() && trace.plane.normal.z < 0.707f)
			{
				pLastRecord = nullptr;
				vRecords.clear();
			}
		}
		*/
	}
	if (!pLastRecord)
		return;
	if (!TIME_TO_TICKS(tCurRecord.m_flSimTime - pLastRecord->m_flSimTime))
	{
		vRecords.pop_front();
		return;
	}

	SDK::Output("CalculateMovement", std::format("Delta: {}, {}", TIME_TO_TICKS(tCurRecord.m_flSimTime - pLastRecord->m_flSimTime), tCurRecord.m_flSimTime - pLastRecord->m_flSimTime).c_str());

	if (pPlayer->InCond(TF_COND_SHIELD_CHARGE))
	{
		s_tDummyCmd.forwardmove = 450.f;
		s_tDummyCmd.sidemove = 0.f;
		SDK::FixMovement(&s_tDummyCmd, pPlayer->GetEyeAngles(), {});
		tCurRecord.m_vDirection.x = s_tDummyCmd.forwardmove;
		tCurRecord.m_vDirection.y = -s_tDummyCmd.sidemove;
		return;
	}

	float flMaxSpeed = SDK::MaxSpeed(pPlayer, true);
	switch (tCurRecord.m_iMode)
	{
	case MoveEnum::Ground:
	{
		static auto sv_accelerate = U::ConVars.FindVar("sv_accelerate");
		static auto sv_friction = U::ConVars.FindVar("sv_friction");
		static auto sv_stopspeed = U::ConVars.FindVar("sv_stopspeed");

		float flAccel = sv_accelerate->GetFloat();
		float flFriction = sv_friction->GetFloat();
		float flStopSpeed = sv_stopspeed->GetFloat();

		float flEntFriction = 1.f;

		Vec3 vOldVelocity = pLastRecord->m_vVelocity, vNewVelocity = tCurRecord.m_vVelocity;
		vOldVelocity.z = vNewVelocity.z = 0;
		vOldVelocity /= std::max(vOldVelocity.Length2D() / flMaxSpeed, 1.f);
		vNewVelocity /= std::max(vNewVelocity.Length2D() / flMaxSpeed, 1.f);

		// friction
		float flSpeed = vOldVelocity.Length2D();
		if (flSpeed >= 0.1f)
		{
			float flControl = std::max(flStopSpeed, flSpeed);
			float flDrop = flControl * flFriction * flEntFriction * TICK_INTERVAL;
			float flNewSpeed = std::max(flSpeed - flDrop, 0.f);
			if (flNewSpeed != flSpeed)
			{
				flNewSpeed /= flSpeed;
				vOldVelocity *= flNewSpeed;
			}
		}

		Vec3 vWishDir = vNewVelocity - vOldVelocity;
		float flAccelSpeed = vWishDir.Normalize();
		float flMaxAccel = flAccel * flMaxSpeed * flEntFriction * TICK_INTERVAL;
		if (flAccelSpeed < flMaxAccel * 0.999f && vNewVelocity.Length2D() > flMaxSpeed * 0.999f)
		{
			float flMult;
			{
				// quadratic
				float flA = powf(vNewVelocity.x, 2.f) + powf(vNewVelocity.y, 2.f);
				float flB = -2 * vNewVelocity.x * vOldVelocity.x - 2 * vNewVelocity.y * vOldVelocity.y;
				float flC = powf(vOldVelocity.x, 2.f) + powf(vOldVelocity.y, 2.f) - powf(flMaxAccel, 2.f);
				flMult = (-flB + sqrt(fabsf(powf(flB, 2.f) - 4 * flA * flC))) / (2 * flA);
			}
			vNewVelocity *= flMult;

			vWishDir = vNewVelocity - vOldVelocity;
			flAccelSpeed = vWishDir.Normalize();

			float flCurSpeed = vOldVelocity.Dot(vWishDir);
			float flAccelSpeed2 = std::max(flMaxSpeed - flCurSpeed, 0.f);
			if (flAccelSpeed2 < flMaxAccel)
			{
				vNewVelocity = tCurRecord.m_vVelocity;
				vNewVelocity.z = 0;
				vNewVelocity /= std::max(vNewVelocity.Length2D() / flMaxSpeed, 1.f);
				{
					// quartic
					float flA = pow((powf(vNewVelocity.x, 2.f) + powf(vNewVelocity.y, 2.f)) / flMaxSpeed, 2);
					float flB = (2 * (powf(vNewVelocity.x, 2.f) + powf(vNewVelocity.y, 2.f)) * (-vOldVelocity.x * vNewVelocity.x - vOldVelocity.y * vNewVelocity.y)) / pow(flMaxSpeed, 2);
					float flC = pow((-vOldVelocity.x * vNewVelocity.x - vOldVelocity.y * vNewVelocity.y) / flMaxSpeed, 2) - powf(vNewVelocity.x, 2.f) - powf(vNewVelocity.y, 2.f);
					float flD = 2 * vNewVelocity.x * vOldVelocity.x + 2 * vNewVelocity.y * vOldVelocity.y;
					float flE = -powf(vOldVelocity.x, 2.f) - powf(vOldVelocity.y, 2.f);
					auto vRoots = Math::SolveQuartic(flA, flB, flC, flD, flE);
					if (vRoots.size())
						flMult = std::clamp(*std::max_element(vRoots.begin(), vRoots.end()), 1.f, flMult);
				}
				vNewVelocity *= flMult;

				vWishDir = vNewVelocity - vOldVelocity;
				flAccelSpeed = vWishDir.Normalize();
			}
		}

		SDK::Output("MoveEnum::Ground", std::format("AccelSpeed: {}", flAccelSpeed).c_str());
		flAccelSpeed = flAccelSpeed < (flAccel * flMaxSpeed * flEntFriction * TICK_INTERVAL) * 0.35f ? 0.f : flMaxSpeed; // this might be a bad solution?

		if (!tCurRecord.m_vDirection.IsZero())
		{
			//float flAng1 = Math::VectorAngles(tCurRecord.m_vDirection).y, flAng2 = Math::VectorAngles(vWishDir).y;
			//float flDiff = Math::NormalizeAngle(flAng1 - flAng2);

			//SDK::Output("MoveEnum::Ground", std::format("Diff: {}", flDiff).c_str());
			{
				Vec3 vStart = tCurRecord.m_vOrigin;
				Vec3 vEnd = tCurRecord.m_vOrigin + tCurRecord.m_vDirection;
				SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, 255, 0, 0, 0, G::DrawDuration ? G::DrawDuration : 0.015).c_str(), G::DebugTarget);
			}
			{
				Vec3 vStart = tCurRecord.m_vOrigin;
				Vec3 vEnd = tCurRecord.m_vOrigin + vWishDir * flAccelSpeed;
				SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, 0, 255, 0, 0, G::DrawDuration ? G::DrawDuration : 0.015).c_str(), G::DebugTarget);
			}

			//if (flAccelSpeed > 0 && !vWishDir.IsZero() && fabsf(flDiff) > 45.f)
				tCurRecord.m_vDirection = vWishDir * flAccelSpeed;
			//else
			//	tCurRecord.m_vDirection = tCurRecord.m_vDirection.Normalized() * flAccelSpeed;
		}
		break;
	}
	case MoveEnum::Air:
	{
		tCurRecord.m_vDirection = tCurRecord.m_vVelocity.Normalized2D() * flMaxSpeed;
		break;
	}
	case MoveEnum::Swim:
	{
		tCurRecord.m_vDirection *= 2;
	}
	}
}

static inline void RunMovement(CTFPlayer* pPlayer, const Vec3& vMove, Vec3& vVelocity, Vec3& vOrigin)
{
	vVelocity[2] = 0.f;

	// Friction
	{
		static auto sv_friction = U::ConVars.FindVar("sv_friction");
		static auto sv_stopspeed = U::ConVars.FindVar("sv_stopspeed");

		float flSpeed = vVelocity.Length();
		if (flSpeed >= 0.1f)
		{
			float flDrop = 0;
			float flFriction = sv_friction->GetFloat();
			float flControl = flSpeed < sv_stopspeed->GetFloat() ? sv_stopspeed->GetFloat() : flSpeed;
			flDrop += flControl * flFriction * I::GlobalVars->frametime;

			float flNewSpeed = flSpeed - flDrop;
			if (flNewSpeed < 0)
				flNewSpeed = 0;

			if (flNewSpeed != flSpeed)
			{
				flNewSpeed /= flSpeed;
				vVelocity *= flNewSpeed;
			}
		}
	}

	// WalkMove
	{
		static auto sv_accelerate = U::ConVars.FindVar("sv_accelerate");
		static auto sv_friction = U::ConVars.FindVar("sv_friction");
		static auto sv_stopspeed = U::ConVars.FindVar("sv_stopspeed");
		static auto tf_clamp_back_speed = U::ConVars.FindVar("tf_clamp_back_speed");
		static auto tf_clamp_back_speed_min = U::ConVars.FindVar("tf_clamp_back_speed_min");

		float flMaxSpeed = SDK::MaxSpeed(pPlayer, true);

		Vec3 vForward, vRight;
		Math::AngleVectors(pPlayer->GetEyeAngles(), &vForward, &vRight);
		vForward = vForward.To2D().Normalized(), vRight = vRight.To2D().Normalized();

		float flForwardMove = vMove.x;
		float flSideMove = vMove.y;

		Vec3 vWishDir = {
			vForward.x * flForwardMove + vRight.x * flSideMove,
			vForward.y * flForwardMove + vRight.y * flSideMove,
			0.f
		};

		float flWishSpeed = std::clamp(vWishDir.Normalize(), 0.f, flMaxSpeed);

		vVelocity.z = 0;

		float flAccelerate = sv_accelerate->GetFloat();
		float flFriction = sv_friction->GetFloat();
		float flWishSpeedThreshold = 100.f * flFriction / flAccelerate;
		if (flWishSpeed > 0 && flWishSpeed < flWishSpeedThreshold)
		{
			if (!pPlayer->InCond(TF_COND_LOST_FOOTING))
			{
				float flSpeed = vVelocity.Length();
				float flControl = flSpeed < sv_stopspeed->GetFloat() ? sv_stopspeed->GetFloat() : flSpeed;
				flAccelerate = (flControl * flFriction) / flWishSpeed + 1;
			}
		}

		// Accelerate
		{
			float flCurrentspeed = vVelocity.Dot(vWishDir);
			float flAddSpeed = flWishSpeed - flCurrentspeed;
			if (flAddSpeed > 0)
			{
				float flAccelSpeed = flAccelerate * I::GlobalVars->frametime * flWishSpeed;
				if (flAccelSpeed > flAddSpeed)
					flAccelSpeed = flAddSpeed;

				vVelocity += vWishDir * flAccelSpeed;
			}
		}

		float flNewSpeed = vVelocity.Length();
		if (flNewSpeed > flMaxSpeed)
		{
			float flScale = (flMaxSpeed / flNewSpeed);
			vVelocity.x *= flScale;
			vVelocity.y *= flScale;
		}

		if (tf_clamp_back_speed->GetFloat() < 1 && vVelocity.Length() > tf_clamp_back_speed_min->GetFloat())
		{
			float flDot = vForward.Dot(vVelocity);
			if (flDot < 0)
			{
				Vector vBackMove = vForward * flDot;
				Vector vRightMove = vRight * vRight.Dot(vVelocity);

				float flBackSpeed = vBackMove.Length();
				float flMaxBackSpeed = (flMaxSpeed * tf_clamp_back_speed->GetFloat());

				if (flBackSpeed > flMaxBackSpeed)
					vBackMove *= flMaxBackSpeed / flBackSpeed;

				vVelocity = vBackMove + vRightMove;

				flNewSpeed = vVelocity.Length();
				if (flNewSpeed > flMaxSpeed)
				{
					float flScale = (flMaxSpeed / flNewSpeed);
					vVelocity.x *= flScale;
					vVelocity.y *= flScale;
				}
			}
		}

		vVelocity += pPlayer->m_vecBaseVelocity();

		float flSpeed = vVelocity.Length();
		if (flSpeed < 1.f)
			vVelocity = {};
		else
		{
			vOrigin += { vVelocity.x* I::GlobalVars->frametime, vVelocity.y* I::GlobalVars->frametime };
			vVelocity -= pPlayer->m_vecBaseVelocity();
		}
	}

	vVelocity[2] = 0.f;
}

static inline void BruteforceMovement(CTFPlayer* pPlayer, MoveData* pLastRecord, MoveData& tCurRecord, std::deque<MoveData>& vRecords)
{
	if (pLastRecord)
	{
		/*
		if (tRecord.m_iMode != pLastRecord->m_iMode)
		{
			pLastRecord = nullptr;
			vRecords.clear();
		}
		else // does this eat up fps? i can't tell currently
		{
			CGameTrace trace = {};
			CTraceFilterWorldAndPropsOnly filter = {};
			SDK::TraceHull(pLastRecord->m_vOrigin, pLastRecord->m_vOrigin + pLastRecord->m_vVelocity * TICK_INTERVAL, pPlayer->m_vecMins() + 0.125f, pPlayer->m_vecMaxs() - 0.125f, pPlayer->SolidMask(), &filter, &trace);
			if (trace.DidHit() && trace.plane.normal.z < 0.707f)
			{
				pLastRecord = nullptr;
				vRecords.clear();
			}
		}
		*/
	}
	if (!pLastRecord)
		return;
	if (!TIME_TO_TICKS(tCurRecord.m_flSimTime - pLastRecord->m_flSimTime))
	{
		vRecords.pop_front();
		return;
	}

	if (pPlayer->InCond(TF_COND_SHIELD_CHARGE))
	{
		s_tDummyCmd.forwardmove = 450.f;
		s_tDummyCmd.sidemove = 0.f;
		SDK::FixMovement(&s_tDummyCmd, pPlayer->GetEyeAngles(), {});
		tCurRecord.m_vDirection.x = s_tDummyCmd.forwardmove;
		tCurRecord.m_vDirection.y = -s_tDummyCmd.sidemove;
		return;
	}

	switch (tCurRecord.m_iMode)
	{
	case MoveEnum::Ground: // walkmove
	{
		static std::vector<Vec3> vMoves = {
			{ 0, 0 },
			{ 450, 0 },
			{ 450, -450 },
			{ 0, -450 },
			{ -450, -450 },
			{ -450, 0 },
			{ -450, 450 },
			{ 0, 450 },
			{ 450, 450 }
		};

		int iTicks = TIME_TO_TICKS(tCurRecord.m_flSimTime - pLastRecord->m_flSimTime);
		Vec3 vAngles = pPlayer->GetEyeAngles();
		float flMinDist = std::numeric_limits<float>::max();
		Vec3 vMinMove = {};

		SDK::Output("");
		SDK::Output("BruteforceMovement", std::format("Ticks: {}; Dist: {}", iTicks, tCurRecord.m_vOrigin.DistTo(pLastRecord->m_vOrigin)).c_str());

		for (auto& vMove : vMoves)
		{
			Vec3 vVelocity = pLastRecord->m_vVelocity;
			Vec3 vOrigin = pLastRecord->m_vOrigin;

			for (int i = 0; i < iTicks; i++)
				RunMovement(pPlayer, vMove, vVelocity, vOrigin);

			//if ((tCurRecord.m_vOrigin - vOrigin).IsZero(0.1f))
			//	SDK::Output("BruteforceMovement", std::format("Dist: {}; Move: {}, {}", flDist, vMove.x, vMove.y).c_str());
			float flDist = tCurRecord.m_vOrigin.DistTo(vOrigin);
			if (flDist < flMinDist)
			{
				flMinDist = flDist;
				vMinMove = vMove;
			}
		}
		{
			Vec3 vStart = tCurRecord.m_vOrigin;
			Vec3 vEnd = tCurRecord.m_vOrigin + tCurRecord.m_vDirection;
			SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, 255, 0, 0, 0, G::DrawDuration ? G::DrawDuration : 0.015).c_str(), G::DebugTarget);
		}
		{
			Vec3 vForward, vRight;
			Math::AngleVectors(vAngles, &vForward, &vRight);
			vForward = vForward.To2D().Normalized(), vRight = vRight.To2D().Normalized();

			float flForwardMove = vMinMove.x;
			float flSideMove = vMinMove.y;

			Vec3 vWishDir = {
				vForward.x * flForwardMove + vRight.x * flSideMove,
				vForward.y * flForwardMove + vRight.y * flSideMove,
				0.f
			};

			Vec3 vStart = tCurRecord.m_vOrigin;
			Vec3 vEnd = tCurRecord.m_vOrigin + vWishDir;
			SDK::OutputClient("Line", std::format("{} {} {} {} {} {} {} {} {} {} {}", vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, 0, 255, 0, 0, G::DrawDuration ? G::DrawDuration : 0.015).c_str(), G::DebugTarget);
		}
		SDK::Output("BruteforceMovement", std::format("Move: {}, {}; Dist: {}", vMinMove.x, vMinMove.y, flMinDist).c_str());
		break;
	}
	case MoveEnum::Air:
	{
		float flMaxSpeed = SDK::MaxSpeed(pPlayer, true);

		tCurRecord.m_vDirection = tCurRecord.m_vVelocity.Normalized2D() * flMaxSpeed;
		break;
	}
	case MoveEnum::Swim:
	{
		tCurRecord.m_vDirection *= 2;
	}
	}
}

static inline void Store(CTFPlayer* pTarget)
{
	G::DebugTarget = pTarget;

	for (CBaseEntity* pEntity = I::GlobalEntityList->FirstEnt(); pEntity; pEntity = I::GlobalEntityList->NextEnt(pEntity))
	{
		auto pPlayer = pEntity->As<CTFPlayer>();
		if (!pEntity->IsPlayer())
			continue;

		auto& vRecords = s_mRecords[pPlayer->entindex()];
		if (!pPlayer->IsAlive() || pPlayer->IsAGhost() || pPlayer->m_vecVelocity().IsZero())
		{
			vRecords.clear();
			continue;
		}
		MoveData* pLastRecord = !vRecords.empty() ? &vRecords.front() : nullptr;
		vRecords.emplace_front(
			Vec3(pPlayer->m_vecVelocity().x, pPlayer->m_vecVelocity().y, 0.f),
			//pPlayer->GetEyeAngles(),
			pPlayer->m_flSimulationTime(), // s_flTime
			pPlayer->m_nWaterLevel() >= 2 ? 2 : pPlayer->IsOnGround() ? 0 : 1,
			pPlayer->m_vecVelocity(),
			pPlayer->m_vecOrigin()
		);
		MoveData& tCurRecord = vRecords.front();
		if (vRecords.size() > 66)
			vRecords.pop_back();

		BruteforceMovement(pPlayer, pLastRecord, tCurRecord, vRecords);
	}
}

#if x86
MAKE_HOOK(CBasePlayer_ProcessUsercmds, S::CBasePlayer_ProcessUsercmds(), void, __fastcall,
	void* ecx, void* edx, CUserCmd* cmds, int numcmds, int totalcmds, int dropped_packets, bool paused)
#else
MAKE_HOOK(CBasePlayer_ProcessUsercmds, S::CBasePlayer_ProcessUsercmds(), void,
	void* rcx, CUserCmd* cmds, int numcmds, int totalcmds, int dropped_packets, bool paused)
#endif
{
	bool bInAttack = false;
	for (int i = totalcmds - 1; i >= 0; i--)
	{
		CUserCmd* pCmd = &cmds[totalcmds - 1 - i];
		if (pCmd && pCmd->buttons & IN_ATTACK)
			bInAttack = true;
	}
	if (bInAttack)
	{
		//SDK::Output("ProcessUsercmds", std::format("{}: {}", SDK::PlatFloatTime(), std::bit_cast<int32_t>(float(SDK::PlatFloatTime() * 1000.0)) & 255).c_str(), { 255, 0, 0, 255 });

		//auto pPlayer = reinterpret_cast<CTFPlayer*>(rcx);

		//float flTime = TICKS_TO_TIME(pPlayer->m_nTickBase());
		//float flAttack = pPlayer->m_flNextAttack();
		//SDK::Output("ProcessUsercmds", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str());
		//SDK::OutputClient("ProcessUsercmds", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str(), pPlayer);
	}

	if (G::ServerHitboxes)
	{
#if x86
		G::DebugTarget = reinterpret_cast<CTFPlayer*>(ecx);
#else
		G::DebugTarget = reinterpret_cast<CTFPlayer*>(rcx);
#endif

		// don't send every tick to prevent throttling
		if (!(I::GlobalVars->tickcount % G::ServerHitboxesRate))
		{
			for (CBaseEntity* pEntity = I::GlobalEntityList->FirstEnt(); pEntity; pEntity = I::GlobalEntityList->NextEnt(pEntity))
			{
				auto pPlayer = pEntity->As<CTFPlayer>();
				if (!pEntity->IsPlayer() || pEntity->entindex() == G::DebugTarget->entindex())
					continue;
#if !x86
				pPlayer->DrawServerHitboxes(TICK_INTERVAL * G::ServerHitboxesRate, true);
#endif
			}
		}
	}

	/*
	if (G::DebugVisuals)
	{
		for (int i = totalcmds - 1; i >= 0; i--)
		{
			s_flTime = 0.f;
			CUserCmd* pCmd = &cmds[totalcmds - 1 - i];
			if (pCmd)
				s_flTime = std::max(s_flTime, TICKS_TO_TIME(pCmd->command_number));
		}

		Store(reinterpret_cast<CTFPlayer*>(rcx));
	}
	*/

#if x86
	return CALL_ORIGINAL(ecx, edx, cmds, numcmds, totalcmds, dropped_packets, paused);
#else
	return CALL_ORIGINAL(rcx, cmds, numcmds, totalcmds, dropped_packets, paused);
#endif
}

#if x86
MAKE_HOOK(CTFWeaponBase_IncrementAmmo, S::CTFWeaponBase_IncrementAmmo(), void, __fastcall,
	void* ecx, void* edx)
#else
MAKE_HOOK(CTFWeaponBase_IncrementAmmo, S::CTFWeaponBase_IncrementAmmo(), void,
	void* rcx)
#endif
{
	if (G::DebugInfo)
	{
#if x86
		auto pWeapon = reinterpret_cast<CTFWeaponBase*>(ecx);
#else
		auto pWeapon = reinterpret_cast<CTFWeaponBase*>(rcx);
#endif
		auto pLocal = pWeapon->m_hOwnerEntity()->As<CTFPlayer>();
		if (pLocal && pWeapon)
		{
			SDK::Output("IncrementAmmo", std::format("{}\n\t{}, {}\n\t{}, {}",
				pWeapon->m_iClip1(),
				TIME_TO_TICKS(pLocal->m_flNextAttack() - I::GlobalVars->curtime),
				pLocal->m_flNextAttack() - I::GlobalVars->curtime,
				TIME_TO_TICKS(I::GlobalVars->curtime - pWeapon->m_flReloadPriorNextFire()),
				I::GlobalVars->curtime - pWeapon->m_flReloadPriorNextFire()).c_str());
		}
	}

#if x86
	CALL_ORIGINAL(ecx, edx);
#else
	CALL_ORIGINAL(rcx);
#endif
}