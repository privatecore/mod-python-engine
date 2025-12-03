#ifndef MOD_PYTHON_ENGINE_API_H
#define MOD_PYTHON_ENGINE_API_H

#include "PythonHeaders.h"
#include <string>

struct PythonAPI
{
    // Core type aliases
    using Object = boost::python::object;
    using List = boost::python::list;
    using Dict = boost::python::dict;
    using Tuple = boost::python::tuple;
    using Str = boost::python::str;
    using ErrorAlreadySet = boost::python::error_already_set;

    // Helpers
    template<typename T>
    static inline auto Ptr(T* ptr)
    {
        return boost::python::ptr(ptr);
    }
    template<typename T>
    static inline T Extract(const Object& obj)
    {
        return boost::python::extract<T>(obj);
    }
    static inline bool IsNone(const Object& obj) { return obj.ptr() == Py_None; }
    static inline Object FromString(const std::string& s) { return Object(s); }
    static inline Object Import(const std::string& name) { return boost::python::import(boost::python::str(name)); }
    static inline Object ExecFile(const std::string& filepath, Object& globals, Object& locals)
    {
        return boost::python::exec_file(filepath.c_str(), globals, locals);
    }

    // RAII guard for the GIL
    struct GILGuard
    {
        PyGILState_STATE state;
        GILGuard() { state = PyGILState_Ensure(); }
        ~GILGuard() { PyGILState_Release(state); }
        GILGuard(const GILGuard&) = delete;
        GILGuard& operator=(const GILGuard&) = delete;
    };
};

#endif // MOD_PYTHON_ENGINE_API_H
