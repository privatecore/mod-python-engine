#ifndef MOD_PYTHON_ENGINE_HOOK_TRAITS_H
#define MOD_PYTHON_ENGINE_HOOK_TRAITS_H

#include "HookDefines.h"
#include <type_traits>

namespace PyEng::Hooks
{
    template<typename HookEnum>
    struct HookTrait;

    /**
     * @brief Simple macro for trait definition
     */
    #define DEFINE_GAME_HOOK_TRAIT(HookEnum, CategoryValue) \
        template<> struct HookTrait<HookEnum> { \
            static constexpr Category category = Category::CategoryValue; \
            static constexpr const char* name = #HookEnum; \
            static constexpr const char* categoryName = #CategoryValue; }

    DEFINE_GAME_HOOK_TRAIT(AccountHook, ACCOUNT);
    DEFINE_GAME_HOOK_TRAIT(PlayerHook, PLAYER);
    DEFINE_GAME_HOOK_TRAIT(CreatureHook, CREATURE);
    DEFINE_GAME_HOOK_TRAIT(GameObjectHook, GAMEOBJECT);
    DEFINE_GAME_HOOK_TRAIT(ItemHook, ITEM);

    #undef DEFINE_GAME_HOOK_TRAIT

    // Validation helpers
    template<typename T, typename = void> struct IsValidHook : std::false_type {};
    template<typename T> struct IsValidHook<T, std::void_t<decltype(HookTrait<T>::category)>> : std::true_type {};
    template<typename T> inline constexpr bool IsValidHookV = IsValidHook<T>::value;

} // namespace PyEng::Hooks

#endif // MOD_PYTHON_ENGINE_HOOK_TRAITS_H
