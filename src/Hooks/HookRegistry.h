#ifndef MOD_PYTHON_ENGINE_HOOK_REGISTRY_H
#define MOD_PYTHON_ENGINE_HOOK_REGISTRY_H

#include "HookInfo.h"
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace PyEng::Hooks
{
    /**
     * @brief String-to-HookInfo lookup table (auto-populated at static init)
     *
     * This map is filled during static initialization by DEFINE_GAME_HOOK macros.
     * Each DEFINE_GAME_HOOK creates a constant and registers its string name here.
     *
     * Example after initialization:
     *   "PLAYER_ON_LOGIN"          -> HookInfo{Category::PLAYER, 32}
     *   "PLAYER_ON_LOGOUT"         -> HookInfo{Category::PLAYER, 34}
     *   "CREATURE_ON_GOSSIP_HELLO" -> HookInfo{Category::CREATURE, 0}
     */
    inline std::unordered_map<std::string, HookInfo>& GetHookMap()
    {
        static std::unordered_map<std::string, HookInfo> hookMap;
        return hookMap;
    }

    /**
     * @brief Internal registration helper called by DEFINE_GAME_HOOK macro
     *
     * @param name String identifier for the hook (ex., "PLAYER_ON_LOGIN")
     * @param info Hook identifier structure
     * @return Always returns true (used for static initialization)
     */
    inline bool RegisterHookInternal(const char* name, HookInfo info)
    {
        GetHookMap()[name] = info;
        return true;
    }

    /**
     * @brief Resolves a string hook name to its corresponding HookInfo
     *
     * @param name String identifier for the hook (ex., "PLAYER_ON_LOGIN")
     * @return HookInfo if found, otherwise std::nullopt
     */
    inline std::optional<HookInfo> GetHookByName(std::string_view name)
    {
        auto const& hookMap = GetHookMap();
        auto itr = hookMap.find(std::string(name));
        return itr != hookMap.end() ? std::optional{itr->second} : std::nullopt;
    }

} // namespace PyEng::Hooks

/**
 * @brief Macro to define a hook constant and auto-register its string mapping
 *
 * This macro does two things:
 * 1. Creates a constexpr HookInfo constant with the given name
 * 2. Registers the hook name WITH CATEGORY PREFIX in the string lookup map
 *
 * Usage: DEFINE_GAME_HOOK(PLAYER, ON_LOGIN, 32)
 */
#define DEFINE_GAME_HOOK(CategoryName, HookName, Id) \
    inline constexpr HookInfo HookName = {Category::CategoryName, Id}; \
    inline bool HookName##_registered = PyEng::Hooks::RegisterHookInternal(#CategoryName "_" #HookName, HookName);

#endif // MOD_PYTHON_ENGINE_HOOK_REGISTRY_H
