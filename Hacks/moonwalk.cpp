//
//  moonwalk.cpp
//  vHook
//
//  Created by Joshua Janssen on 19/06/2018.
//  Copyright © 2018 ViKiNG. All rights reserved.
//

#include "moonwalk.h"

#include "bhop.h"

void MoonWalk::CreateMove( CUserCmd* cmd )
{
    if (!vars.misc.moon)
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!localplayer)
        return;
    
    if(pInputSystem->IsButtonDown(KEY_W))
    {
        cmd->forwardmove = 450;
    }
    
    if(pInputSystem->IsButtonDown(KEY_S))
    {
        cmd->forwardmove = -450;
    }
    
    if(pInputSystem->IsButtonDown(KEY_D))
    {
        cmd->sidemove = 450;
    }
    
    if(pInputSystem->IsButtonDown(KEY_A))
    {
        cmd->sidemove = -450;
    }
    
    pEngine->ExecuteClientCmd( "bind w +back; bind s +forward; bind a +moveright; bind d +moveleft" );
    
}
