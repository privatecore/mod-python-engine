#ifndef MOD_PYTHON_ENGINE_HOOK_INFO_H
#define MOD_PYTHON_ENGINE_HOOK_INFO_H

#include "HookTraits.h"
#include <functional>

/**
 * @brief Type-safe hook identifier (global scope)
 */
struct HookInfo
{
    Hooks::Category category;
    uint32 value;

    constexpr bool operator==(const HookInfo& other) const
    {
        return category == other.category && value == other.value;
    }
    constexpr bool operator!=(const HookInfo& other) const { return !(*this == other); }
};

/**
 * @brief Hash specialization for HookInfo using 8-bit compact shift.
 * Memory layout: [category (8-bit)] [value (8-bit)] = 16-bit hash.
 *
 * @warning If hook values exceed 255, increase category_shift to 16
 */
template<>
struct std::hash<HookInfo>
{
    size_t operator()(const HookInfo& hinfo) const noexcept
    {
        static constexpr size_t category_shift = 8;
        static constexpr uint32 value_mask = 0xFF;

        // compile-time validation
        static_assert(sizeof(Hooks::Category) == 1, "Category must be uint8");
        static_assert(category_shift <= 24, "Shift must fit in size_t on 32-bit platforms");

        return (static_cast<size_t>(hinfo.category) << category_shift) |
               (static_cast<size_t>(hinfo.value) & value_mask);
    }
};

/**
 * @brief Type-safe factory function for creating HookInfo identifiers
 *
 * @param henum Specific hook enum value (for ex., PlayerHook::ON_LOGIN)
 * @return Hook identifier containing the category and value
 */
template<typename HookEnum>
inline constexpr HookInfo MakeHookInfo(HookEnum henum)
{
    // compile-time validation
    static_assert(std::is_enum_v<HookEnum>, "MakeHookInfo requires an enum type");
    static_assert(Hooks::IsValidHookV<HookEnum>, "Unknown hook enum type - did you add it with DEFINE_HOOK_TRAIT?");

    return HookInfo{Hooks::HookTrait<HookEnum>::category, static_cast<uint32>(henum)};
}

#endif // MOD_PYTHON_ENGINE_HOOK_INFO_H
