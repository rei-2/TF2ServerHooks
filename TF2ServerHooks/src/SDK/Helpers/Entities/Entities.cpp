#include "Entities.h"

#include "../../SDK.h"
#include "../../../Utils/Hash/FNV1A.h"

void CEntities::Store()
{
	for (CBaseEntity* pEntity = I::GlobalEntityList->FirstEnt(); pEntity; pEntity = I::GlobalEntityList->NextEnt(pEntity))
	{
		auto nClassID = pEntity->GetClassID();
		switch (nClassID)
		{
		case ETFClassID::CTFPlayerResource:
			m_pPlayerResource = pEntity->As<CTFPlayerResource>();
			break;
		case ETFClassID::CObjectSentrygun:
		case ETFClassID::CObjectDispenser:
		case ETFClassID::CObjectTeleporter:
			m_mGroups[EGroupType::BUILDINGS].push_back(pEntity);
			break;
		case ETFClassID::CBaseAnimating:
		{
			if (IsHealth(pEntity))
				m_mGroups[EGroupType::PICKUPS_HEALTH].push_back(pEntity);
			else if (IsAmmo(pEntity))
				m_mGroups[EGroupType::PICKUPS_AMMO].push_back(pEntity);
			else if (IsPowerup(pEntity))
				m_mGroups[EGroupType::PICKUPS_POWERUP].push_back(pEntity);
			else if (IsSpellbook(pEntity))
				m_mGroups[EGroupType::PICKUPS_SPELLBOOK].push_back(pEntity);
			break;
		}
		case ETFClassID::CTFAmmoPack:
			m_mGroups[EGroupType::PICKUPS_AMMO].push_back(pEntity);
			break;
		case ETFClassID::CBaseProjectile:
		case ETFClassID::CBaseGrenade:
		case ETFClassID::CTFWeaponBaseGrenadeProj:
		case ETFClassID::CTFWeaponBaseMerasmusGrenade:
		case ETFClassID::CTFGrenadePipebombProjectile:
		case ETFClassID::CTFStunBall:
		case ETFClassID::CTFBall_Ornament:
		case ETFClassID::CTFProjectile_Jar:
		case ETFClassID::CTFProjectile_Cleaver:
		case ETFClassID::CTFProjectile_JarGas:
		case ETFClassID::CTFProjectile_JarMilk:
		case ETFClassID::CTFProjectile_SpellBats:
		case ETFClassID::CTFProjectile_SpellKartBats:
		case ETFClassID::CTFProjectile_SpellMeteorShower:
		case ETFClassID::CTFProjectile_SpellMirv:
		case ETFClassID::CTFProjectile_SpellPumpkin:
		case ETFClassID::CTFProjectile_SpellSpawnBoss:
		case ETFClassID::CTFProjectile_SpellSpawnHorde:
		case ETFClassID::CTFProjectile_SpellSpawnZombie:
		case ETFClassID::CTFProjectile_SpellTransposeTeleport:
		case ETFClassID::CTFProjectile_Throwable:
		case ETFClassID::CTFProjectile_ThrowableBreadMonster:
		case ETFClassID::CTFProjectile_ThrowableBrick:
		case ETFClassID::CTFProjectile_ThrowableRepel:
		case ETFClassID::CTFBaseRocket:
		case ETFClassID::CTFFlameRocket:
		case ETFClassID::CTFProjectile_Arrow:
		case ETFClassID::CTFProjectile_GrapplingHook:
		case ETFClassID::CTFProjectile_HealingBolt:
		case ETFClassID::CTFProjectile_Rocket:
		case ETFClassID::CTFProjectile_BallOfFire:
		case ETFClassID::CTFProjectile_MechanicalArmOrb:
		case ETFClassID::CTFProjectile_SentryRocket:
		case ETFClassID::CTFProjectile_SpellFireball:
		case ETFClassID::CTFProjectile_SpellLightningOrb:
		case ETFClassID::CTFProjectile_SpellKartOrb:
		case ETFClassID::CTFProjectile_EnergyBall:
		case ETFClassID::CTFProjectile_Flare:
		case ETFClassID::CTFBaseProjectile:
		case ETFClassID::CTFProjectile_EnergyRing:
		//case ETFClassID::CTFProjectile_Syringe:
		{
			m_mGroups[EGroupType::WORLD_PROJECTILES].push_back(pEntity);
			break;
		}
		case ETFClassID::CCaptureFlag:
			m_mGroups[EGroupType::WORLD_OBJECTIVE].push_back(pEntity);
			break;
		case ETFClassID::CHeadlessHatman:
		case ETFClassID::CTFTankBoss:
		case ETFClassID::CMerasmus:
		case ETFClassID::CZombie:
		case ETFClassID::CEyeballBoss:
			m_mGroups[EGroupType::WORLD_NPC].push_back(pEntity);
			break;
		case ETFClassID::CTFPumpkinBomb:
		case ETFClassID::CTFGenericBomb:
			m_mGroups[EGroupType::WORLD_BOMBS].push_back(pEntity);
			break;
		case ETFClassID::CCurrencyPack:
			m_mGroups[EGroupType::PICKUPS_MONEY].push_back(pEntity);
			break;
		}
	}

	for (CBaseEntity* pEntity = I::GlobalEntityList->FirstEnt(); pEntity; pEntity = I::GlobalEntityList->NextEnt(pEntity))
	{
		auto pPlayer = pEntity->As<CTFPlayer>();
		if (!pEntity->IsPlayer())
			continue;

		m_mGroups[EGroupType::PLAYERS].push_back(pEntity);
	}

	int iLag;
	{
		static int iStaticTickcout = I::GlobalVars->tickcount;
		iLag = I::GlobalVars->tickcount - iStaticTickcout - 1;
		iStaticTickcout = I::GlobalVars->tickcount;
	}

	static auto sv_maxusrcmdprocessticks = U::ConVars.FindVar("sv_maxusrcmdprocessticks");
	int iMaxShift = sv_maxusrcmdprocessticks ? sv_maxusrcmdprocessticks->GetInt() : 24;
	/*
	for (CBaseEntity* pEntity = I::GlobalEntityList->FirstEnt(); pEntity; pEntity = I::GlobalEntityList->NextEnt(pEntity))
	{
		auto pPlayer = pEntity->As<CTFPlayer>();
		if (!pEntity->IsPlayer())
			continue;

		bool bDormant = pPlayer->IsDormant();

		float flOldSimTime = m_mOldSimTimes[n] = m_mSimTimes.contains(n) ? m_mSimTimes[n] : pPlayer->m_flOldSimulationTime();
		float flSimTime = m_mSimTimes[n] = pPlayer->m_flSimulationTime();
		float flDeltaTime = m_mDeltaTimes[n] = TICKS_TO_TIME(std::clamp(TIME_TO_TICKS(flSimTime - flOldSimTime) - iLag, 0, iMaxShift));
		if (flDeltaTime)
			m_mSetTicks[n] = I::GlobalVars->tickcount;
		m_mChokes[n] = I::GlobalVars->tickcount - m_mSetTicks[n];

		if (!flDeltaTime)
			continue;
		else if (bDormant)
		{
			m_mBones[n].first = false;
			continue;
		}

		m_bSettingUpBones = true;
		m_mBones[n].first = pPlayer->SetupBones(m_mBones[n].second, MAXSTUDIOBONES, BONE_USED_BY_ANYTHING, flSimTime);
		m_bSettingUpBones = false;
	}
	*/
}

void CEntities::Clear(bool bShutdown)
{
	m_pPlayerResource = nullptr;
	m_mGroups.clear();
	m_bSettingUpBones = false;

	if (bShutdown)
	{
		m_mSimTimes.clear();
		m_mOldSimTimes.clear();
		m_mDeltaTimes.clear();
		m_mChokes.clear();
		m_mBones.clear();
	}
}

bool CEntities::IsHealth(CBaseEntity* pEntity)
{
	switch (FNV1A::Hash32(pEntity->GetModelName().ToCStr()))
	{
	case FNV1A::Hash32Const("models/items/banana/plate_banana.mdl"):
	case FNV1A::Hash32Const("models/items/medkit_small.mdl"):
	case FNV1A::Hash32Const("models/items/medkit_medium.mdl"):
	case FNV1A::Hash32Const("models/items/medkit_large.mdl"):
	case FNV1A::Hash32Const("models/items/medkit_small_bday.mdl"):
	case FNV1A::Hash32Const("models/items/medkit_medium_bday.mdl"):
	case FNV1A::Hash32Const("models/items/medkit_large_bday.mdl"):
	case FNV1A::Hash32Const("models/items/plate.mdl"):
	case FNV1A::Hash32Const("models/items/plate_sandwich_xmas.mdl"):
	case FNV1A::Hash32Const("models/items/plate_robo_sandwich.mdl"):
	case FNV1A::Hash32Const("models/props_medieval/medieval_meat.mdl"):
	case FNV1A::Hash32Const("models/workshopweapons/c_models/c_chocolate/plate_chocolate.mdl"):
	case FNV1A::Hash32Const("models/workshopweapons/c_models/c_fishcake/plate_fishcake.mdl"):
	case FNV1A::Hash32Const("models/props_halloween/halloween_medkit_small.mdl"):
	case FNV1A::Hash32Const("models/props_halloween/halloween_medkit_medium.mdl"):
	case FNV1A::Hash32Const("models/props_halloween/halloween_medkit_large.mdl"):
	case FNV1A::Hash32Const("models/items/ld1/mushroom_large.mdl"):
	case FNV1A::Hash32Const("models/items/plate_steak.mdl"):
	case FNV1A::Hash32Const("models/props_brine/foodcan.mdl"):
		return true;
	}
	return false;
}

bool CEntities::IsAmmo(CBaseEntity* pEntity)
{
	switch (FNV1A::Hash32(pEntity->GetModelName().ToCStr()))
	{
	case FNV1A::Hash32Const("models/items/ammopack_small.mdl"):
	case FNV1A::Hash32Const("models/items/ammopack_medium.mdl"):
	case FNV1A::Hash32Const("models/items/ammopack_large.mdl"):
	case FNV1A::Hash32Const("models/items/ammopack_large_bday.mdl"):
	case FNV1A::Hash32Const("models/items/ammopack_medium_bday.mdl"):
	case FNV1A::Hash32Const("models/items/ammopack_small_bday.mdl"):
		return true;
	}
	return false;
}

bool CEntities::IsPowerup(CBaseEntity* pEntity)
{
	switch (FNV1A::Hash32(pEntity->GetModelName().ToCStr()))
	{
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_agility.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_crit.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_defense.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_haste.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_king.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_knockout.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_plague.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_precision.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_reflect.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_regen.mdl"):
	//case FNV1A::Hash32Const("models/pickups/pickup_powerup_resistance.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_strength.mdl"):
	//case FNV1A::Hash32Const("models/pickups/pickup_powerup_strength_arm.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_supernova.mdl"):
	//case FNV1A::Hash32Const("models/pickups/pickup_powerup_thorns.mdl"):
	//case FNV1A::Hash32Const("models/pickups/pickup_powerup_uber.mdl"):
	case FNV1A::Hash32Const("models/pickups/pickup_powerup_vampire.mdl"):
		return true;
	}
	return false;
}

bool CEntities::IsSpellbook(CBaseEntity* pEntity)
{
	switch (FNV1A::Hash32(pEntity->GetModelName().ToCStr()))
	{
	case FNV1A::Hash32Const("models/props_halloween/hwn_spellbook_flying.mdl"):
	case FNV1A::Hash32Const("models/props_halloween/hwn_spellbook_upright.mdl"):
	case FNV1A::Hash32Const("models/props_halloween/hwn_spellbook_upright_major.mdl"):
	case FNV1A::Hash32Const("models/items/crystal_ball_pickup.mdl"):
	case FNV1A::Hash32Const("models/items/crystal_ball_pickup_major.mdl"):
	case FNV1A::Hash32Const("models/props_monster_mash/flask_vial_green.mdl"):
	case FNV1A::Hash32Const("models/props_monster_mash/flask_vial_purple.mdl"): // prop_dynamic in the map, probably won't work
		return true;
	}
	return false;
}

CTFPlayerResource* CEntities::GetPR() { return m_pPlayerResource; }

const std::vector<CBaseEntity*>& CEntities::GetGroup(const EGroupType& Group) { return m_mGroups[Group]; }

float CEntities::GetSimTime(CBaseEntity* pEntity) { int iIndex = pEntity->entindex(); return m_mSimTimes.contains(iIndex) ? m_mSimTimes[iIndex] : pEntity->m_flSimulationTime(); }
float CEntities::GetOldSimTime(CBaseEntity* pEntity) { int iIndex = pEntity->entindex(); return m_mOldSimTimes.contains(iIndex) ? m_mOldSimTimes[iIndex] : pEntity->m_flOldSimulationTime(); }
float CEntities::GetDeltaTime(int iIndex) { return m_mDeltaTimes.contains(iIndex) ? m_mDeltaTimes[iIndex] : TICK_INTERVAL; }
int CEntities::GetChoke(int iIndex) { return m_mChokes.contains(iIndex) ? m_mChokes[iIndex] : 0; }
matrix3x4* CEntities::GetBones(int iIndex) { return m_mBones[iIndex].first ? m_mBones[iIndex].second : nullptr; }

bool CEntities::IsSettingUpBones() { return m_bSettingUpBones; }