#ifndef MOD_PYTHON_ENGINE_GIL_H
#define MOD_PYTHON_ENGINE_GIL_H

#include "PythonHeaders.h"

namespace PyEng::Bridge
{
    // RAII guard for the GIL
    class GILGuard
    {
    public:
        GILGuard() : state(PyGILState_Ensure()) {}
        ~GILGuard() { PyGILState_Release(state); }

        GILGuard(const GILGuard&) = delete;
        GILGuard& operator=(const GILGuard&) = delete;

    private:
        PyGILState_STATE state;
    };

} // namespace PyEng::Bridge

#endif // MOD_PYTHON_ENGINE_GIL_H
