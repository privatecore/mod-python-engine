#include "AutoRegistryMgr.h"
#include "PythonHeaders.h"

// Create Exports scope for the forwards
CREATE_REGISTRY_SCOPE(Exports);

// Forward declarations into the Exports scope
REGISTER_TO_SCOPE(Exports, export_unit_class, 20);
REGISTER_TO_SCOPE(Exports, export_worldobject_class, 10);
REGISTER_TO_SCOPE(Exports, export_player_class, 21);
REGISTER_TO_SCOPE(Exports, export_game_constants, 1);
REGISTER_TO_SCOPE(Exports, export_hook_api, 0);
REGISTER_TO_SCOPE(Exports, export_object_class, 5);

// Register module name with Python before Py_Initialize()
extern "C" PyObject* PyInit_azerothcore();

/**
 * @brief Registers the C++ azerothcore module into Python's internal table of
 * modules before the interpreter starts. This allows Python scripts to import
 * and use C++ functionality via import azerothcore.
 */
void InitAzerothCoreModule()
{
    // NOTE: Must match BOOST_PYTHON_MODULE name below
    if (PyImport_AppendInittab("azerothcore", PyInit_azerothcore) == -1)
        throw std::runtime_error("Failed to append azerothcore module to inittab");
}

/**
 * @brief Construct a new boost python module object
 */
BOOST_PYTHON_MODULE(azerothcore)
{
    EXECUTE_REGISTRY_SCOPE(Exports);
}
