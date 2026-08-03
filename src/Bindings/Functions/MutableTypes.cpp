#include "PythonHeaders.h"
#include "PythonMutable.h"

namespace bp = boost::python;
using namespace PyEng::Bridge;

template<typename T>
void register_mutable_type(char const* name, char const* int_converter = "__int__")
{
    using MutableT = Mutable<T>;

    bp::class_<MutableT>(name, bp::no_init)
        .def("get", &MutableT::get, "Get the current value")
        .def("set", &MutableT::set, bp::arg("value"), "Set a new value")
        .def(int_converter, &MutableT::get, "Convert to Python value")
        .def("__repr__", &MutableT::repr);
}

/**
 * @brief Export Mutable Types to Python
 */
void export_mutable_types()
{
    register_mutable_type<int8>("Int8Ref");
    register_mutable_type<int16>("Int16Ref");
    register_mutable_type<int32>("Int32Ref");
    register_mutable_type<int64>("Int64Ref");
    register_mutable_type<uint8>("UInt8Ref");
    register_mutable_type<uint16>("UInt16Ref");
    register_mutable_type<uint32>("UInt32Ref");
    register_mutable_type<uint64>("UInt64Ref");

    register_mutable_type<float>("FloatRef", "__float__");
    register_mutable_type<double>("DoubleRef", "__float__");
    register_mutable_type<bool>("BoolRef", "__bool__");
}
