#include "AutoRegistryMgr.h"
#include "PythonEngine.h"
#include "ScriptMgr.h"

// Create Scripts scope for the forwards
CREATE_REGISTRY_SCOPE(Scripts);

// Forward declarations into the Scripts scope
REGISTER_TO_SCOPE(Scripts, AddPythonAccountScripts);
REGISTER_TO_SCOPE(Scripts, AddPythonCommandScripts);
REGISTER_TO_SCOPE(Scripts, AddPythonCreatureScripts);
REGISTER_TO_SCOPE(Scripts, AddPythonGameObjectScripts);
REGISTER_TO_SCOPE(Scripts, AddPythonItemScripts);
REGISTER_TO_SCOPE(Scripts, AddPythonPlayerScripts);

class PythonLoader : public WorldScript
{
public:
    PythonLoader() : WorldScript("PythonLoader") {}

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload)
        {
            // Initialize the Engine (creates the Python VM, registers bindings)
            // @todo create separate method for reload(?)
            sPythonEngine->Initialize();
        }
    }

    void OnBeforeWorldInitialized() override
    {
        // Immediately load all scripts from Python.ScriptsPath
        sPythonEngine->LoadScripts();
    }

    void OnAfterUnloadAllMaps() override
    {
        // Ensure the Python engine is turned off safely, preventing memory
        // leaks or hanging processes
        sPythonEngine->Shutdown();
    }
};

void Addmod_python_engineScripts()
{
    new PythonLoader();

    EXECUTE_REGISTRY_SCOPE(Scripts);
}
