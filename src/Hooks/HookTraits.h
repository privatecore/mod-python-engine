#ifndef MOD_PYTHON_ENGINE_HOOK_TRAITS_H
#define MOD_PYTHON_ENGINE_HOOK_TRAITS_H

#include "HookDefines.h"
#include <type_traits>

/**
 * @brief Simple Macro for Trait Definition
 */
#define DEFINE_HOOK_TRAIT(HookEnum, CategoryValue) \
    template<> struct HookTrait<HookEnum> { \
        static constexpr Category category = Category::CategoryValue; \
        static constexpr const char* name = #HookEnum; \
        static constexpr const char* categoryName = CategoryToString(category); \
    }

namespace Hooks
{
    template<typename T>
    struct HookTrait;

    /**
     * @brief Converts a Category enum value to its string representation
     *
     * @param category Category enum value to convert
     * @return Null-terminated string representing the category name
     */
    constexpr const char* CategoryToString(Category category)
    {
        switch (category)
        {
            case Category::ACCOUNT:     return "ACCOUNT";
            case Category::PLAYER:      return "PLAYER";
            case Category::CREATURE:    return "CREATURE";
            case Category::GAMEOBJECT:  return "GAMEOBJECT";
            case Category::ITEM:        return "ITEM";
            default:                    return "UNKNOWN";
        }
    }

    DEFINE_HOOK_TRAIT(AccountHook,      ACCOUNT);
    DEFINE_HOOK_TRAIT(PlayerHook,       PLAYER);
    DEFINE_HOOK_TRAIT(CreatureHook,     CREATURE);
    DEFINE_HOOK_TRAIT(GameObjectHook,   GAMEOBJECT);
    DEFINE_HOOK_TRAIT(ItemHook,         ITEM);

    // Validation helper
    template<typename T, typename = void> struct IsValidHook : std::false_type {};
    template<typename T> struct IsValidHook<T, std::void_t<decltype(HookTrait<T>::category)>> : std::true_type {};
    template<typename T> inline constexpr bool IsValidHookV = IsValidHook<T>::value;

} // namespace Hooks

#endif // MOD_PYTHON_ENGINE_HOOK_TRAITS_H
