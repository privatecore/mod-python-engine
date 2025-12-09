#include "PythonHeaders.h"
#include "GameObjectAdapter.h"

namespace bp = boost::python;

/**
 * @brief GameObject Class - Represents game objects (chests, doors, buttons, etc.)
 */
void export_gameobject_class()
{
    using namespace PyEng::GameObjectAdapter;

    bp::class_<GameObject, boost::noncopyable> gameobject_class("GameObject", bp::no_init);

    gameobject_class.def("GetEntry", &GameObject::GetEntry);
    gameobject_class.def("GetName", &GameObject::GetName, bp::return_value_policy<bp::copy_const_reference>());
    gameobject_class.def("Respawn", &Respawn);
    gameobject_class.def("Delete", &GameObject::Delete);
    gameobject_class.def("Use", &Use);
    gameobject_class.def("GetGoState", &GameObject::GetGoState);
    gameobject_class.def("SetGoState", &GameObject::SetGoState);
    gameobject_class.def("IsSpawned", &GameObject::isSpawned);
    gameobject_class.def("GetGUID", &GetGUIDLow);
}
