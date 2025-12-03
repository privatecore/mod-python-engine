#include "PythonHeaders.h"
#include "GameObjectAdapter.h"

namespace bp = boost::python;

/**
 * @brief GameObject Class - Represents game objects (chests, doors, buttons, etc.)
 */
void export_gameobject_class()
{
    bp::class_<GameObject, boost::noncopyable>("GameObject", bp::no_init)
        .def("GetEntry", &GameObject::GetEntry)
        .def("GetName", &GameObject::GetName, bp::return_value_policy<bp::copy_const_reference>())
        .def("Respawn", &PythonGameObjectAdapter::Respawn)
        .def("Delete", &GameObject::Delete)
        .def("Use", &PythonGameObjectAdapter::Use)
        .def("GetGoState", &GameObject::GetGoState)
        .def("SetGoState", &GameObject::SetGoState)
        .def("IsSpawned", &GameObject::isSpawned)
        .def("GetGUID", &PythonGameObjectAdapter::GetGUIDLow);
}
