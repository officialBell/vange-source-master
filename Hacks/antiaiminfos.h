#include "../Interfaces/hooks.h"
#include "../Hacks/esp.h"
#include "../main.h"
#include "../Hacks/antiaim.h"

/*
namespace AntiAimInfos
{

	// Hooks
	void PaintTraverse();
	void CreateMove(CUserCmd* cmd);
};
*/
void AntiAimInfo(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bPacket);
