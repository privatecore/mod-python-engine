#ifndef MOD_PYTHON_ENGINE_PLAYER_ADAPTER_H
#define MOD_PYTHON_ENGINE_PLAYER_ADAPTER_H

#include "Define.h"
#include "Player.h"
#include "Chat.h"

namespace PythonPlayerAdapter
{
    inline uint32 GetGUIDLow(Player* player)
    {
        return player ? player->GetGUID().GetCounter() : 0;
    }

    inline uint32 GetAccountId(Player* player)
    {
        return player && player->GetSession() ? player->GetSession()->GetAccountId() : 0;
    }

    inline void Say(Player* player, const std::string& text, uint32 language)
    {
        if (player)
            player->Say(text, static_cast<Language>(language));
    }

    static void Yell(Player* player, const std::string& text, uint32 language)
    {
        if (player)
            player->Yell(text, static_cast<Language>(language));
    }

    static void SendNotification(Player* player, const std::string& text)
    {
        if (player && player->GetSession())
        {
            ChatHandler handler(player->GetSession());
            handler.SendNotification(text);
        }
    }

    inline void SendSysMessage(Player* player, const std::string& text)
    {
        if (player && player->GetSession())
        {
            ChatHandler handler(player->GetSession());
            handler.SendSysMessage(text);
        }
    }

    inline void AddItem(Player* player, uint32 itemId, uint32 count)
    {
        if (player)
            player->AddItem(itemId, count);
    }

    inline void RemoveItem(Player* player, uint32 item, uint32 count)
    {
        if (player)
            player->DestroyItemCount(item, count, true, false);
    }

    inline bool HasItem(Player* player, uint32 item, uint32 count)
    {
        if (!player)
            return false;

        return player->HasItemCount(item, count);
    }

    inline bool TeleportTo(Player* player, uint32 mapid, float x, float y, float z, float o)
    {
        if (!player)
            return false;

        return player->TeleportTo(mapid, x, y, z, o);
    }

} // namespace PythonPlayerAdapter

#endif // MOD_PYTHON_ENGINE_PLAYER_ADAPTER_H
