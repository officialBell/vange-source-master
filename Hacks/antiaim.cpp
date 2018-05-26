//
//  antiaim.cpp
//  vHook
//

#include "antiaim.h"
#include "INetChannelInfo.h"

Vector atTargets;

float GetBestHeadAngle(CUserCmd* cmd, C_BasePlayer* local)
{
    float Back, Right, Left;
    
    Vector src3D, dst3D, forward, right, up, src, dst;
    trace_t tr;
    Ray_t backray, rightray, leftray;
    CTraceFilter filter;
    
    Vector ViewAngles = cmd->viewangles;
    
    AngleVectors(ViewAngles, &forward);
    //AngleVectors(angles, forward);
    
    filter.pSkip = local;
    src3D = local->GetEyePosition();
    dst3D = src3D + (forward * 384.f);
    
    backray.Init(src3D, dst3D);
    pEngineTrace->TraceRay(backray, MASK_SHOT, &filter, &tr);
    Back = (tr.endpos - tr.startpos).Length();
    
    rightray.Init(src3D + right * 35.f, dst3D + right * 35.f);
    pEngineTrace->TraceRay(rightray, MASK_SHOT, &filter, &tr);
    Right = (tr.endpos - tr.startpos).Length();
    
    leftray.Init(src3D - right * 35.f, dst3D - right * 35.f);
    pEngineTrace->TraceRay(leftray, MASK_SHOT, &filter, &tr);
    Left = (tr.endpos - tr.startpos).Length();
    
    if (Left > Right)
        return (cmd->viewangles.y - 90.f);
    else if (Right > Left)
        return (cmd->viewangles.y + 90.f);
    else if (Back > Right || Back > Left)
        return (cmd->viewangles.y - 180.f);
    
    return 0;
}


void antiResolverFlip(CUserCmd* cmd, C_BaseEntity* local)
{
    if(!vars.misc.antiResolverFlip)
        return;
    
    static bool antiResolverFlip = false;
    if (cmd->viewangles.y == local->GetLowerBodyYawTarget())
    {
        if (antiResolverFlip)
            cmd->viewangles.y += 60.f;
        else
            cmd->viewangles.y -= 60.f;
        
        antiResolverFlip = !antiResolverFlip;
    }
}

float next_lby_update;
float old_lby;

float corrected_time( CUserCmd* ucmd, C_BaseEntity* local)
{
    static int g_tick = 0;
    static CUserCmd* g_pLastCmd = nullptr;
    if ( !g_pLastCmd || g_pLastCmd->hasbeenpredicted ) {
        g_tick = local->GetTickBase( );
    } else {
        // Required because prediction only runs on frames, not ticks
        // So if your framerate goes below tickrate, m_nTickBase won't update every tick
        ++g_tick;
    }
    g_pLastCmd = ucmd;
    float curtime = g_tick * pGlobals->interval_per_tick;
    return curtime;
}

bool lby_updated( CUserCmd* cmd, C_BaseEntity* local )
{
    float server_time = corrected_time(cmd, local);
    static bool once = true;
    
    if ( once && local->GetLowerBodyYawTarget( ) != old_lby ) {
        old_lby = local->GetLowerBodyYawTarget( );
        next_lby_update = server_time + 1.1;
        once = false;
    }
    
    bool on_ground = local->GetFlags( ) & FL_ONGROUND;
    
    if ( server_time >= next_lby_update && on_ground ) {
        next_lby_update = server_time + 1.1;
        return true;
    }
    
    return false;
}

void do_real2(CUserCmd* cmd, C_BaseEntity* local){
    
    static bool side1 = false;
    static bool side2 = false;
    static bool back = false;
    
    if (pInputSystem->IsButtonDown(KEY_RIGHT)) {
        side1 = true;    side2 = false;    back = false;
    }
    if (pInputSystem->IsButtonDown(KEY_LEFT)) {
        side1 = false;    side2 = true;    back = false;
    }
    
    if ( side1 ){ // Right
        cmd->viewangles.y -= 90.f;
    }
    
    if ( side2 ){ // Left
        cmd->viewangles.y += 90;
    }
    
    if (lby_updated(cmd, local)) {
        cmd->viewangles.y += vars.misc.delta;
        //cmd->viewangles.y += 115.f; // less then 180 to prevent 979 animation, but less then 120 so its harder to predict
    }
    
    if (pInputSystem->IsButtonDown(KEY_X)){ // Should fuck people up trying to resolve you
        float factor;
        if(!(local->GetFlags() & FL_ONGROUND)){
            factor =  360.0 / M_PHI;
            cmd->viewangles.y = fmodf(pGlobals->curtime * factor, 180.0);
        }
        else{
           cmd->viewangles.y = rand() % (360 - -360 + 1 ) + -360;
        }
    }
}

void do_real(CUserCmd* cmd, C_BaseEntity* local) {
    if (local->GetVelocity().Length2D() > 1.f) { // moving, lby starts updating at > 1.f velocity
        cmd->viewangles.y += 180.0f + rand() % (35 - -35 + 1 ) + -35;
    } else
    { // if we are standing still and our lby isn't updating
        if (lby_updated(cmd, local)) {
            cmd->viewangles.y = 90.f;
            cmd->viewangles.y += 115.f; // less then 180 to prevent 979 animation, but less then 120 so its harder to predict
        } else
        {
            cmd->viewangles.y = 90.f;
        }
    }
}

void do_fake(CUserCmd* cmd) {
    *bSendPacket = true;
    cmd->viewangles.y = rand() % (180 - -180 + 1 ) + -180;
}

void DoAntiaim(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon)
{
    
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (!weapon)
        return;
    
    if (weapon->IsGrenade())
        return;
    
    static bool bFlip = false;
    bFlip = !bFlip;
    
    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_USE)
        return;
    
    cmd->viewangles.x = 89.f;
    
    if (!vars.misc.fakelag) {
        *bSendPacket = cmd->command_number % 2;
    }
    
    if (!bSendPacket || vars.misc.fakeaa) {
        do_fake(cmd);
    } else {
        do_real2(cmd, local);
    }
    
    cmd->viewangles.ClampAngles();
}


/*
void DoAntiaim(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bPacket)
{
    
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (weapon->IsGrenade())
        return;
    
    bool Freestanding = GetBestHeadAngle;
    
    static bool fakeswitch = false;
    static bool bFlip = false;
    bool bAttack = true;
    bFlip = !bFlip;
    int maxJitter;
    int random;
    float temp;

    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_USE)
        return;
    
    if (!vars.misc.fakelag) {
        *bSendPacket = cmd->command_number % 2;
    }
    
    if(cmd->buttons & IN_ATTACK && (bAttack))
    {
        bPacket = false;
    }
    else
    {
        bPacket = true;
        
        if (vars.misc.fakeaa) // Fake AntiAim
        {
            fakeswitch = !fakeswitch;
            if (fakeswitch)
                bPacket = false;
            else
                bPacket = true;
        }
        
        if(vars.misc.aaX > 0)
        {
            bool clamp;
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Emotion)
            {
                cmd->viewangles.x = 89;
            }
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Dance){
                static float pDance = 0.0f;
                pDance += 45.0f;
                if (pDance > 100)
                    pDance = 0.0f;
                else if (pDance > 75.f)
                    cmd->viewangles.x = -89.f;
                else if (pDance < 75.f)
                    cmd->viewangles.x = 89.f;
            }
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::FakeDown){
                clamp = false;
                cmd->viewangles.x = bFlip ? 89.0f : 69.0f;;
            }
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::FakeUp)
            {
                clamp = false;
                cmd->viewangles.x = bFlip ? 89.0f : -89.0f;;
            }
            
        } // END OF PITCH
        
        if(vars.misc.aaY > 0)
        {
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::Backwards)
            {
                cmd->viewangles.y -= 179.f;
            }
            
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::LowerYaw)
            {
                //cmd->viewangles.y = Freestanding; // I wished this fucking worked
                static int fakeTick = 0;
                fakeTick++;
                
                if (vars.misc.fakeaa)
                {
                    if (!bSendPacket)
                    {
                        
                        if (fakeTick < 300)
                            cmd->viewangles.y += 67.57f;
                        else if (fakeTick > 300)
                            cmd->viewangles.y -= 67.15f;
                        
                        if (fakeTick < 300)
                            cmd->viewangles.y += 67.57f;
                        else if (fakeTick > 300)
                            cmd->viewangles.y -= 67.15f;
                        
                        if (fakeTick > 600)
                            fakeTick = 0;
                        
                    }
                    else
                    {
                        cmd->viewangles.y += 180.f;
                    }
                }
                else
                {
                    cmd->viewangles.y -= 180.f;
                }
            }
            
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::manedgee)
            {
                bool air = !(local->GetFlags() & FL_ONGROUND); // in air
                
                static bool enabled     = false;
                static bool check       = false;
                float factor;
                
                if ( air ) // In air
                {
                    factor =  360.0 / M_PHI;
                    cmd->viewangles.y = fmodf(pGlobals->curtime * factor, 180.0);
                }
                else
                { // On ground
                    if (pInputSystem->IsButtonDown(KEY_X))
                        
                    {
                        if (!check)
                            enabled = !enabled;
                        check = true;
                    }
                    else
                    {
                        check = false;
                    }
                    
                    if ( enabled )
                    {
                        cmd->viewangles.y += 90.f;
                    }
                    
                    else
                    {
                        cmd->viewangles.y -= 90.0f;
                        
                    }
                    
                    if (lby_updated(cmd, local)) {
                        cmd->viewangles.y += 115.f; // less then 180 to prevent 979 animation, but less then 120 so its harder to predict
                    }
                }
            }
            
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::LBYbreak)
            {
                static bool side1 = false;
                static bool side2 = false;
                static bool back = false;
                
                if (pInputSystem->IsButtonDown(KEY_RIGHT)) {
                    side1 = true;    side2 = false;    back = false;
                }
                if (pInputSystem->IsButtonDown(KEY_LEFT)) {
                    side1 = false;    side2 = true;    back = false;
                }
                
                if ( side1 ){ // Right
                    cmd->viewangles.y -= 90.f;
                }
                
                if ( side2 ){ // Left
                    cmd->viewangles.y += 90;
                }
                
                if (lby_updated(cmd, local)) {
                    cmd->viewangles.y += 115.f; // less then 180 to prevent 979 animation, but less then 120 so its harder to predict
                }
                
                if (pInputSystem->IsButtonDown(KEY_X)){ // Should fuck people up trying to resolve you
                    int random = rand() % 100;
                    if (random < 35 + (rand() % 15))
                    {
                        cmd->viewangles.y = rand() % (180 - -180 + 1 ) + -180;
                    }
                    
                    else if (random < 85 + (rand() % 15))
                    {
                        cmd->viewangles.y = rand() % (360 - -360 + 1 ) + -360;
                    }
                }
            }
            
        } // END OF YAW
        
        if( vars.misc.FaaY > 0 && ( (vars.misc.fakeaa && bPacket)|| !bSendPacket ) )
        {
            if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::Rand) {
                cmd->viewangles.y = rand() % (180 - -180 + 1 ) + -180;
            }
            
            if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::Rand2) {
                int random = rand() % 100;
                int maxJitter = rand() % (85 - 70 + 1) + 70;
                local->GetLowerBodyYawTarget() - (rand() % maxJitter);
                if (random < 35 + (rand() % 15))
                {
                    cmd->viewangles.y -= local->GetLowerBodyYawTarget() - (rand() % maxJitter);;
                }
                
                else if (random < 85 + (rand() % 15))
                {
                    cmd->viewangles.y += local->GetLowerBodyYawTarget() - (rand() % maxJitter);;
                }
            }
            
            if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::Rand3){
                cmd->viewangles.y = rand() % (360 - -360 + 1 ) + -360;
                //cmd->viewangles.y = RandomFloat(35, 35);
            }
            
            if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::lower135){
                static int ChokedPackets = -1;
                ChokedPackets++;
                if (ChokedPackets < 1)
                {
                    *bSendPacket = true;
                    cmd->viewangles.y += 180;
                    ChokedPackets = -1;
                }
                else
                {
                    *bSendPacket = false;
                    ChokedPackets = -1;
                }
            }
            
            if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::oneeighro){ // 180 rotation
                static float factor;
                static int ChokedPackets = -1;
                ChokedPackets++;
                if (ChokedPackets < 1)
                {
                    *bSendPacket = true;
                    factor =  360.0 / M_PHI;
                    cmd->viewangles.y += 180+(pGlobals->curtime * factor, 180.0);
                    ChokedPackets = -1;
                }
                else
                {
                    *bSendPacket = false;
                    ChokedPackets = -1;
                }
            }
                
            
        } // End Of FakeAA Yaw
        
        
        
        if( vars.misc.MaaY > 0)
        {
            float factor;
            
            if(vars.misc.MaaY == VIEW_ANTIIAIM_MYAW::LowerBody)
            {
                {
                    static int fakeTick = 0;
                    fakeTick++;
                    
                    if (vars.misc.fakeaa)
                    {
                        if (!bSendPacket)
                        {
                            
                            if (fakeTick < 300)
                                cmd->viewangles.y += 67.57f;
                            else if (fakeTick > 300)
                                cmd->viewangles.y -= 67.15f;
                            
                            if (fakeTick < 300)
                                cmd->viewangles.y += 67.57f;
                            else if (fakeTick > 300)
                                cmd->viewangles.y -= 67.15f;
                            
                            if (fakeTick > 600)
                                fakeTick = 0;
                            
                        }
                        else
                        {
                            cmd->viewangles.y += 180.f;
                        }
                    }
                    else
                    {
                        cmd->viewangles.y += 180.f;
                    }
                    
                }
            }
            
            if(vars.misc.MaaY == VIEW_ANTIIAIM_MYAW::BackJitter)
            {
                cmd->viewangles.y -= 180;
                random = rand() % 100;
                maxJitter = rand() % (85-70+1) + 70;
                temp = maxJitter - (rand() % maxJitter);
                if(random < 35 + (rand() % 15))
                    cmd->viewangles.y -= temp;
                else if(random < 85 + (rand()% 15))
                    cmd->viewangles.y += temp;
            }
            
            if(vars.misc.MaaY == VIEW_ANTIIAIM_MYAW::Rotate)
            {
                factor =  360.0 / M_PHI;
                cmd->viewangles.y = fmodf(pGlobals->curtime * factor, 180.0);
            }
        } // End of Moving on ground Yaw
        
        
        if(vars.misc.AaaY > 0)
        {
            float factor;
            
            if(vars.misc.AaaY == VIEW_ANTIIAIM_AYAW::LowerBod)
            {
                static int fakeTick = 0;
                fakeTick++;
                
                if (vars.misc.fakeaa)
                {
                    if (!bSendPacket)
                    {
                        
                        if (fakeTick < 300)
                            cmd->viewangles.y += 67.57f;
                        else if (fakeTick > 300)
                            cmd->viewangles.y -= 67.15f;
                        
                        if (fakeTick < 300)
                            cmd->viewangles.y += 67.57f;
                        else if (fakeTick > 300)
                            cmd->viewangles.y -= 67.15f;
                        
                        if (fakeTick > 600)
                            fakeTick = 0;
                        
                    }
                    else
                    {
                        cmd->viewangles.y += 180.f;
                    }
                }
                else
                {
                    cmd->viewangles.y += 180.f;
                }
            }
            if(vars.misc.AaaY == VIEW_ANTIIAIM_AYAW::Rotatee)
            {
                factor =  360.0 / M_PHI;
                cmd->viewangles.y = fmodf(pGlobals->curtime * factor, 180.0);
            }
            
        } // End of Moving in Air Yaw AA
        
    }
    cmd->viewangles.ClampAngles();
}*/




    
    /*if (!bSendPacket) {
        do_real(cmd, local);
    } else {
        do_fake(cmd);
    }*/
    
    //cmd->viewangles.ClampAngles();

