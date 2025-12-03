#include "PythonEngine.h"
#include "HookMacros.h"
#include "ScriptMgr.h"
#include "Creature.h"
#include "Player.h"

class PythonCreatureScript : public CreatureScript
{
public:
    PythonCreatureScript() : CreatureScript("PythonCreatureScript") {}

    // Disable database binding requirement and suppress errors like:
    // Script named '<PythonEntityScript>' is not assigned in the database.
    // @todo should use AllCreatureScript instead?
    bool IsDatabaseBound() const override { return false; }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        TRIGGER_CREATURE_HOOK(ON_GOSSIP_HELLO, creature->GetEntry(), player, creature);
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        TRIGGER_CREATURE_HOOK(ON_GOSSIP_SELECT, creature->GetEntry(), player, creature, sender, action);
        return false;
    }

    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code) override
    {
        TRIGGER_CREATURE_HOOK(ON_GOSSIP_SELECT_CODE, creature->GetEntry(), player, creature, sender, action, code);
        return false;
    }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        TRIGGER_CREATURE_HOOK(ON_QUEST_ACCEPT, creature->GetEntry(), player, creature, quest);
        return false;
    }

    bool OnQuestSelect(Player* player, Creature* creature, Quest const* quest) override
    {
        TRIGGER_CREATURE_HOOK(ON_QUEST_SELECT, creature->GetEntry(), player, creature, quest);
        return false;
    }

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest) override
    {
        TRIGGER_CREATURE_HOOK(ON_QUEST_COMPLETE, creature->GetEntry(), player, creature, quest);
        return false;
    }

    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt) override
    {
        TRIGGER_CREATURE_HOOK(ON_QUEST_REWARD, creature->GetEntry(), player, creature, quest, opt);
        return false;
    }
};

class PythonAllCreatureScript : public AllCreatureScript
{
public:
    PythonAllCreatureScript() : AllCreatureScript("PythonAllCreatureScript") {}

    void OnCreatureAddWorld(Creature* creature) override
    {
        TRIGGER_CREATURE_HOOK(ON_ADD_WORLD, creature->GetEntry(), creature);
    }

    void OnCreatureRemoveWorld(Creature* creature) override
    {
        TRIGGER_CREATURE_HOOK(ON_REMOVE_WORLD, creature->GetEntry(), creature);
    }
};

void AddPythonCreatureScripts()
{
    new PythonCreatureScript();
    new PythonAllCreatureScript();
}
