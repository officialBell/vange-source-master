//
//  aimbot.cpp
//  vHook
//

#include "aimbot.h"
#include "autoshoot.h"
#include "antiaim.h"
#include "autowall.h"

C_BaseEntity* Aimbot::curTarget = nullptr;

int MakeHitscan(C_BaseEntity* entity)
{
    vector<int> hitboxes;
    
    if(vars.aimbot.hitscantype == 1)
    {
        // high
        hitboxes.push_back(HITBOX_HEAD);
        hitboxes.push_back(HITBOX_NECK);
        hitboxes.push_back(HITBOX_LOWER_NECK);
        hitboxes.push_back(HITBOX_PELVIS);
        hitboxes.push_back(HITBOX_BODY);
        hitboxes.push_back(HITBOX_THORAX);
        hitboxes.push_back(HITBOX_CHEST);
        hitboxes.push_back(HITBOX_UPPER_CHEST);
        hitboxes.push_back(HITBOX_RIGHT_THIGH);
        hitboxes.push_back(HITBOX_LEFT_THIGH);
        hitboxes.push_back(HITBOX_RIGHT_CALF);
        hitboxes.push_back(HITBOX_LEFT_CALF);
        hitboxes.push_back(HITBOX_RIGHT_FOOT);
        hitboxes.push_back(HITBOX_LEFT_FOOT);
        hitboxes.push_back(HITBOX_RIGHT_HAND);
        hitboxes.push_back(HITBOX_LEFT_HAND);
        hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
        hitboxes.push_back(HITBOX_RIGHT_FOREARM);
        hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
        hitboxes.push_back(HITBOX_LEFT_FOREARM);
        hitboxes.push_back(HITBOX_MAX);
    }
    
    if(vars.aimbot.hitscantype == 2)
    {
        hitboxes.push_back(HITBOX_HEAD);
        hitboxes.push_back(HITBOX_NECK);
        hitboxes.push_back(HITBOX_UPPER_CHEST);
        hitboxes.push_back(HITBOX_CHEST);
        hitboxes.push_back(HITBOX_BODY);
        hitboxes.push_back(HITBOX_PELVIS);
        hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
        hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
        hitboxes.push_back(HITBOX_RIGHT_THIGH);
        hitboxes.push_back(HITBOX_LEFT_THIGH);
    }
    
    if(vars.aimbot.hitscantype == 3)
    {
        hitboxes.push_back(HITBOX_HEAD);
        hitboxes.push_back(HITBOX_NECK);
        hitboxes.push_back(HITBOX_UPPER_CHEST);
        hitboxes.push_back(HITBOX_CHEST);
        hitboxes.push_back(HITBOX_BODY);
        hitboxes.push_back(HITBOX_PELVIS);
    }
    
    if(vars.aimbot.hitscantype == 4)
    {
        hitboxes.push_back(HITBOX_PELVIS);
        hitboxes.push_back(HITBOX_BODY);
        hitboxes.push_back(HITBOX_THORAX);
        hitboxes.push_back(HITBOX_CHEST);
        hitboxes.push_back(HITBOX_UPPER_CHEST);
        hitboxes.push_back(HITBOX_RIGHT_THIGH);
        hitboxes.push_back(HITBOX_LEFT_THIGH);
        hitboxes.push_back(HITBOX_RIGHT_CALF);
        hitboxes.push_back(HITBOX_LEFT_CALF);
        hitboxes.push_back(HITBOX_RIGHT_FOOT);
        hitboxes.push_back(HITBOX_LEFT_FOOT);
        hitboxes.push_back(HITBOX_RIGHT_HAND);
        hitboxes.push_back(HITBOX_LEFT_HAND);
        hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
        hitboxes.push_back(HITBOX_RIGHT_FOREARM);
        hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
        hitboxes.push_back(HITBOX_LEFT_FOREARM);
        
    }
    
    if(vars.aimbot.hitscan)
    {
        
        int highestdamage_hitbox = 0;
        int highestdamage = 0;
        
        for(auto hit : hitboxes)
        {
            Vector vDest = GetHitboxPosition(entity, hit);
            float thisDamage = 0.f;
            Autowall::FireBulletData data;
            
            thisDamage = Autowall::GetDamage(vDest, true, data);
            
            if(thisDamage > highestdamage)
            {
                highestdamage = thisDamage;
                highestdamage_hitbox = hit;
            }
            
        }
        
        return highestdamage_hitbox;
    }
    else
    {
        return vars.aimbot.hitbox;
    }
    
}


void Hitchance(C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon)
{
    if(vars.aimbot.hitchance)
    {
        float hitchance = 101;
        if (!pWeapon) return 0;
        if(vars.aimbot.accuracyhithcance > 1)
        {
            float inaccuracy = pWeapon->GetInaccuracy();
            if (inaccuracy == 0) inaccuracy = 0.0000001;
            inaccuracy = 1 / inaccuracy;
            hitchance = inaccuracy;
        }
        return hitchance;
    }
}


void DoAim(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, float& flForward, float& flSide)
{
    
    if(!vars.aimbot.enabled)
        return;
    
    Vector eyepos = local->GetEyePosition();
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity == local)
            continue;
        
        if(entity->GetTeam() == local->GetTeam())
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetImmune())
            continue;
        
        if(weapon->GetAmmo() < 1)
            continue;
        
        if(weapon->IsKnife() || weapon->IsBomb())
            continue;
        
        if(gCorrections[entity->GetIndex()].whitelist)
            continue;
        
        Vector vFrom, vTo;
        
        Aimbot::curTarget = entity;
        
        vFrom = GetHitboxPosition(entity, MakeHitscan(entity));
        
        vTo = CalcAngle(eyepos, vFrom);
        
        auto isVISIBLE = IsVisible(local, entity);
        float getdmg = 0.f;
        Autowall::FireBulletData data;
        bool canHit = false;
        
        if(vars.aimbot.autowall)
        {
            getdmg = Autowall::GetDamage(vFrom, true, data);
            canHit = getdmg >= vars.aimbot.mindmg;
        }
        
        // FOV HERE
        
        atTargets = vTo;
        
        if(canHit || isVISIBLE)
        {
            if(GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) <= vars.aimbot.FovToPlayer)
            {
                if(vars.aimbot.autoshoot)
                {
                    //pCmd->buttons |= IN_ATTACK;
                    AutoShoot(local, weapon, pCmd);
                }
                
                if(vars.aimbot.autocock)
                {
                    //pCmd->buttons |= IN_ATTACK;
                    AutoCock(pCmd, weapon);
                }
                
                if (vars.aimbot.autoscope && weapon->GetCSWpnData()->m_iZoomLevels > 0 && !local->IsScoped())
                {
                    pCmd->buttons |= IN_ATTACK2;
                }
                
                if(vars.aimbot.autocrouch)
                {
                    pCmd->buttons |= IN_DUCK;
                }
                
                
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(pCmd->buttons & IN_ATTACK)
                {
                    if(!vars.aimbot.silent)
                    {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    }
                    else
                    {
                        pCmd->viewangles = vTo;
                    }
                    
                }
                
            }
            
        }
        
    }
    
}













