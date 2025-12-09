#ifndef MOD_PYTHON_ENGINE_AUTO_REGISTRY_H
#define MOD_PYTHON_ENGINE_AUTO_REGISTRY_H

#include <algorithm>
#include <vector>

/**
 * @brief Priority-based function registry with isolated scopes. The original
 * idea comes from ScriptRegistry in the core sources.
 *
 * @tparam Tag Unique type identifier for scopes
 */
template<typename Tag>
class AutoRegistry
{
public:
    /**
     * @brief Register function with priority
     *
     * @param func Function pointer to register
     * @param priority Execution priority (lower = executes first)
     */
    static void Register(void (*func)(), int priority = 0)
    {
        GetHandlers().emplace_back(Entry{priority, func});
    }

    /**
     * @brief Execute all registered functions sorted by priority
     */
    static void Execute()
    {
        auto& handlers = GetHandlers();

        std::stable_sort(handlers.begin(), handlers.end());
        for (auto& entry : handlers)
            entry.func();
    }

private:
    struct Entry
    {
        int priority;   // lower = executes first
        void (*func)(); // function pointer

        bool operator<(const Entry& other) const noexcept { return priority < other.priority; }
    };

    /**
     * @brief Get the Handlers objectGet static handlers storage
     *
     * @return Reference to static handlers vector
     */
    static std::vector<Entry>& GetHandlers()
    {
        static std::vector<Entry> handlers;
        return handlers;
    }
};

#define CREATE_REGISTRY_SCOPE(ScopeName) \
    struct ScopeName##_Tag {}; \
    inline void Execute##ScopeName() { AutoRegistry<ScopeName##_Tag>::Execute(); }

#define REGISTER_TO_SCOPE(ScopeName, FuncName, ...) \
    extern void FuncName(); \
    namespace { \
        struct AutoRegister##FuncName { \
            AutoRegister##FuncName() { \
                AutoRegistry<ScopeName##_Tag>::Register(&FuncName, ##__VA_ARGS__); } \
        } autoRegister##FuncName; }

#define EXECUTE_REGISTRY_SCOPE(ScopeName) \
    AutoRegistry<ScopeName##_Tag>::Execute()

#endif // MOD_PYTHON_ENGINE_AUTO_REGISTRY_H
