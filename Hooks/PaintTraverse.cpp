#include "../main.h"
#include "../Drawings/menu.h"
#include "../Hacks/crosshair.h"
#include "../Hacks/esp.h"
#include "../Hacks/spectators.h"
#include "../Hacks/antiaiminfos.h"
#include "../Hacks/hitmarker.h"

void hkPaintTraverse(void* thisptr, VPANEL panel, bool forceRepaint, bool allowForce)
{
    
    if (vars.misc.noscope && !strcmp("HudZoom", pPanel->GetName(panel)))
        return;
    
    paintVMT->GetOriginalMethod<tPaintTraverse>(42)(thisptr, panel, forceRepaint, allowForce);
    
    C_BaseEntity* local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    static VPANEL last = 0;
    
    if(!last)
    {
        if(strstr(pPanel->GetName(panel), "FocusOverlayPanel"))
        {
            framefont       = draw->createfont(framefont, "BigNoodleTitling", 14, FONTFLAG_ANTIALIAS);
            espfont         = draw->createfont(espfont, "Arial Bold", 12, FONTFLAG_DROPSHADOW);
            
            mFont           = draw->createfont(mFont, "BigNoodleTitling", 1, FONTFLAG_ANTIALIAS);
            sFont           = draw->createfont(sFont, "BigNoodleTitling", 12, FONTFLAG_ANTIALIAS);     // Used for sliders
            tFont           = draw->createfont(tFont, "BigNoodleTitling", 18, FONTFLAG_ANTIALIAS);     // Used for tabs
            heading         = draw->createfont(heading, "BigNoodleTitling", 21, FONTFLAG_ANTIALIAS);   // Used for headings
            osFont          = draw->createfont(osFont, "osmiummenufont", 30, FONTFLAG_ANTIALIAS);
            cFont           = draw->createfont(cFont, "BigNoodleTitling", 14, FONTFLAG_ANTIALIAS);     // Combos
            titleFont       = draw->createfont(cFont, "BigNoodleTitling", 52, FONTFLAG_ANTIALIAS);     // vlone.cc Title
            subtitleFont    = draw->createfont(cFont, "Verdana", 30, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);     // vlone.cc Subtitle
            o4Font_03       = draw->createfont(o4Font_03, "04b03", 12, FONTFLAG_ANTIALIAS);
            o4Font_11       = draw->createfont(o4Font_11, "04b11", 12, FONTFLAG_ANTIALIAS);
            o4Font_20       = draw->createfont(o4Font_20, "04b_20", 12, FONTFLAG_ANTIALIAS);
            
            last = panel;
        }
        
        {   // Initialisation
            vars.colors.ctchams     = Color(60, 53, 178, 255);
            vars.colors.ctchams_ign = Color(229, 22, 90, 255);
            
            vars.colors.tchams      = Color(60, 53, 178, 255);
            vars.colors.tchams_ign  = Color(229, 22, 90, 255);
            
            vars.colors.tbox        = Color(60, 53, 178, 255);
            vars.colors.tbox_ign    = Color(229, 22, 90, 255);
            
            vars.colors.ctbox       = Color(60, 53, 178, 255);
            vars.colors.ctbox_ign   = Color(229, 22, 90, 255);
            
            vars.colors.hands       = Color(255, 0, 83, 255);
            vars.colors.weapon      = Color(0, 0, 255, 255);
            
            vars.colors.scope       = Color::Red();
            vars.colors.world       = Color::Black();
            vars.colors.sky         = Color::Red();
        }
        
    }
    
    
    if(panel == last)
    {
        
        if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
            return;
        
        pwnmymenu();
        
        {   // Drawing features / own scope just for readablity
            
            DrawOtherESP();     // Other ESP
            
            DrawPlayerESP();    // Player esp
                        
            DrawScope(local);   // Draws the crosshar for noscope
            
            rCrosshair(local);  // Draws recoil crosshair
            
            manualaa();        // Manual AA idicator
            
            Spectatorlist();    // Draws speclist
            
            //aw_hitmarker->initilisze();
        }
        
        if(vars.menu)
        {   // Draw menu items
            menu->renderMenu();
            draw->drawmouse();
        }
        
        draw->drawstring(10, 15, Color::White(), espfont, "[Private Vange.me]");
    }
}

