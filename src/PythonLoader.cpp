#include "PythonEngine.h"
#include "ScriptMgr.h"

// Forward declarations
void AddPythonAccountScripts();
void AddPythonCommandScripts();
void AddPythonCreatureScripts();
void AddPythonGameObjectScripts();
void AddPythonPlayerScripts();

class PythonLoader : public WorldScript
{
public:
    PythonLoader() : WorldScript("PythonLoader") {}

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload)
        {
            // Initialize the Engine (creates the Python VM, registers bindings)
            // @todo create separate method for reload
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

    AddPythonAccountScripts();
    AddPythonCommandScripts();
    AddPythonCreatureScripts();
    AddPythonGameObjectScripts();
    AddPythonPlayerScripts();
}
