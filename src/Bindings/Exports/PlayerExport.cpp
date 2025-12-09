#include "PythonHeaders.h"
#include "PlayerAdapter.h"
#include "Player.h"

namespace bp = boost::python;

/**
 * @brief Player Class - Represents a player character
 * @note Inherits from Unit
 */
void export_player_class()
{
    using namespace PyEng::PlayerAdapter;

    bp::class_<Player, bp::bases<Unit>, boost::noncopyable> player_class("Player", bp::no_init);

    // common
    player_class.def("GetGUID", &GetGUIDLow);
    player_class.def("GetAccountId", &GetAccountId);

    // level
    player_class.def("GiveXP", &GiveXP);
    player_class.def("GiveLevel", &Player::GiveLevel);
    player_class.def("SetXP", &SetXP);

    // chat
    player_class.def("Say", &Say);
    player_class.def("Yell", &Yell);
    player_class.def("SendNotification", &SendNotification);
    player_class.def("SendSysMessage", &SendSysMessage);

    // item
    player_class.def("HasItem", &HasItem);
    player_class.def("AddItem", &AddItem);
    player_class.def("DestroyItem", &DestroyItem);
    player_class.def("RemoveItem", &RemoveItem);

    // money
    player_class.def("GetMoney", &Player::GetMoney);
    player_class.def("SetMoney", &Player::SetMoney);
    player_class.def("ModifyMoney", &ModifyMoney);

    // teleport
    player_class.def("TeleportTo", &TeleportTo);

    // quest
    player_class.def("HasQuest", &Player::HasQuest);
    player_class.def("CompleteQuest", &Player::SendQuestComplete);
}
