#include "HookMacros.h"
#include "ScriptMgr.h"

class PythonAccountScript : public AccountScript
{
public:
    PythonAccountScript() : AccountScript("PythonAccountScript") {}

    /**
     * @brief Called when an account logs in successfully
     *
     * @param accountId Contains information about the account id
     */
    void OnAccountLogin(uint32 accountId) override
    {
        TRIGGER_ACCOUNT_HOOK(ON_ACCOUNT_LOGIN, accountId);
    }

    /**
     * @brief Called when an account login fails
     *
     * @param accountId Contains information about the account id
     */
    void OnFailedAccountLogin(uint32 accountId) override
    {
        TRIGGER_ACCOUNT_HOOK(ON_FAILED_ACCOUNT_LOGIN, accountId);
    }
};

void AddPythonAccountScripts()
{
    new PythonAccountScript();
}
