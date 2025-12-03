#include "PythonEngine.h"
#include "HookMacros.h"
#include "ScriptMgr.h"

class PythonAccountScript : public AccountScript
{
public:
    PythonAccountScript() : AccountScript("PythonAccountScript") {}

    void OnAccountLogin(uint32 accountId) override
    {
        TRIGGER_ACCOUNT_HOOK(ON_ACCOUNT_LOGIN, accountId);
    }

    void OnFailedAccountLogin(uint32 accountId) override
    {
        TRIGGER_ACCOUNT_HOOK(ON_FAILED_ACCOUNT_LOGIN, accountId);
    }
};

void AddPythonAccountScripts()
{
    new PythonAccountScript();
}
