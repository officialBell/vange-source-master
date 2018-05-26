//
//  aimbot.hpp
//  vHook
//
#pragma once

#include "main.h"

void DoAim(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, float& flForward, float& flSide);
void Hitchance(C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon);


namespace Aimbot
{
    extern C_BaseEntity* curTarget;
}

