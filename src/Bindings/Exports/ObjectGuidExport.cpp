#include "PythonHeaders.h"
#include "ObjectGuid.h"

namespace bp = boost::python;

/**
 * @brief ObjectGuid Class - Unique identifier value type for game entities
 */
void export_objectguid_class()
{
    bp::class_<ObjectGuid> objectguid_class("ObjectGuid");

    // constructor
    objectguid_class.def(bp::init<>());
    objectguid_class.def(bp::init<uint64>(bp::arg("rawValue")));

    // common
    objectguid_class.def("GetRawValue", &ObjectGuid::GetRawValue);
    objectguid_class.def("GetCounter", &ObjectGuid::GetCounter);
    objectguid_class.def("IsEmpty", &ObjectGuid::IsEmpty);
    objectguid_class.def("Clear", &ObjectGuid::Clear);

    // type check
    objectguid_class.def("IsPlayer", &ObjectGuid::IsPlayer);
    objectguid_class.def("IsCreature", &ObjectGuid::IsCreature);
    objectguid_class.def("IsGameObject", &ObjectGuid::IsGameObject);
    objectguid_class.def("IsItem", &ObjectGuid::IsItem);
    objectguid_class.def("IsPet", &ObjectGuid::IsPet);
    objectguid_class.def("IsVehicle", &ObjectGuid::IsVehicle);
    objectguid_class.def("IsUnit", &ObjectGuid::IsUnit);

    // comparison
    objectguid_class.def(bp::self == bp::self);
    objectguid_class.def(bp::self != bp::self);
    objectguid_class.def(bp::self < bp::self);

    // string repr
    objectguid_class.def("ToString", &ObjectGuid::ToString);
    objectguid_class.def("__str__", &ObjectGuid::ToString);
    objectguid_class.def("__repr__", &ObjectGuid::ToString);
    objectguid_class.def("__hash__", &ObjectGuid::GetRawValue);
}
