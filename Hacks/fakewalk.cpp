//
//  fakewalk.cpp
//  vHook
//
//  Created by Warlauke on 10/20/17.
//  Copyright © 2017 ViKiNG. All rights reserved.
//

#include "fakewalk.h"

void Fakewalk(CUserCmd* cmd, C_BaseEntity* local)
{
    
    if(!vars.misc.fakewalk)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    C_BaseEntity* localplayer = (C_BaseEntity*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!localplayer)
        return;
    
    if(!pInputSystem->IsButtonDown(MOUSE_4))
        return;
    
    static int iChoked = 0;
    
    iChoked = iChoked > 7  ? 0 : iChoked + 1;
    cmd->forwardmove = iChoked < 2 || iChoked > 5 ? 0 : cmd->forwardmove;
    cmd->sidemove = iChoked < 2 || iChoked > 5 ? 0 : cmd->sidemove;
    
    *bSendPacket = iChoked < 1;
    
}


