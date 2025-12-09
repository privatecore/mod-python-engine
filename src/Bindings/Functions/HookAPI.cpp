#include "PythonEngine.h"
#include <iostream>

namespace bp = boost::python;

namespace
{
    /**
     * @brief Register global hook (no entry ID)
     *
     * @param eventName Hook name string (for ex., "PLAYER_ON_LOGIN")
     * @param callback Python callable object
     */
    void RegisterGlobal(const char* eventName, PythonAPI::Object callback)
    {
        if (!sPythonEngine->IsEnabled())
            return;

        sPythonEngine->RegisterHook(std::string(eventName), callback, 0);
    }

    /**
     * @brief Register entry-specific hook
     *
     * @param eventName Hook name string (for ex., "CREATURE_ON_GOSSIP_HELLO")
     * @param callback Python callable object
     * @param entryId Specific entry ID (creature/item/spell/etc.)
     */
    void RegisterEntry(const char* eventName, PythonAPI::Object callback, uint32 entryId)
    {
        if (!sPythonEngine->IsEnabled())
            return;

        sPythonEngine->RegisterHook(std::string(eventName), callback, entryId);
    }

} // anonymous namespace

/**
 * @brief Export Hook API Functions
 */
void export_hook_api()
{
    // Usage: ac.Register("PLAYER_ON_LOGIN", on_login)
    bp::def("Register", &RegisterGlobal);

    // Usage: ac.Register("CREATURE_ON_GOSSIP_HELLO", on_gossip_hello, 12345)
    bp::def("Register", &RegisterEntry);
}
