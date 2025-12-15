#include "PythonEngine.h"
#include "PythonAPI.h"

namespace bp = boost::python;
using namespace PyEng::Bridge;

namespace
{
    /**
     * @brief Register global hook (no entry ID)
     *
     * @param eventName Hook name string (ex., "PLAYER_ON_LOGIN")
     * @param callback Python callable object
     */
    void RegisterGlobal(const char* eventName, API::Object callback)
    {
        if (!sPythonEngine->IsEnabled())
            return;

        sPythonEngine->RegisterHook(std::string(eventName), callback, 0);
    }

    /**
     * @brief Register entry-specific hook
     *
     * @param eventName Hook name string (ex., "CREATURE_ON_GOSSIP_HELLO")
     * @param callback Python callable object
     * @param entryId Specific entry ID (creature/item/spell/etc.)
     */
    void RegisterEntry(const char* eventName, API::Object callback, uint32 entryId)
    {
        if (!sPythonEngine->IsEnabled())
            return;

        sPythonEngine->RegisterHook(std::string(eventName), callback, entryId);
    }

} // anonymous namespace

/**
 * @brief Export Hook API Functions to Python
 */
void export_hook_api()
{
    // Usage: azerothcore.Register("PLAYER_ON_LOGIN", on_login)
    bp::def("Register", &RegisterGlobal);

    // Usage: azerothcore.Register("CREATURE_ON_GOSSIP_HELLO", on_gossip_hello, 12345)
    bp::def("Register", &RegisterEntry);
}
