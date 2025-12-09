#include "HookMacros.h"
#include "ScriptMgr.h"
#include "GameObject.h"
#include "Player.h"

class PythonGameObjectScript : public GameObjectScript
{
public:
    PythonGameObjectScript() : GameObjectScript("PythonGameObjectScript") {}

    /**
     * @brief Disable database binding requirement and suppress errors like:
     * Script named '<PythonEntityScript>' is not assigned in the database.
     *
     * @todo should use AllGameObjectScript instead?
     */
    bool IsDatabaseBound() const override { return false; }

    /**
     * @brief Called when a player opens a gossip dialog with the GameObject
     *
     * @param player Contains information about the Player
     * @param go Contains information about the GameObject
     * @return False if you want to continue, true if you want to disable
     */
    bool OnGossipHello(Player* player, GameObject* go) override
    {
        TRIGGER_GAMEOBJECT_HOOK(ON_GOSSIP_HELLO, go->GetEntry(), player, go);
        return false;
    }

    /**
     * @brief Called when a player selects a gossip item in the GameObject's gossip menu
     *
     * @param player Contains information about the Player
     * @param go Contains information about the GameObject
     * @param sender Contains information about the sender type
     * @param action Contains information about the action id
     * @return False if you want to continue, true if you want to disable
     */
    bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action) override
    {
        TRIGGER_GAMEOBJECT_HOOK(ON_GOSSIP_SELECT, go->GetEntry(), player, go, sender, action);
        return false;
    }

    /**
     * @brief Called when the GameObject is destroyed (destructible buildings only)
     *
     * @param go Contains information about the GameObject
     * @param player Contains information about the Player
     */
    void OnDestroyed(GameObject* go, Player* player) override
    {
        TRIGGER_GAMEOBJECT_HOOK(ON_REMOVE_WORLD, go->GetEntry(), go, player);
    }

    /**
     * @brief Called when the GameObject is damaged (destructible buildings only)
     *
     * @param go Contains information about the GameObject
     * @param player Contains information about the Player
     */
    void OnDamaged(GameObject* go, Player* player) override
    {
        TRIGGER_GAMEOBJECT_HOOK(ON_ADD_WORLD, go->GetEntry(), go, player);
    }
};

void AddPythonGameObjectScripts()
{
    new PythonGameObjectScript();
}
