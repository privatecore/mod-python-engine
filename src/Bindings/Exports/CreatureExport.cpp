#include "PythonHeaders.h"
#include "CreatureAdapter.h"

namespace bp = boost::python;

/**
 * @brief Creature Class - Represents NPCs, monsters, pets, etc.
 * @note Inherits from Unit
 */
void export_creature_class()
{
    bp::class_<Creature, bp::bases<Unit>, boost::noncopyable>("Creature", bp::no_init)
        .def("GetEntry", &Creature::GetEntry)
        .def("Despawn", &Creature::DespawnOrUnsummon)
        .def("Respawn", &PythonCreatureAdapter::Respawn)
        .def("Say", &PythonCreatureAdapter::Say)
        .def("Yell", &PythonCreatureAdapter::Yell)
        .def("GetGUID", &PythonCreatureAdapter::GetGUIDLow);
}
