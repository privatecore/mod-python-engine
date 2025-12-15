#include "PythonHeaders.h"
#include "Adapters/CreatureAdapter.h"

namespace bp = boost::python;

/**
 * @brief Creature Class - Represents NPCs, monsters, pets, etc.
 * @note Inherits from Unit
 */
void export_creature_class()
{
    using namespace PyEng::CreatureAdapter;

    bp::class_<Creature, bp::bases<Unit>, boost::noncopyable> creature_class("Creature", bp::no_init);

    creature_class.def("GetEntry", &Creature::GetEntry);
    creature_class.def("Despawn", &Creature::DespawnOrUnsummon);
    creature_class.def("Respawn", &Respawn);
    creature_class.def("Say", &Say);
    creature_class.def("Yell", &Yell);
    creature_class.def("GetGUID", &GetGUIDLow);
}
