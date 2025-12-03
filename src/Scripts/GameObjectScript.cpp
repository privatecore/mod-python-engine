#include "PythonEngine.h"
#include "HookMacros.h"
#include "ScriptMgr.h"
#include "GameObject.h"
#include "Player.h"

class PythonGameObjectScript : public GameObjectScript
{
public:
    PythonGameObjectScript() : GameObjectScript("PythonGameObjectScript") {}

    // Disable database binding requirement and suppress errors like:
    // Script named '<PythonEntityScript>' is not assigned in the database.
    // @todo should use AllGameObjectScript instead?
    bool IsDatabaseBound() const override { return false; }

    bool OnGossipHello(Player* player, GameObject* go) override
    {
        TRIGGER_GAMEOBJECT_HOOK(ON_GOSSIP_HELLO, go->GetEntry(), player, go);
        return false;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action) override
    {
        TRIGGER_GAMEOBJECT_HOOK(ON_GOSSIP_SELECT, go->GetEntry(), player, go, sender, action);
        return false;
    }

    void OnDamaged(GameObject* go, Player* player) override
    {
        TRIGGER_GAMEOBJECT_HOOK(ON_ADD_WORLD, go->GetEntry(), go, player);
    }

    void OnDestroyed(GameObject* go, Player* player) override
    {
        TRIGGER_GAMEOBJECT_HOOK(ON_REMOVE_WORLD, go->GetEntry(), go, player);
    }
};

void AddPythonGameObjectScripts()
{
    new PythonGameObjectScript();
}
