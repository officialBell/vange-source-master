#include "main.h"

/*
 
 ...
 ;::::;
 ;::::; :;
 ;:::::'   :;
 ;:::::;     ;.
 ,:::::'       ;           OOO
 ::::::;       ;          OOOOO
 ;:::::;       ;         OOOOOOOO
 ,;::::::;     ;'         / OOOOOOO
 ;:::::::::`. ,,,;.        /  / DOOOOOO
 .';:::::::::::::::::;,     /  /     DOOOO
 ,::::::;::::::;;;;::::;,   /  /        DOOO
 ;`::::::`'::::::;;;::::: ,#/  /          DOOO
 :`:::::::`;::::::;;::: ;::#  /            DOOO
 ::`:::::::`;:::::::: ;::::# /              DOO
 `:`:::::::`;:::::: ;::::::#/               DOO
 :::`:::::::`;; ;:::::::::##                OO
 ::::`:::::::`;::::::::;:::#                OO
 `:::::`::::::::::::;'`:;::#                O
 `:::::`::::::::;' /  / `:#
 ::::::`:::::;'  /  /   `#
 
 its supposed to be a grim reaper
 
 */

RecvVarProxyFn OldProxy_Y; //OldProxy_X;

// Pitch Resolver
/*
 float AAA_Pitch(C_BaseEntity* entity){
 int index = entity->GetIndex();
 float angle = gCorrections[index].x;
 
 angle = 89;
 }
 */

float AAA_Yaw(C_BaseEntity* entity)
{
    int index = entity->GetIndex();
    float angle = gCorrections[index].y;
    
    bool LBYbreak;
    for (int i = 0; i < 13; i++)
    {
        entity->GetAnimTime();
    }
    
    bool IsMovingOnInAir;
    //Check if player has a velocity greater than 0 (moving) and if they are onground.
    !(entity->GetFlags() & FL_ONGROUND);
    
    bool OnGround;
    //Check if player has a velocity greater than 0 (moving) and if they are onground.
    entity->GetFlags() & FL_ONGROUND;
    
    bool MovingOnGround;
    //Check if player has a velocity greater than 0 (moving) and if they are onground.
    entity->GetVelocity().Length2D() > 45.f && entity->GetFlags() & FL_ONGROUND;
    
    // Fake Walk dectection
    bool maybeFakeWalking;
    MovingOnGround && entity->GetVelocity().Length2D() < 36.0f;
    
    bool HasFakeHead;
    //lby should update if distance from lby to eye angles exceeds 35 degrees
    abs(angle - entity->GetLowerBodyYawTarget()) > 35;
    
    
    bool Lbywithin35;
    //lby should update if distance from lby to eye angles less than 35 degrees
    abs(angle - entity->GetLowerBodyYawTarget()) < 35;
    
    int shotmissed = 0;
    bool shots = 1;
    bool bLowerBodyUpdated;
    
    if (vars.aimbot.yresolve == 1)
    {
        if (IsMovingOnInAir)
        {
            switch (shots % 4)//logging hits for everyhitgroup//not anymore
            {
                case 1:
                    angle = entity->GetLowerBodyYawTarget() - 45;
                    break;
                case 2:
                    angle = entity->GetLowerBodyYawTarget() + 45;
                    break;
                case 3:
                    angle = entity->GetLowerBodyYawTarget() + 90;
                    break;
                case 4:
                    angle = entity->GetLowerBodyYawTarget() - 90;
                    break;
                    //continue;
            }
        }
        else//NOT MOVING
        {
            if (HasFakeHead)//lby and eye angles arent synced eZ resolve
            {
                angle = angle - entity->GetLowerBodyYawTarget();
            }
            else {
                if (Lbywithin35) //if lby and eye angles subtracted < 35 then we assume that theyre using an lby breaker
                {
                    switch (shotmissed % 5)
                    {
                            
                        case 0:
                            angle = entity->GetLowerBodyYawTarget() - 180;
                            break;
                        case 1:
                            angle = entity->GetLowerBodyYawTarget() - 180;
                            break;
                        case 2:
                            angle = entity->GetLowerBodyYawTarget() - 45;
                            break;
                        case 3:
                            angle = entity->GetLowerBodyYawTarget() + 45;
                            break;
                        case 4:
                            angle = entity->GetLowerBodyYawTarget() + 90;
                            break;
                        case 5:
                            angle = entity->GetLowerBodyYawTarget() - 90;
                            break;
                    }
                    
                    static float StoredYaw = 0;
                    static bool bLowerBodyIsUpdated = false;
                    if (entity->GetLowerBodyYawTarget() != StoredYaw) bLowerBodyIsUpdated = true;
                    else bLowerBodyIsUpdated = false;
                    if (bLowerBodyIsUpdated) StoredYaw = entity->GetLowerBodyYawTarget();
                    if (entity->GetFlags() & FL_ONGROUND && entity->GetVelocity().Length2D() != 0) angle = entity->GetLowerBodyYawTarget();
                    else
                    {
                        
                        {       // Yaw Resolver
                            // int num = Globals::Shots % 4 is a meme
                            int num = shotmissed % 4;
                            switch (num)
                            {
                                case 0:angle = angle + 180;
                                    break;
                                case 1:angle = angle - 90;
                                    break;
                                case 2:angle = angle + 90;
                                    break;
                                case 3:angle = angle + 179.95;
                                    break;
                                case 4:angle = angle - 179.95;
                                    break;
                                case 5:angle = angle + 40;
                                    break;
                                case 6:angle = angle - 40;
                                    break;
                                case 7:angle = angle + 30;
                                    break;
                                case 8:angle = angle - 30;
                                    break;
                                case 9:angle = angle + 15;
                                    break;
                                case 10:angle = angle - 15;
                                    break;
                            }
                        }
                    }
                }
                
            }
            
            if (OnGround) {
                if (maybeFakeWalking)
                {
                    
                    vector<int> hitboxes;
                    
                    //Baim
                    hitboxes.push_back(HITBOX_LOWER_CHEST);
                    hitboxes.push_back(HITBOX_BELLY);
                    hitboxes.push_back(HITBOX_PELVIS);
                    hitboxes.push_back(HITBOX_UPPER_CHEST);
                    // Feet
                    hitboxes.push_back(HITBOX_RIGHT_FOOT);
                    hitboxes.push_back(HITBOX_LEFT_FOOT);
                    hitboxes.push_back(HITBOX_RIGHT_CALF);
                    hitboxes.push_back(HITBOX_LEFT_CALF);
                    
                }
                angle = entity->GetLowerBodyYawTarget();
            }
            else
            {
                static bool isMoving;
                float PlayerIsMoving = abs(entity->GetVelocity().Length());
                if (PlayerIsMoving > 0.1) isMoving = true;
                else if (PlayerIsMoving <= 0.1) isMoving = false;
                
                static float oldlby = 0.0f;
                static bool bLowerBodyIsUpdated;
                float delta = angle - entity->GetLowerBodyYawTarget();
                if (entity->GetLowerBodyYawTarget() != oldlby) bLowerBodyIsUpdated = true;
                else bLowerBodyIsUpdated = false;
                
                if (bLowerBodyIsUpdated || isMoving || fabsf(delta) >= 35.0f)
                {
                    angle = entity->GetLowerBodyYawTarget();
                    entity->oldlby = entity->GetLowerBodyYawTarget();
                }
                
                else
                {
                    if (fabsf(delta) < 35.f && fabsf(delta) > 0.f)
                        angle = entity->GetLowerBodyYawTarget() + delta;
                }
                return angle;
            }
            
            static bool bLowerBodyIsUpdated;
            {
                
                if (shotmissed > 3 && shotmissed < 21)
                {
                    if (!bLowerBodyIsUpdated)
                    {
                        angle = entity->GetLowerBodyYawTarget();
                    }
                    else if (!bLowerBodyIsUpdated)
                    {
                        switch (shots % 4)
                        {
                            case 1: angle = - 30 + rand() % 45 - rand() % 51;
                                break;
                            case 2: angle = entity->GetLowerBodyYawTarget() + 20 - rand() % 35;
                                break;
                            case 3: angle = entity->GetLowerBodyYawTarget() + 45 % 30 - rand() % 90;
                                break;
                            case 4: angle = entity->GetLowerBodyYawTarget() - 90 - rand() % 90 - rand() % 40;
                                break;
                            case 5: angle = 160 - rand() % 90 - rand() % 40;
                                break;
                        }
                    }
                    else
                        angle = rand() % 180 - rand() % 45;
                }
                
                else if (shotmissed >= 2 && shotmissed <= 3)
                    
                {
                    if (bLowerBodyIsUpdated)
                    {
                        angle = entity->GetLowerBodyYawTarget();
                    }
                    else
                        angle = entity->GetLowerBodyYawTarget();
                }
                else
                {
                    if (bLowerBodyIsUpdated)
                    {
                        bool timer = false;
                        if (timer)
                            angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
                        timer = !timer;
                        /*else
                         angle = entity->GetLowerBodyYawTarget(); - rand() % 100;*/
                    }
                    else
                    {
                        bool timer = false;
                        if (timer)
                            angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
                        timer = !timer;
                        /*else
                         angle = entity->GetLowerBodyYawTarget(); - rand() % 20;*/
                    }
                }
            }
        }
    }
    
    if(vars.aimbot.yresolve == 2){
        angle = entity->GetLowerBodyYawTarget();
    }
    
    if(vars.aimbot.yresolve == 3){
        {
            {
                //p100
                float movinglby[64];
                float lbytomovinglbydelta[64];
                
                { // Standing
                    static float old_simtime[65];// Using fake angles?
                    if (entity->GetSimulationTime() != old_simtime[entity->GetIndex()])
                    {
                        angle = entity->GetSimulationTime() - old_simtime[entity->GetIndex()] == pGlobals->interval_per_tick; //entity->GetSimTime() - old_simtime[entity->GetIndex()] >= TICKS_TO_TIME(2)
                        old_simtime[entity->GetIndex()] = entity->GetSimulationTime();
                    }
                    
                    static float oldlby = 0.0f;
                    static bool bLowerBodyIsUpdated;
                    float delta = angle - entity->GetLowerBodyYawTarget();
                    if (entity->GetLowerBodyYawTarget() != oldlby) bLowerBodyIsUpdated = true;
                    else bLowerBodyIsUpdated = false;
                    
                    if (bLowerBodyIsUpdated || fabsf(delta) >= 35.0f)
                    {
                        angle = entity->GetLowerBodyYawTarget();
                        entity->oldlby = entity->GetLowerBodyYawTarget();
                    }
                    
                    else
                    {
                        if (fabsf(delta) < 35.f && fabsf(delta) > 0.f)
                            angle = entity->GetLowerBodyYawTarget() + delta;
                    }
                    return angle;
                }
                {
                    static bool bLowerBodyIsUpdated;
                    if (shotmissed > 3 && shotmissed < 21)
                    {
                        if (!bLowerBodyIsUpdated)
                        {
                            angle = entity->GetLowerBodyYawTarget();
                        }
                        else if (!bLowerBodyIsUpdated)
                        {
                            switch (shots % 4)
                            {
                                case 1: angle = - 30 + rand() % 45 - rand() % 51;
                                    break;
                                case 2: angle = entity->GetLowerBodyYawTarget() + 20 - rand() % 35;
                                    break;
                                case 3: angle = entity->GetLowerBodyYawTarget() + 45 % 30 - rand() % 90;
                                    break;
                                case 4: angle = entity->GetLowerBodyYawTarget() - 90 - rand() % 90 - rand() % 40;
                                    break;
                                case 5: angle = 160 - rand() % 90 - rand() % 40;
                                    break;
                            }
                        }
                        else
                            angle = rand() % 180 - rand() % 45;
                    }
                    
                    else if (shotmissed >= 2 && shotmissed <= 3)
                        
                    {
                        if (bLowerBodyIsUpdated)
                        {
                            angle = entity->GetLowerBodyYawTarget();
                        }
                        else
                            angle = entity->GetLowerBodyYawTarget();
                    }
                    else
                    {
                        if (bLowerBodyIsUpdated)
                        {
                            bool timer = false;
                            if (timer){
                                angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
                            }else{
                                angle = entity->GetLowerBodyYawTarget(); - rand() % 100;
                            }
                        }
                        else
                        {
                            bool timer = false;
                            if (timer){
                                angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
                            }else
                                angle = entity->GetLowerBodyYawTarget(); - rand() % 20;
                        }
                    }
                    
                    lbytomovinglbydelta[entity->GetIndex()] = entity->GetLowerBodyYawTarget() - lbytomovinglbydelta[entity->GetIndex()];
                    
                    if (entity->GetVelocity().Length2D() > 6 && entity->GetVelocity().Length2D() < 42)
                    {
                        angle = entity->GetLowerBodyYawTarget() + 120;
                    }
                    if (HasFakeHead)//lby and eye angles arent synced eZ resolve
                    {
                        angle = angle - entity->GetLowerBodyYawTarget();
                    }
                    if (LBYbreak) // where all the mother fuckers will get dicked on :)
                    {
                        switch (shotmissed % 5){
                            case 0:
                                angle = entity->GetLowerBodyYawTarget() + 180;
                                break;
                            case 1:
                                angle = entity->GetLowerBodyYawTarget() - 180;
                                break;
                            case 2:
                                angle = entity->GetLowerBodyYawTarget() - 45;
                                break;
                            case 3:
                                angle = entity->GetLowerBodyYawTarget() + 45;
                                break;
                            case 4:
                                angle = entity->GetLowerBodyYawTarget() + 90;
                                break;
                            case 5:
                                angle = entity->GetLowerBodyYawTarget() - 90;
                                break;
                        }
                    }
                    if (Lbywithin35) //if lby and eye angles subtracted < 35 then we assume that theyre using an lby breaker
                    {
                        switch (shotmissed % 5)
                        {
                                
                            case 0:
                                angle = entity->GetLowerBodyYawTarget() + 180;
                                break;
                            case 1:
                                angle = entity->GetLowerBodyYawTarget() - 180;
                                break;
                            case 2:
                                angle = entity->GetLowerBodyYawTarget() - 45;
                                break;
                            case 3:
                                angle = entity->GetLowerBodyYawTarget() + 45;
                                break;
                            case 4:
                                angle = entity->GetLowerBodyYawTarget() + 90;
                                break;
                            case 5:
                                angle = entity->GetLowerBodyYawTarget() - 90;
                                break;
                        }
                    }
                    else if (entity->GetVelocity().Length2D() < 6 || entity->GetVelocity().Length2D() > 42) // they are moving
                    {
                        angle = entity->GetLowerBodyYawTarget();
                        movinglby[entity->GetIndex()] = entity->GetLowerBodyYawTarget();
                    }
                    if (maybeFakeWalking)
                    {
                        vector<int> hitboxes;
                        
                        hitboxes.push_back(HITBOX_LOWER_CHEST);
                        hitboxes.push_back(HITBOX_BELLY);
                        hitboxes.push_back(HITBOX_PELVIS);
                        hitboxes.push_back(HITBOX_UPPER_CHEST);
                    }
                    
                    else if (lbytomovinglbydelta[entity->GetIndex()] > 50 && lbytomovinglbydelta[entity->GetIndex()] < -50 &&
                             lbytomovinglbydelta[entity->GetIndex()] < 112 && lbytomovinglbydelta[entity->GetIndex()] < -112) // the 50 will allow you to have a 30 degree margin of error (do the math :))
                    {
                        angle = movinglby[entity->GetIndex()];
                    }
                    else angle = entity->GetLowerBodyYawTarget();
                }
            }
        }
    }
    
    if(vars.aimbot.yresolve == 4){
        
        static float oldlby = 0.0f;
        static bool bLowerBodyIsUpdated;
        float delta = angle - entity->GetLowerBodyYawTarget();
        if (entity->GetLowerBodyYawTarget() != oldlby) bLowerBodyIsUpdated = true;
        else bLowerBodyIsUpdated = false;
        
        if (bLowerBodyIsUpdated || fabsf(delta) >= 35.0f)
        {
            angle = entity->GetLowerBodyYawTarget();
            entity->oldlby = entity->GetLowerBodyYawTarget();
        }
        
        else
        {
            if (fabsf(delta) < 35.f && fabsf(delta) > 0.f)
                angle = entity->GetLowerBodyYawTarget() + delta;
        }
        return angle;
    }
    {
        static bool bLowerBodyIsUpdated;
        if (shotmissed > 3 && shotmissed < 21)
        {
            if (!bLowerBodyIsUpdated)
            {
                angle = entity->GetLowerBodyYawTarget();
            }
            else if (!bLowerBodyIsUpdated)
            {
                switch (shots % 4)
                {
                    case 1: angle = - 30 + rand() % 45 - rand() % 51;
                        break;
                    case 2: angle = entity->GetLowerBodyYawTarget() + 20 - rand() % 35;
                        break;
                    case 3: angle = entity->GetLowerBodyYawTarget() + 45 % 30 - rand() % 90;
                        break;
                    case 4: angle = entity->GetLowerBodyYawTarget() - 90 - rand() % 90 - rand() % 40;
                        break;
                    case 5: angle = 160 - rand() % 90 - rand() % 40;
                        break;
                }
            }
            else
                angle = rand() % 180 - rand() % 45;
        }
        
        else if (shotmissed >= 2 && shotmissed <= 3)
            
        {
            if (bLowerBodyIsUpdated)
            {
                angle = entity->GetLowerBodyYawTarget();
            }
            else
                angle = entity->GetLowerBodyYawTarget();
        }
        else
        {
            if (bLowerBodyIsUpdated)
            {
                bool timer = false;
                if (timer){
                    angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
                }else{
                    angle = entity->GetLowerBodyYawTarget(); - rand() % 100;
                }
            }
            else
            {
                bool timer = false;
                if (timer){
                    angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
                }else
                    angle = entity->GetLowerBodyYawTarget(); - rand() % 20;
            }
        }
        if (maybeFakeWalking)
        {
            vector<int> hitboxes;
            
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            
            angle = entity->GetLowerBodyYawTarget();
        }
        
        
        // Breaking LBY
        static float current_layer_activity = entity->GetAnimTime();
        static float previous_layer_activity = 0;
        
        if (current_layer_activity == 979){ // the current layer must be triggering 979
            {
                if (previous_layer_activity == 979) // the previous layer must be trigerring 979
                {
                    switch (shots % 3){
                        case 1: angle = entity->GetLowerBodyYawTarget() + 110;
                            break;
                        case 2: angle = entity->GetLowerBodyYawTarget() + 180;
                            break;
                        case 3: angle = entity->GetLowerBodyYawTarget() - 110;
                            break;
                    }
                    // we can tell now that he is surely breaking lby in some sort
                    angle = entity->GetLowerBodyYawTarget() - 180.f; // for the resolver it's enough here to just flip him, because we will backtrack him | unless u dont have backtrack
                }
            }
        }
    }
    if(vars.aimbot.yresolve == 5)
    {
        float last_moving_lby [ 65 ];
        
        bool Movingg;
        entity->GetVelocity( ).Length2D( ) > 1.f && ( entity->GetFlags() & FL_ONGROUND);
        
        bool Fakewalkk;
        Movingg && entity->GetVelocity().Length2D() < 45.f && !( entity->GetFlags( ) & FL_DUCKING );
        
        if ( Movingg ) {
            if ( Fakewalkk ) {
                angle = entity->GetLowerBodyYawTarget( ) - 180.f;
            }
            else
            {
                angle = entity->GetLowerBodyYawTarget( );
                last_moving_lby [ entity->GetIndex() ] = entity->GetLowerBodyYawTarget( );
            }
            if (HasFakeHead)
            {
                angle = angle - entity->GetLowerBodyYawTarget();
            }
        }
        else
        {
#define RandomFloat(min, max) (rand() % (max - min + 1) + min)
            angle += RandomFloat(35, 35);
            //angle = last_moving_lby[ entity->GetIndex() ] + rand( ) % ( 25 - -25 + 1 ) + -25;
        }
        
    } // end of resolver 5
    
    if(vars.aimbot.yresolve == 6){
        angle += RandomFloat(35, 35);
    }
    
    
} // End of resolver



    //Styles Resolver - SHIT RESOLVER
    /*
    bool bLowerBodyUpdated;
    bool IsUsingFakeAngles;
    float Differences[65];
    
    bool HasFakeHead;
        //lby should update if distance from lby to eye angles exceeds 35 degrees
    abs(angle - entity->GetLowerBodyYawTarget()) > 35;
    
    bool Lbywithin35;
    //lby should update if distance from lby to eye angles less than 35 degrees
    abs(angle - entity->GetLowerBodyYawTarget()) < 35;
    
    bool IsMovingOnGround;
    //Check if player has a velocity greater than 0 (moving) and if they are onground.
    entity->GetVelocity().Length2D() > 45.f && entity->GetFlags() & FL_ONGROUND;
    
    bool IsMovingOnInAir;
    //Check if player has a velocity greater than 0 (moving) and if they are onground.
    !(entity->GetFlags() & FL_ONGROUND);
    
    bool OnGround;
    //Check if player has a velocity greater than 0 (moving) and if they are onground.
    if (entity->GetFlags() & FL_ONGROUND)
    OnGround = true;
    else
    OnGround = false;
    
    int GetEstimatedServerTickCount(float latency);
    (float)((uintptr_t)& pGlobals->interval_per_tick + 0.5) + 1 + (int)((uintptr_t)&pGlobals->tickcount);
   
    bool missedshots = 0;
    bool shots = 1;
    
    float flLowerBodyYaw = entity->GetLowerBodyYawTarget();
    int difference = angle - flLowerBodyYaw;
    
    int temp = difference;
    while (temp < 0)
        temp += 360;
    while (temp > 360)
        temp -= 360;
    auto getdst = [](int a, int b) {
        int x = abs(b - a) % 360;
        return x > 180 ? 360 - x : x;
    };
    
    float prevlby = 0.f;
    int avg = 1;
    int count = 1;
    static float LatestLowerBodyYawUpdateTime[55];
    static float LatestLowerBodyYawUpdateTime1[55];

    static float time_at_update[65];
    float kevin[64];
    static bool bLowerBodyIsUpdated=false;
    
    if (entity->GetLowerBodyYawTarget() != kevin[entity->GetIndex()])
        bLowerBodyIsUpdated = true;
    else
        bLowerBodyIsUpdated = false;
    
    if (entity->GetVelocity().Length2D() > 0.1)
    {
        kevin[entity->GetIndex()] = entity->GetLowerBodyYawTarget();//storing their moving lby for later
        //LatestLowerBodyYawUpdateTime[entity->GetIndex()] = entity->GetSimulationTime() +0.22;
        
    }
    
      if(LatestLowerBodyYawUpdateTime[entity->GetIndex()] < entity->GetSimulationTime())
      {
      angle = entity->GetLowerBodyYawTarget();
      LatestLowerBodyYawUpdateTime[entity->GetIndex()] = local->GetServerSimulationFrameTime() + 1.1;
      }
    
    if (flLowerBodyYaw == prevlby)
    prevlby = flLowerBodyYaw;
    
    avg += getdst(static_cast<int>(angle), static_cast<int>(flLowerBodyYaw));
    
    count++;

  if (GetAsyncKeyState(Menu::Window.RageBotTab.KeyBindAA.GetKey()) && Menu::Window.RageBotTab.KeyBindAA.GetKey() > 0)
  {
  
  auto local_player = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
  if (!local_player)
  return;
  
  Vector viewangles;
  pEngine->GetViewAngles(viewangles);
  auto delta = NormalizeYaw(viewangles.y - angle)
  
  if (delta > 0)
  angle + 180;
  else
  angle - 180;
  }
if (LatestLowerBodyYawUpdateTime[pEntity->GetIndex()] < pEntity->GetSimulationTime() || bLowerBodyIsUpdated)
{
    angle = entity->GetLowerBodyYawTarget();
    LatestLowerBodyYawUpdateTime[entity->GetIndex()] = pEntity->GetSimulationTime() + 1.1;
}
 

    if (IsMovingOnInAir)
        
    {
        switch (shots % 4)//logging hits for everyhitgroup//not anymore
        {
            case 1:
                angle = entity->GetLowerBodyYawTarget() - 45;
                break;
            case 2:
                angle = entity->GetLowerBodyYawTarget() + 45;
                break;
            case 3:
                angle = entity->GetLowerBodyYawTarget() + 90;
                break;
            case 4:
                angle = entity->GetLowerBodyYawTarget() - 90;
                break;
                //continue;
        }
    }
    else//NOT MOVING
    {
        if (HasFakeHead)//lby and eye angles arent synced eZ resolve
        {
            angle = angle - entity->GetLowerBodyYawTarget();
        }
        else {
            if (Lbywithin35) //if lby and eye angles subtracted < 35 then we assume that theyre using an lby breaker
            {
                switch (missedshots % 5)
                {
                    case 0:
                        angle = entity->GetLowerBodyYawTarget() - 180;
                        break;
                    case 1:
                        angle = entity->GetLowerBodyYawTarget() - 180;
                        break;
                    case 2:
                        angle = entity->GetLowerBodyYawTarget() - 45;
                        break;
                    case 3:
                        angle = entity->GetLowerBodyYawTarget() + 45;
                        break;
                    case 4:
                        angle = entity->GetLowerBodyYawTarget() + 90;
                        break;
                    case 5:
                        angle = entity->GetLowerBodyYawTarget() - 90;
                        break;
                }
     
                 if (Backtracking->arr_infos.at(pEntity->GetIndex()).TickRecords.size() < 3)
                 return;
                 for (auto& r : record.TickRecords) {
                 if (r.m_flLowerBodyYawTarget == prevlby)
                 continue;
                 
                 prevlby = r.m_flLowerBodyYawTarget;
                 
                 float diff = r.m_flLowerBodyYawTarget - prevlby;
                 
                 avg += static_cast<int>(diff);
                 count++;
                 }
                 avg /= count;
                 angle += avg;
            }
      
        }
    }
    //}
    float yClamped = angle;
    while (yClamped < -180.0f)
        yClamped += 360.0f;
        
        while (yClamped > 180.0f)
            yClamped -= 360.0f;
    angle = yClamped;
    }
}
*/

    
     // Brute Force Resolver
    /*
        bool MeetsLBYReq;
        if (entityf->GetFlags() & FL_ONGROUND)
            MeetsLBYReq = true;
        else
            MeetsLBYReq = false;
        
        bool IsMoving;
        if (entity->GetVelocity().Length2D() >= 0.5)
            IsMoving = true;
        else
            IsMoving = false;
    
    static bool bLowerBodyIsUpdated;
    
    bool missedshots = 0;
    bool shots = 1;
    {
        if (missedshots > 3 && missedshots < 21)
        {
            if (MeetsLBYReq && bLowerBodyIsUpdated)
            {
                angle = entity->GetLowerBodyYawTarget();
            }
            else if (!MeetsLBYReq && bLowerBodyIsUpdated)
            {
                switch (shots % 4)
                {
                    case 1: angle = - 30 + rand() % 45 - rand() % 51;
                        break;
                    case 2:
                        angle = entity->GetLowerBodyYawTarget() + 20 - rand() % 35;
                        break;
                    case 3:
                        angle = entity->GetLowerBodyYawTarget() + 45 % 30 - rand() % 90;
                        break;
                    case 4:
                        angle = entity->GetLowerBodyYawTarget() - 90 - rand() % 90 - rand() % 40;
                        break;
                    case 5:
                        angle = 160 - rand() % 90 - rand() % 40;
                        break;
                }
            }
            else
                angle = rand() % 180 - rand() % 45;
        }
        
        else if (missedshots >= 2 && missedshots <= 3)
        {
            if (MeetsLBYReq && bLowerBodyIsUpdated)
            {
                angle = entity->GetLowerBodyYawTarget();
            }
            else
                angle = entity->GetLowerBodyYawTarget();
        }
        else
        {
            if (MeetsLBYReq && bLowerBodyIsUpdated)
            {
                bool timer;
                if (timer)
                    angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
            *else
                    angle = entity->GetLowerBodyYawTarget(); - rand() % 100;
                timer = !timer;
            }
            else
            {
                bool timer;
                if (timer)
                    angle = entity->GetLowerBodyYawTarget(); + rand() % 20;
            else
                    angle = entity->GetLowerBodyYawTarget(); - rand() % 20;
                timer = !timer;
            }
        }
    }
}
*/

    /*
     //Brute Force Resolver 2
    {
    static bool isMoving;
    float PlayerIsMoving = abs(entity->GetVelocity().Length());
    if (PlayerIsMoving > 0.9) isMoving = true;
    else if (PlayerIsMoving <= 0.9) isMoving = false;
    
    bool MeetsLBYReq;
    if (entity->GetFlags() & FL_ONGROUND)
        MeetsLBYReq = true;
    else
        MeetsLBYReq = false;
    
    static bool bLowerBodyIsUpdated;
    
        angle = 179.f;
        if (isMoving)
        {
            angle = entity->GetLowerBodyYawTarget() - 25.f + rand() % 15 - rand() % 19;
            
        }
        else if (!MeetsLBYReq && !bLowerBodyIsUpdated)
        {
            angle = 175.f + rand() % 40 - rand() % 41;
        }
        else if (!MeetsLBYReq && !bLowerBodyIsUpdated)
        {
            angle = entity->GetLowerBodyYawTarget() - 125.f - rand() % 40 + rand() % 39;
        }
}
     */
    
    
    
    // LBY Flip force Resolver
    //angle = entity->GetLowerBodyYawTarget() + 180;

    
    
    
     // LBY Resolver
    /*
     static bool isMoving;
    float PlayerIsMoving = abs(entity->GetVelocity().Length());
    if (PlayerIsMoving > 0.1) isMoving = true;
    else if (PlayerIsMoving <= 0.1) isMoving = false;
    
    static float oldlby = 0.0f;
    static bool bLowerBodyIsUpdated;
    float delta = angle - entity->GetLowerBodyYawTarget();
    if (entity->GetLowerBodyYawTarget() != oldlby) bLowerBodyIsUpdated = true;
    else bLowerBodyIsUpdated = false;
    
    if (bLowerBodyIsUpdated || isMoving || fabsf(delta) >= 35.0f)
    {
        angle = entity->GetLowerBodyYawTarget();
        entity->oldlby = entity->GetLowerBodyYawTarget();
    }
    
    else
    {
        if (fabsf(delta) < 35.f && fabsf(delta) > 0.f)
           angle = entity->GetLowerBodyYawTarget() + delta;
    }
    return angle;
}
*/

    
 // LBY Resolver 2
    /*
     float delta = angle - entity->GetLowerBodyYawTarget();
 

     if (entity->GetLowerBodyYawTarget() != entity->oldlby || fabsf(delta) >= 33.f || (entity->GetVelocity().Length2D() > 0.1f && entity->GetFlags() & FL_ONGROUND))

     {

         angle = entity->GetLowerBodyYawTarget();
         entity->oldlby = entity->GetLowerBodyYawTarget();

     }
     else
     {
         if (fabsf(delta) < 33.f && fabsf(delta) > 0.f)
         {
             angle = entity->GetLowerBodyYawTarget() + delta;

         }
     }
     return angle;
}
     */

// Lower Body Resolver 3
    /*
    static bool isMoving;
    float PlayerIsMoving = abs(entity->GetVelocity().Length());
    if (PlayerIsMoving > 0.1) isMoving = true;
    else if (PlayerIsMoving <= 0.1) isMoving = false;
    
    static float lowerDelta[64];
    static float lastYaw[64];
    float delta = angle - entity->GetLowerBodyYawTarget();
    static float oldlby = 0.0f;
    
    float curLower = entity->GetLowerBodyYawTarget();
    float curYaw = angle;
    
    delta = curYaw - curLower;
    
    if (fabs(delta) > 15.f)
    {
        if (isMoving)
        {
            angle = entity->GetLowerBodyYawTarget();
            entity->oldlby = entity->GetLowerBodyYawTarget();
        }
        else {
            if (curYaw != oldlby)
            {
                angle += delta;
                oldlby = curYaw;
            }
        }
    }
}
*/
     
     // Mutiny Resolver
    /*
    bool new_yaw = entity->GetLowerBodyYawTarget() + rand() % -45; 45;
    bool LatestLowerBodyYawUpdateTime = pGlobals->curtime;
    bool isMoving = entity->GetVelocity().Length() > 29.f;
    bool onGround = (entity->GetFlags() & FL_ONGROUND);
    
    if (entity->GetLowerBodyYawTarget() != LatestLowerBodyYawUpdateTime || (isMoving && onGround))
        
    LatestLowerBodyYawUpdateTime = entity->GetLowerBodyYawTarget();
    
    else // On Ground resolver
    {
        if (pGlobals->curtime - LatestLowerBodyYawUpdateTime >= 0.5)
        {
            new_yaw -= 180;
        }
        else
        {
            auto cur = this->m_arrInfos.at(index).m_sRecords;
        
        if (cur.size() > 1)
        {
            if (HasStaticRealAngle(cur, 5))
                new_yaw = (cur.front().m_flLowerBodyYawTarget) + (Math::RandomFloat(0.f, 1.f) > 0.5f ? 10 : -10);
            else if (HasStaticYawDifference(cur, 10))
                new_yaw -=  (cur.front().m_angEyeAngles.y - cur.front().m_flLowerBodyYawTarget);
            else if (HasSteadyDifference(cur, 10, pPlayer)) {
                float tickdif = static_cast<float>(cur.front().tickcount - cur.at(1).tickcount);
                float lbydif = GetDelta(cur.front().m_flLowerBodyYawTarget, cur.at(1).m_flLowerBodyYawTarget);
                float ntickdif = static_cast<float>(TIME_TO_TICKS(g_pGlobals->curtime) - cur.front().tickcount);
                new_yaw = (lbydif / tickdif) * ntickdif;
        }
    }
}
*/
 
// Pitch Corrections
/*
 void FixPitch(const CRecvProxyData *pData, void *pStruct, void *pOut) { // Auto Detection for FakeDown Down and Up.
    
    float angle = pData->m_Value.m_Float;
    
    int index = ((C_BaseEntity*)pStruct)->GetIndex();
    
    gCorrections[index].x = angle;
    
    OldProxy_X(pData, pStruct, pOut);
}
*/


void FixYaw(const CRecvProxyData *pData, void *pStruct, void *pOut) {
    float flYaw = pData->m_Value.m_Float;
    
    int index = ((C_BaseEntity*)pStruct)->GetIndex();
    
    gCorrections[index].y = flYaw;
    
    OldProxy_Y(pData, pStruct, pOut);
}
