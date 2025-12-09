#include "PythonEngine.h"
#include "ScriptMgr.h"
#include "Chat.h"

using namespace Acore::ChatCommands;

class PythonCommandScript : public CommandScript
{
public:
    PythonCommandScript() : CommandScript("PythonCommandScript") {}

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable pythonCommandTable = {
            { "reload", HandleReloadPythonScripts, SEC_ADMINISTRATOR, Console::Yes }
        };

        static ChatCommandTable commandTable = {
            { "python", pythonCommandTable }
        };

        return commandTable;
    }

    /**
     * @brief Reloads all Python scripts through the Python engine and sends
     * system message that the reload has been performed.
     *
     * @param handler Pointer to the chat handler
     * @param args Unused command arguments
     */
    static bool HandleReloadPythonScripts(ChatHandler* handler, const char* /*args*/)
    {
        sPythonEngine->ReloadScripts();
        handler->SendGlobalGMSysMessage("Python scripts reloaded.");
        return true;
    }
};

void AddPythonCommandScripts()
{
    new PythonCommandScript();
}
