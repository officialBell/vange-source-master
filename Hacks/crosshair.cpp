#include "crosshair.h"

// Thanks @pwned
// Draw crosshair functions here

void rCrosshair(C_BaseEntity* local)
{
    if(!vars.visuals.rcrosshair)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    if(!local)
        return;
    
    static int Height, Width;
    pEngine->GetScreenSize(Width, Height);
    
    int x = Width / 2;
    int y = Height / 2;
    
    Vector punchAngles = local->GetPunchAngles();
    
    int dy = Height / 90;
    int dx = Width / 90;
    int X = x - (dx * punchAngles.y);
    int Y = y + (dy * punchAngles.x);
    
    draw->drawCrosshair(X, Y, Color::White());
}

void DrawScope(C_BaseEntity* local)
{
    if(!vars.misc.noscope || !local || (local && !local->IsScoped()))
        return;
    
    auto weapon = GetActiveWeapon(local);
    
    if(!weapon)
        return;
    
    if(*weapon->GetItemDefinitionIndex() == WEAPON_AUG || *weapon->GetItemDefinitionIndex() == WEAPON_SG556)
        return;
    
    int w, h;
    pEngine->GetScreenSize(w, h);
    
    draw->drawline(w / 2, 0, w / 2, h, Color::Black());
    draw->drawline(0, h / 2, w, h / 2, Color::Black());
}

void manualaa()
{
    if ( !vars.visuals.antiaim_indicator )
        return;
    
    static bool left = false;
    static bool right = false;
    
    int Height, Width;
    pEngine->GetScreenSize(Height, Width);
    
    int x = Width / 2;
    int y = Height / 2;
    
    if (pInputSystem->IsButtonDown(KEY_LEFT)) {
        left = true; right = false;
    }
    else if (pInputSystem->IsButtonDown(KEY_RIGHT)) {
        left = false; right = true;
    }

    
    if(vars.visuals.indicatorAA_types == 1){
        
        if( left )
        {
            draw->drawstring(25, 600, Color(255, 255, 255, 255), subtitleFont, ("left"));
        }
        
        if( right )
        {
            draw->drawstring(25, 600, Color(255, 255, 255, 255), subtitleFont, ("right"));
        }
    }
    
    if(vars.visuals.indicatorAA_types == 2){
        
        if( right ) {
            draw->drawstring(y + 40, x, Color(10, 145, 190, 255), subtitleFont, (">")); // Green
            draw->drawstring(y - 60, x, Color(255, 255, 255, 255), subtitleFont, ("<")); // White
        }
        
        if( left ){
            draw->drawstring(y + 40, x, Color(255, 255, 255, 255), subtitleFont, (">")); // White
            draw->drawstring(y - 60, x, Color(10, 145, 190, 255), subtitleFont, ("<")); // Green
        }
    }

    // number order
    // y
    // x
}

/*void DrawDirection(const Vector& origin) //monarch is the NIGGA
{
    constexpr float radius = 360.0f;
    int width, height;
    pEngine->GetScreenSize(width, height);
    
    Vector vRealAngles;
    pEngine->GetViewAngles(vRealAngles);
    
    Vector vForward, vRight, vUp(0.0f, 0.0f, 1.0f);
    
    AngleVectors(vRealAngles, &vForward);
    
    vForward.z = 0.0f;
    NormalizeAngle(vForward);
    CrossProduct(vUp, vForward, vRight);
    
    float flFront = DotProduct(origin, vForward);
    float flSide = DotProduct(origin, vRight);
    float flXPosition = radius * -flSide;
    float flYPosition = radius * -flFront;
    
    float rotation = cmd->viewangles.y + 180;
    
    rotation = atan2(flXPosition, flYPosition) + M_PI;
    rotation *= 180.0f / M_PI;
    
    float flYawRadians = -(rotation)* M_PI / 180.0f;
    float flCosYaw = cos(flYawRadians);
    float flSinYaw = sin(flYawRadians);
    
    flXPosition = (int)((width / 2.0f) + (radius * flSinYaw));
    flYPosition = (int)((height / 2.0f) - (radius * flCosYaw));
    
    draw->drawline(flXPosition, flYPosition, 10, 50, Color(255, 0, 255, 120));
}*/























