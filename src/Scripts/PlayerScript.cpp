#include "HookMacros.h"
#include "ScriptMgr.h"
#include "Player.h"

class PythonPlayerScript : public PlayerScript
{
public:
    PythonPlayerScript() : PlayerScript("PythonPlayerScript") {}

    /**
     * @brief Called when a player logs in
     *
     * @param player Contains information about the Player
     */
    void OnPlayerLogin(Player* player) override
    {
        TRIGGER_PLAYER_HOOK(ON_LOGIN, player);
    }

    /**
     * @brief Called when a player logs out
     *
     * @param player Contains information about the Player
     */
    void OnPlayerLogout(Player* player) override
    {
        TRIGGER_PLAYER_HOOK(ON_LOGOUT, player);
    }

    /**
     * @brief Called when a player kills another player
     *
     * @param killer Contains information about the killer Player
     * @param killed Contains information about the killed Player
     */
    void OnPlayerPVPKill(Player* killer, Player* killed) override
    {
        TRIGGER_PLAYER_HOOK(ON_PVP_KILL, killer, killed);
    }

    /**
     * @brief Called when a player gains XP (before anything is given)
     *
     * @param player Contains information about the Player
     * @param amount Contains information about the amount of XP gained
     * @param victim Contains information about the victim unit (used with XP source kill)
     * @param xpSource Contains information about the XP source (kill, quest, explore, bg)
     */
    void OnPlayerGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override
    {
        TRIGGER_PLAYER_HOOK(ON_GIVE_EXP, player, amount, victim, xpSource);
    }

    /**
     * @brief Called when a player's level changes (right after the level is applied)
     *
     * @param player Contains information about the Player
     * @param oldLevel Contains information about the previous level value
     */
    void OnPlayerLevelChanged(Player* player, uint8 oldLevel) override
    {
        TRIGGER_PLAYER_HOOK(ON_LEVEL_CHANGED, player, oldLevel);
    }

    /**
     * @brief Called when a player's money is modified (before the modification is done)
     *
     * @param player Contains information about the Player
     * @param amount Contains information about the amount of money changed
     */
    void OnPlayerMoneyChanged(Player* player, int32& amount) override
    {
        TRIGGER_PLAYER_HOOK(ON_MONEY_CHANGED, player, amount);
    }

    /**
     * @brief After looting an item
     *
     * @param player Contains information about the Player
     * @param item Contains information about the Item
     * @param count Contains information about the count looted
     * @param lootguid Contains information about the loot ObjectGuid
     */
    void OnPlayerLootItem(Player* player, Item* item, uint32 count, ObjectGuid lootguid) override
    {
        TRIGGER_PLAYER_HOOK(ON_LOOT_ITEM, player, item, count, lootguid);
    }
};

void AddPythonPlayerScripts()
{
    new PythonPlayerScript();
}
