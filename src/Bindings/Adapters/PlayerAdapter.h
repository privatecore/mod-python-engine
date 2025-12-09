#ifndef MOD_PYTHON_ENGINE_PLAYER_ADAPTER_H
#define MOD_PYTHON_ENGINE_PLAYER_ADAPTER_H

#include "Player.h"
#include "Chat.h"

/**
 * @brief Adapter namespace providing simplified Player API wrappers
 */
namespace PyEng::PlayerAdapter
{
    // Get player low part GUID
    inline uint32 GetGUIDLow(Player* player)
    {
        return player ? player->GetGUID().GetCounter() : 0;
    }

    // Get player account ID
    inline uint32 GetAccountId(Player* player)
    {
        return player && player->GetSession() ? player->GetSession()->GetAccountId() : 0;
    }

    // Give experience to player
    inline void GiveXP(Player* player, uint32 xp, Unit* victim = nullptr, float group_rate = 1.0f,
                       bool isLFGReward = false)
    {
        if (player)
            player->GiveXP(xp, victim, group_rate, isLFGReward);
    }

    // Set current experience value for player
    inline void SetXP(Player* player, uint32 xp)
    {
        if (player)
            player->SetUInt32Value(PLAYER_XP, xp);
    }

    // Say text in specified language
    inline void Say(Player* player, const std::string& text, uint32 language)
    {
        if (player)
            player->Say(text, static_cast<Language>(language));
    }

    // Yell text in specified language
    inline void Yell(Player* player, const std::string& text, uint32 language)
    {
        if (player)
            player->Yell(text, static_cast<Language>(language));
    }

    // Send notification to player
    inline void SendNotification(Player* player, const std::string& text)
    {
        if (player && player->GetSession())
        {
            ChatHandler handler(player->GetSession());
            handler.SendNotification(text);
        }
    }

    // Send system message to player
    inline void SendSysMessage(Player* player, const std::string& text)
    {
        if (player && player->GetSession())
        {
            ChatHandler handler(player->GetSession());
            handler.SendSysMessage(text);
        }
    }

    // Check if player has item count
    inline bool HasItem(Player* player, uint32 item, uint32 count)
    {
        if (!player)
            return false;

        return player->HasItemCount(item, count);
    }

    // Add item count to player inventory
    inline void AddItem(Player* player, uint32 itemId, uint32 count)
    {
        if (player)
            player->AddItem(itemId, count);
    }

    // Destroy item from player inventory
    inline void DestroyItem(Player* player, uint32 item, uint32 count)
    {
        if (player)
            player->DestroyItemCount(item, count, true, false);
    }

    // Remove item from specific bag/slot
    inline void RemoveItem(Player* player, uint8 bag, uint8 slot)
    {
        if (player)
            player->RemoveItem(bag, slot, true);
    }

    // Modify player money (add or subtract)
    inline bool ModifyMoney(Player* player, int32 amount)
    {
        if (!player)
            return false;

        return player->ModifyMoney(amount);
    }

    // Teleport player to location (map, x, y, z, o)
    inline bool TeleportTo(Player* player, uint32 mapid, float x, float y, float z, float o)
    {
        if (!player)
            return false;

        return player->TeleportTo(mapid, x, y, z, o);
    }

} // namespace PyEng::PlayerAdapter

#endif // MOD_PYTHON_ENGINE_PLAYER_ADAPTER_H
