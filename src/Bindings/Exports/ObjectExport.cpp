#include "PythonHeaders.h"
#include "Object.h"

namespace bp = boost::python;

/**
 * @brief Object Class - Base class for all game objects
 */
void export_object_class()
{
    bp::class_<Object, boost::noncopyable> object_class("Object", bp::no_init);

    // common
    object_class.def("GetEntry", &Object::GetEntry);
    object_class.def("GetTypeId", &Object::GetTypeId);
    object_class.def("isType", &Object::isType);

    // type checks
    object_class.def("IsInWorld", &Object::IsInWorld);
    object_class.def("IsItem", &Object::IsItem);
    object_class.def("IsUnit", &Object::IsUnit);
    object_class.def("IsPlayer", &Object::IsPlayer);
    object_class.def("IsCreature", &Object::IsCreature);
    object_class.def("IsGameObject", &Object::IsGameObject);
    object_class.def("IsDynamicObject", &Object::IsDynamicObject);
    object_class.def("IsCorpse", &Object::IsCorpse);

    // field access
    object_class.def("GetUInt32Value", &Object::GetUInt32Value);
    object_class.def("GetFloatValue", &Object::GetFloatValue);
    object_class.def("SetUInt32Value", &Object::SetUInt32Value);
    object_class.def("SetFloatValue", &Object::SetFloatValue);

    // flags
    object_class.def("HasFlag", &Object::HasFlag);
    object_class.def("SetFlag", &Object::SetFlag);
    object_class.def("RemoveFlag", &Object::RemoveFlag);
}

/**
 * @brief WorldObject Class - Base class for objects in the game world
 * @note Inherits from Object, WorldObject
 */
void export_worldobject_class()
{
    bp::class_<WorldObject, bp::bases<Object>, boost::noncopyable> worldobject_class("WorldObject", bp::no_init);

    // common
    worldobject_class.def("GetName", &WorldObject::GetName, bp::return_value_policy<bp::copy_const_reference>());

    // location
    worldobject_class.def("GetInstanceId", &WorldObject::GetInstanceId);
    worldobject_class.def("GetAreaId", &WorldObject::GetAreaId);
    worldobject_class.def("GetZoneId", &WorldObject::GetZoneId);
    worldobject_class.def("GetMap", &WorldObject::GetMap, bp::return_value_policy<bp::reference_existing_object>());
}
