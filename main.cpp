#include "main.h"

namespace Global
{
    CUserCmd*     cmd;
    C_BasePlayer* local;
    C_BaseCombatWeapon* localWeapon;
}

int __attribute__((constructor)) Init()
{
    InitializeInterfaces();    
    InitializeVMTs();
    InitializeHooks();
    Offsets::getOffsets();
    PrintInfo();
    return 0;
}

void __attribute__((constructor)) DeInit()
{

}
