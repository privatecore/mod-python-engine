#include "PythonEngine.h"
#include "Config.h"
#include "Log.h"
#include "Timer.h"
#include <filesystem>

namespace fs = std::filesystem;

// Singleton Instance
PythonEngine* PythonEngine::instance()
{
    static PythonEngine instance;
    return &instance;
}

PythonEngine::~PythonEngine()
{
    // Destructor calls Shutdown just in case it wasn't called manually
    Shutdown();
}

void PythonEngine::Initialize()
{
    if (Py_IsInitialized())
        return;

    enabled = sConfigMgr->GetOption<bool>("Python.Enabled", true);
    if (!enabled)
    {
        LOG_INFO("module.python", "Python Engine is disabled in config.");
        return;
    }

    LOG_INFO("module.python", "Initializing Python Engine...");

    try
    {
        InitAzerothCoreModule();
        Py_Initialize();

        PythonAPI::Object main_module = PythonAPI::Import("__main__");
        main_namespace = main_module.attr("__dict__");

        LOG_INFO("module.python", "Python Engine Initialized Successfully.");
    }
    catch (...)
    {
        LOG_ERROR("module.python", "Python Engine Initialization Failed!");
        LogException();
        enabled = false;
    }
}

void PythonEngine::Shutdown()
{
    if (!Py_IsInitialized())
        return;

    LOG_INFO("module.python", "Shutting down Python Engine...");

    {
        std::unique_lock<std::shared_mutex> lock(hookMutex);
        PythonAPI::GILGuard gil;

        hookMap.clear();
        main_namespace = PythonAPI::Object(); // Release main module ref
    }

    // Py_Finalize should generally be called only if we are sure no other C++
    // statics need Python
    Py_Finalize();
    enabled = false;

    LOG_INFO("module.python", "Python Engine shutdown complete.");
}

void PythonEngine::LoadScripts()
{
    if (!enabled)
        return;

    uint32 oldMSTime = getMSTime();

    LOG_INFO("module.python", "Loading Python scripts...");

    std::string pathStr = sConfigMgr->GetOption<std::string>("Python.ScriptsPath", "python_scripts");
    fs::path scriptsPath(pathStr);

    if (!scriptsPath.is_absolute())
        scriptsPath = fs::current_path() / scriptsPath;

    if (!fs::exists(scriptsPath))
    {
        LOG_ERROR("module.python", "Python scripts directory not found: {}", scriptsPath.string());
        return;
    }

    int count = 0;
    for (const auto& entry : fs::recursive_directory_iterator(scriptsPath))
    {
        if (entry.path().extension() != ".py")
            continue;

        ExecuteScript(entry.path().string());
        count++;
    }

    LOG_INFO("module.python", ">> Loaded {} Python scripts in {} ms.", count, GetMSTimeDiffToNow(oldMSTime));
}

void PythonEngine::ReloadScripts()
{
    if (!enabled)
        return;

    reloading = true;

    LOG_DEBUG("module.python", "Clearing Hooks registry...");

    {
        std::unique_lock<std::shared_mutex> lock(hookMutex);
        PythonAPI::GILGuard gil;

        hookMap.clear();
    }
    // Release lock here to allow re-entry during script execution if needed
    // (though ExecuteScript re-locks GIL)

    LoadScripts();

    reloading = false;
}

void PythonEngine::ExecuteScript(const std::string& filepath)
{
    if (!enabled)
        return;

    LOG_DEBUG("module.python", "Executing script file: {}...", filepath);

    try
    {
        PythonAPI::GILGuard gil;
        PythonAPI::ExecFile(filepath, main_namespace, main_namespace);
    }
    catch (...)
    {
        LOG_ERROR("module.python", "Failed to execute script file: {}", filepath);
        LogException();
    }
}

void PythonEngine::RegisterHook(const std::string& eventName, PythonAPI::Object callback, uint32 entryId)
{
    if (!enabled || eventName.empty())
        return;

    // Validate that the provided object is actually a function or callable object.
    // This prevents runtime crashes later when the event attempts to trigger.
    if (!PyCallable_Check(callback.ptr()))
    {
        LOG_ERROR("module.python", "Attempted to register a non-callable callback for hook '{}' and entry {}.",
                                   eventName, entryId);
        return;
    }

    auto hookIdOpt = GetHookByName(eventName);
    if (!hookIdOpt.has_value())
    {
        LOG_ERROR("module.python", "Attempted to register unknown event hook '{}'.", eventName);
        return;
    }

    HookInfo hookId = hookIdOpt.value();

    // If triggerDepth > 0, we are currently inside a Trigger (holding shared lock).
    // Attempting to acquire unique lock now would cause a deadlock.
    if (triggerDepth > 0)
    {
        LOG_ERROR("module.python", "CRITICAL: Attempted to register hook '{}' inside an event handler! "
                                   "Dynamic registration causes deadlocks and is forbidden.", eventName);
        return;
    }

    std::unique_lock<std::shared_mutex> lock(hookMutex);
    try
    {
        hookMap[hookId][entryId].push_back(callback);
        LOG_DEBUG("module.python", "Registered hook '{}' for entry {}", eventName, entryId);
    }
    catch (...)
    {
        LOG_ERROR("module.python", "Failed to register hook '{}' for entry {}", eventName, entryId);
        LogException();
    }
}

void PythonEngine::LogException()
{
    try
    {
        std::rethrow_exception(std::current_exception());
    }
    catch (PythonAPI::ErrorAlreadySet const&)
    {
        LogPythonError();
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("module.python", "C++ Exception:\n{}", e.what());
    }
    catch (...)
    {
        LOG_ERROR("module.python", "C++ Exception:\nUnknown non-standard exception.");
    }
}

void PythonEngine::LogPythonError()
{
    if (!PyErr_Occurred())
        return;

    LOG_ERROR("module.python", "Python exception caught (printed to stderr).");
    PyErr_Print();
}
