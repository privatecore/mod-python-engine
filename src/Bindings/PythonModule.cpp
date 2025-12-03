#include "PythonEngine.h"

// Forward declarations
void export_hook_api();
void export_game_constants();
void export_unit_class();
void export_creature_class();
void export_player_class();
void export_gameobject_class();
void export_item_class();

// Register module name with Python before Py_Initialize()
extern "C" PyObject* PyInit_azerothcore();

/**
 * @brief Registers the C++ azerothcore module into Python's internal table of built-in
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
    // Register the Register() function for hook registration
    export_hook_api();

    // Register all game constants (races, classes, powers, etc.)
    export_game_constants();

    // Register all game classes (Unit, Player, Creature, etc.)
    export_unit_class();
    export_creature_class();
    export_player_class();
    export_gameobject_class();
    export_item_class();
}
