// PlayerHooks.cpp
#include "PythonEngine.h"
#include "HookMacros.h"
#include "ScriptMgr.h"
#include "Player.h"

class PythonPlayerScript : public PlayerScript
{
public:
    PythonPlayerScript() : PlayerScript("PythonPlayerScript") {}

    void OnPlayerLogin(Player* player) override
    {
        TRIGGER_PLAYER_HOOK(ON_LOGIN, player);
    }

    void OnPlayerLogout(Player* player) override
    {
        TRIGGER_PLAYER_HOOK(ON_LOGOUT, player);
    }

    void OnPlayerPVPKill(Player* killer, Player* killed) override
    {
        TRIGGER_PLAYER_HOOK(ON_PVP_KILL, killer, killed);
    }

    void OnPlayerGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        TRIGGER_PLAYER_HOOK(ON_GIVE_EXP, player, amount, victim, xpSource);
    }

    void OnPlayerLevelChanged(Player* player, uint8 oldLevel) override
    {
        TRIGGER_PLAYER_HOOK(ON_LEVEL_CHANGED, player, oldLevel);
    }

    void OnPlayerMoneyChanged(Player* player, int32& amount) override
    {
        TRIGGER_PLAYER_HOOK(ON_MONEY_CHANGED, player, amount);
    }
};

void AddPythonPlayerScripts()
{
    new PythonPlayerScript();
}
