#include "PythonHeaders.h"
#include "UnitAdapter.h"

namespace bp = boost::python;

/**
 * @brief Unit Class - Base class for all entities (players, creatures, pets)
 */
void export_unit_class()
{
    bp::class_<Unit, boost::noncopyable>("Unit", bp::no_init)
        .def("GetName", &Unit::GetName, bp::return_value_policy<bp::copy_const_reference>())
        .def("GetLevel", &Unit::GetLevel)
        .def("GetGUID", &PythonUnitAdapter::GetGUIDLow)
        .def("GetHealth", &Unit::GetHealth)
        .def("GetMaxHealth", &Unit::GetMaxHealth)
        .def("SetHealth", &Unit::SetHealth, bp::args("val"))
        .def("GetPower", &Unit::GetPower, bp::args("power"))
        .def("GetMaxPower", &Unit::GetMaxPower, bp::args("power"))
        .def("IsAlive", &Unit::IsAlive)
        .def("IsDead", &Unit::isDead)
        .def("IsInCombat", &Unit::IsInCombat)
        .def("GetGender", &Unit::getGender)
        .def("GetRace", &Unit::getRace, bp::arg("original") = false)
        .def("GetClass", &Unit::getClass);
}
