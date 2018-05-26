#include "main.h"

int hkKeyEvent(void* thisptr, int eventcode, int keynum, const char* currentbinding)
{
    if(eventcode == 0)   // Key pressed
    {
        if(keynum == KEY_INSERT || keynum == KEY_LALT)
        {
            vars.menu = !vars.menu;
            
            if(vars.menu)
                pEngine->ExecuteClientCmd("cl_mouseenable 0");
            else
                pEngine->ExecuteClientCmd("cl_mouseenable 1");

        }
        
    }
    
    if(eventcode == 1)  // Key released
    {
        if(vars.menu && (vars.misc_clantag || vars.misc_name || vars.misc_changename))
        {
            draw->handleinput(keynum, draw->m_szCurrentString);
            return 0;
        }
        
    }
    
    return clientVMT->GetOriginalMethod<tKeyEvent>(20)(thisptr, eventcode, keynum, currentbinding);
}




