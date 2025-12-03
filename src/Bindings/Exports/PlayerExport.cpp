#include "PythonHeaders.h"
#include "PlayerAdapter.h"

namespace bp = boost::python;

/**
 * @brief Player Class - Represents a player character
 * @note Inherits from Unit
 */
void export_player_class()
{
    bp::class_<Player, bp::bases<Unit>, boost::noncopyable>("Player", bp::no_init)
        .def("Say", &PythonPlayerAdapter::Say)
        .def("Yell", &PythonPlayerAdapter::Yell)
        .def("SendNotification", &PythonPlayerAdapter::SendNotification)
        .def("SendSysMessage", &PythonPlayerAdapter::SendSysMessage)
        .def("AddItem", &PythonPlayerAdapter::AddItem)
        .def("RemoveItem", &PythonPlayerAdapter::RemoveItem)
        .def("HasItem", &PythonPlayerAdapter::HasItem)
        .def("GetMoney", &Player::GetMoney)
        .def("SetMoney", &Player::SetMoney)
        .def("TeleportTo", &PythonPlayerAdapter::TeleportTo)
        .def("HasQuest", &Player::HasQuest)
        .def("CompleteQuest", &Player::SendQuestComplete)
        .def("GetAccountId", &PythonPlayerAdapter::GetAccountId)
        .def("GetGUID", &PythonPlayerAdapter::GetGUIDLow);
}
