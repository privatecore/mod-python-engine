#include "HookMacros.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Spell.h"

class PythonItemScript : public ItemScript
{
public:
    PythonItemScript() : ItemScript("PythonItemScript") {}

    /**
     * @brief Disable database binding requirement and suppress errors like:
     * Script named '<PythonEntityScript>' is not assigned in the database.
     *
     * @todo should use AllItemScript instead?
     */
    bool IsDatabaseBound() const override { return false; }

    /**
     * @brief Called when a player accepts a quest from the item
     *
     * @param player Contains information about the Player
     * @param item Contains information about the Item
     * @param quest Contains information about the Quest
     * @return False if you want to continue, true if you want to disable
     */
    bool OnQuestAccept(Player* player, Item* item, Quest const* quest) override
    {
        TRIGGER_ITEM_HOOK(ON_USE, item->GetEntry(), player, item, quest);
        return false;
    }

    /**
     * @brief Called when a player uses the item
     *
     * @param player Contains information about the Player
     * @param item Contains information about the Item
     * @param targets Contains information about the SpellCastTargets
     * @return False if you want to continue, true if you want to disable
     */
    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
    {
        TRIGGER_ITEM_HOOK(ON_USE, item->GetEntry(), player, item, targets);
        return false;
    }

    /**
     * @brief Called when the item is destroyed
     *
     * @param player Contains information about the Player
     * @param item Contains information about the Item
     * @return False if you want to continue, true if you want to disable
     */
    bool OnRemove(Player* player, Item* item) override
    {
        TRIGGER_ITEM_HOOK(ON_USE, item->GetEntry(), player, item);
        return false;
    }

    /**
     * @brief Called before casting a combat spell from this item (chance on hit
     * spells of item template, can be used to prevent cast if returning false)
     *
     * @param player Contains information about the Player
     * @param victim Contains information about the victim Unit
     * @param spellInfo Contains information about the SpellInfo
     * @param item Contains information about the Item
     * @return False if you want to continue, true if you want to disable
     */
    bool OnCastItemCombatSpell(Player* player, Unit* victim, SpellInfo const* spellInfo, Item* item) override
    {
        TRIGGER_ITEM_HOOK(ON_USE, item->GetEntry(), player, victim, spellInfo, item);
        return true;
    }

    /**
     * @brief Called when the item expires (is destroyed)
     *
     * @param player Contains information about the Player
     * @param proto Contains information about the ItemTemplate
     * @return False if you want to continue, true if you want to disable
     */
    bool OnExpire(Player* player, ItemTemplate const* proto) override
    {
        TRIGGER_ITEM_HOOK(ON_USE, proto->ItemId, player, proto);
        return false;
    }

    /**
     * @brief Called when a player selects an option in an item gossip window
     *
     * @param player Contains information about the Player
     * @param item Contains information about the Item
     * @param sender Contains information about the sender type
     * @param action Contains information about the action id
     */
    void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action) override
    {
        TRIGGER_ITEM_HOOK(ON_USE, item->GetEntry(), player, item, sender, action);
    }

    /**
     * @brief Called when a player selects an option in an item gossip window
     *
     * @param player Contains information about the Player
     * @param item Contains information about the Item
     * @param sender Contains information about the sender type
     * @param action Contains information about the action id
     * @param code Contains information about the code entered
     */
    void OnGossipSelectCode(Player* player, Item* item, uint32 sender, uint32 action, const char* code) override
    {
        TRIGGER_ITEM_HOOK(ON_USE, item->GetEntry(), player, item, sender, action, code);
    }
};

void AddPythonItemScripts()
{
    new PythonItemScript();
}
