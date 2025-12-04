#include "Player.h"
#include "PythonHeaders.h"
#include "PlayerAdapter.h"

namespace bp = boost::python;

/**
 * @brief Player Class - Represents a player character
 * @note Inherits from Unit
 */
void export_player_class()
{
    bp::class_<Player, bp::bases<Unit>, boost::noncopyable> player_class("Player", bp::no_init);

    player_class.def("GetGUID", &PythonPlayerAdapter::GetGUIDLow);
    player_class.def("GetAccountId", &PythonPlayerAdapter::GetAccountId);

    player_class.def("Say", &PythonPlayerAdapter::Say);
    player_class.def("Yell", &PythonPlayerAdapter::Yell);
    player_class.def("SendNotification", &PythonPlayerAdapter::SendNotification);
    player_class.def("SendSysMessage", &PythonPlayerAdapter::SendSysMessage);

    player_class.def("HasItem", &PythonPlayerAdapter::HasItem);
    player_class.def("AddItem", &PythonPlayerAdapter::AddItem);
    player_class.def("DestroyItem", &PythonPlayerAdapter::DestroyItem);
    player_class.def("RemoveItem", &PythonPlayerAdapter::RemoveItem);

    player_class.def("GetMoney", &Player::GetMoney);
    player_class.def("SetMoney", &Player::SetMoney);
    player_class.def("ModifyMoney", &PythonPlayerAdapter::ModifyMoney);

    player_class.def("TeleportTo", &PythonPlayerAdapter::TeleportTo);

    player_class.def("HasQuest", &Player::HasQuest);
    player_class.def("CompleteQuest", &Player::SendQuestComplete);
}
