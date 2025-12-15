#include "PythonHeaders.h"
#include "Adapters/UnitAdapter.h"

namespace bp = boost::python;

/**
 * @brief Unit Class - Base class for all entities (players, creatures, pets)
 * @note Inherits from WorldObject
 */
void export_unit_class()
{
    using namespace PyEng::UnitAdapter;

    bp::class_<Unit, bp::bases<WorldObject>, boost::noncopyable> unit_class("Unit", bp::no_init);

    // common
    unit_class.def("GetGUID", &GetGUIDLow);
    unit_class.def("GetName", &Unit::GetName, bp::return_value_policy<bp::copy_const_reference>());
    unit_class.def("GetGender", &Unit::getGender);
    unit_class.def("GetRace", &Unit::getRace, bp::arg("original") = false);
    unit_class.def("GetClass", &Unit::getClass);
    unit_class.def("GetLevel", &Unit::GetLevel);

    // health/power
    unit_class.def("GetHealth", &Unit::GetHealth);
    unit_class.def("GetMaxHealth", &Unit::GetMaxHealth);
    unit_class.def("SetHealth", &Unit::SetHealth, bp::args("val"));
    unit_class.def("GetPower", &Unit::GetPower, bp::args("power"));
    unit_class.def("GetMaxPower", &Unit::GetMaxPower, bp::args("power"));

    // movement
    unit_class.def("IsInCombat", &Unit::IsInCombat);
    unit_class.def("IsPolymorphed", &Unit::IsPolymorphed);
    unit_class.def("isFrozen", &Unit::isFrozen);
    unit_class.def("IsInFlight", &Unit::IsInFlight);
    unit_class.def("IsLevitating", &Unit::IsLevitating);
    unit_class.def("IsWalking", &Unit::IsWalking);
    unit_class.def("IsMoving", &Unit::isMoving);
    unit_class.def("IsSwimming", &Unit::isSwimming);
    unit_class.def("IsFlying", &Unit::IsFlying);
    unit_class.def("IsFalling", &Unit::IsFalling);
    unit_class.def("IsRooted", &Unit::IsRooted);
    unit_class.def("IsStopped", &Unit::IsStopped);

    // misc
    unit_class.def("IsAlive", &Unit::IsAlive);
    unit_class.def("IsDead", &Unit::isDead);
}
