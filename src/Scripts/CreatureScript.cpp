#include "HookMacros.h"
#include "ScriptMgr.h"
#include "Creature.h"
#include "Player.h"

class PythonCreatureScript : public CreatureScript
{
public:
    PythonCreatureScript() : CreatureScript("PythonCreatureScript") {}

    /**
     * @brief Disable database binding requirement and suppress errors like:
     * Script named '<PythonEntityScript>' is not assigned in the database.
     *
     * @todo should use AllCreatureScript instead?
     */
    bool IsDatabaseBound() const override { return false; }

    /**
     * @brief Called when a player opens a gossip dialog with the creature
     *
     * @param player Contains information about the Player
     * @param creature Contains information about the Creature
     * @return False if you want to continue, true if you want to disable
     */
    bool OnGossipHello(Player* player, Creature* creature) override
    {
        TRIGGER_CREATURE_HOOK(ON_GOSSIP_HELLO, creature->GetEntry(), player, creature);
        return false;
    }

    /**
     * @brief Called when a player selects a gossip item in the creature's gossip menu
     *
     * @param player Contains information about the Player
     * @param creature Contains information about the Creature
     * @param sender Contains information about the sender type
     * @param action Contains information about the action id
     * @return False if you want to continue, true if you want to disable
     */
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) override
    {
        TRIGGER_CREATURE_HOOK(ON_GOSSIP_SELECT, creature->GetEntry(), player, creature, sender, action);
        return false;
    }

    /**
     * @brief Called when a player selects a gossip with a code in the creature's gossip menu
     *
     * @param player Contains information about the Player
     * @param creature Contains information about the Creature
     * @param sender Contains information about the sender type
     * @param action Contains information about the action id
     * @param code Contains information about the code entered
     * @return False if you want to continue, true if you want to disable
     */
    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code) override
    {
        TRIGGER_CREATURE_HOOK(ON_GOSSIP_SELECT_CODE, creature->GetEntry(), player, creature, sender, action, code);
        return false;
    }

    /**
     * @brief Called when a player accepts a quest from the creature
     *
     * @param player Contains information about the Player
     * @param creature Contains information about the Creature
     * @param quest Contains information about the Quest
     * @return False if you want to continue, true if you want to disable
     */
    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        TRIGGER_CREATURE_HOOK(ON_QUEST_ACCEPT, creature->GetEntry(), player, creature, quest);
        return false;
    }

    /**
     * @brief Called when a player selects a quest in the creature's quest menu
     *
     * @param player Contains information about the Player
     * @param creature Contains information about the Creature
     * @param quest Contains information about the Quest
     * @return False if you want to continue, true if you want to disable
     */
    bool OnQuestSelect(Player* player, Creature* creature, Quest const* quest) override
    {
        TRIGGER_CREATURE_HOOK(ON_QUEST_SELECT, creature->GetEntry(), player, creature, quest);
        return false;
    }

    /**
     * @brief Called when a player completes a quest with the creature
     *
     * @param player Contains information about the Player
     * @param creature Contains information about the Creature
     * @param quest Contains information about the Quest
     * @return False if you want to continue, true if you want to disable
     */
    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest) override
    {
        TRIGGER_CREATURE_HOOK(ON_QUEST_COMPLETE, creature->GetEntry(), player, creature, quest);
        return false;
    }

    /**
     * @brief Called when a player selects a quest reward
     *
     * @param player Contains information about the Player
     * @param creature Contains information about the Creature
     * @param quest Contains information about the Quest
     * @param opt Contains information about the quest's reward id
     * @return False if you want to continue, true if you want to disable
     */
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

    /**
     * @brief This hook runs after adding a creature to the world
     *
     * @param creature Contains information about the Creature
     */
    void OnCreatureAddWorld(Creature* creature) override
    {
        TRIGGER_CREATURE_HOOK(ON_ADD_WORLD, creature->GetEntry(), creature);
    }

    /**
     * @brief This hook runs after removing a creature from the world
     *
     * @param creature Contains information about the Creature
     */
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
