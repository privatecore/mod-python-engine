// PythonEngine.h
#ifndef MOD_PYTHON_ENGINE_ENGINE_H
#define MOD_PYTHON_ENGINE_ENGINE_H

#include "PythonAPI.h"
#include "HookRegistry.h"
#include "Define.h"
#include <atomic>
#include <shared_mutex>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

// Forward declaration
void InitAzerothCoreModule();

class PythonEngine
{
public:
    [[nodiscard]] static PythonEngine* instance();

    PythonEngine(const PythonEngine&) = delete;
    PythonEngine& operator=(const PythonEngine&) = delete;

    void Initialize();
    void LoadScripts();
    void ReloadScripts();
    void Shutdown();
    void RegisterHook(const std::string& eventName, PythonAPI::Object callback, uint32 entryId = 0);

    [[nodiscard]] bool IsEnabled() const { return enabled; }

    /**
     * @brief Main bridge between C++ game logic and Python scripts. When a specific
     * game event occurs (for ex., player login, creature death), this method looks
     * up all registered Python callbacks and executes them.
     *
     * @param hinfo Hook identifier to trigger (created via MakeHookInfo)
     * @param entryId Specific entry ID (creature/item/spell/etc., 0 for global)
     * @param args Variadic arguments to pass to Python callbacks
     */
    template<typename... Args>
    void Trigger(HookInfo hinfo, uint32 entryId, Args&&... args)
    {
        if (!enabled || reloading)
            return;

        auto argsTuple = std::make_tuple(std::forward<Args>(args)...);

        std::shared_lock<std::shared_mutex> lock(hookMutex);
        TriggerDepthGuard depthGuard;

        auto itr = hookMap.find(hinfo);
        if (itr == hookMap.end())
            return;

        TriggerCallbacks(itr->second, 0, argsTuple); // global hooks
        if (entryId > 0)
            TriggerCallbacks(itr->second, entryId, argsTuple); // entry-specific hooks
    }

private:
    PythonEngine() = default;
    ~PythonEngine();

    void ExecuteScript(const std::string& filepath);
    void LogException();
    void LogPythonError();

    // RAII guard for Trigger Depth
    struct TriggerDepthGuard
    {
        TriggerDepthGuard() { PythonEngine::triggerDepth++; }
        ~TriggerDepthGuard() { PythonEngine::triggerDepth--; }
        TriggerDepthGuard(const TriggerDepthGuard&) = delete;
        TriggerDepthGuard& operator=(const TriggerDepthGuard&) = delete;
    };

    // Type converters
    template<typename T>
    static PythonAPI::Object to_py(T&& v)
    {
        return PythonAPI::Object(std::forward<T>(v));
    }
    template<typename T>
    static PythonAPI::Object to_py(T* p)
    {
        if (!p)
            return PythonAPI::Object();

        return PythonAPI::Object(PythonAPI::Ptr(p));
    }
    static PythonAPI::Object to_py(const char* s) { return PythonAPI::FromString(std::string(s)); }
    static PythonAPI::Object to_py(const std::string& s) { return PythonAPI::FromString(s); }

    /**
     * @brief Executes all registered Python callbacks for a specific hook
     *
     * @param entryMap Map of entity IDs to callback vectors
     * @param entryId Specific entry ID (creature/item/spell/etc., 0 for global)
     * @param argsTuple Tuple of C++ arguments to pass to Python callbacks
     */
    template<typename Tuple>
    void TriggerCallbacks(const std::unordered_map<uint32, std::vector<PythonAPI::Object>>& entryMap, uint32 entryId,
                          const Tuple& argsTuple)
    {
        auto itr = entryMap.find(entryId);
        if (itr == entryMap.end())
            return;

        PythonAPI::GILGuard gil;
        for (const auto& callback : itr->second)
        {
            try
            {
                std::apply([&](const auto&... unpacked_args) { callback(to_py(unpacked_args)...); }, argsTuple);
            }
            catch (...)
            {
                LogException();
            }
        }
    }

    std::atomic<bool> enabled{false};
    std::atomic<bool> reloading{false};
    mutable std::shared_mutex hookMutex;
    inline static thread_local int triggerDepth = 0;

    std::unordered_map<HookInfo, std::unordered_map<uint32, std::vector<PythonAPI::Object>>> hookMap;

    PythonAPI::Object main_namespace;
};

#define sPythonEngine PythonEngine::instance()

#endif // MOD_PYTHON_ENGINE_ENGINE_H
