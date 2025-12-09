#ifndef MOD_PYTHON_ENGINE_HOOK_INFO_H
#define MOD_PYTHON_ENGINE_HOOK_INFO_H

#include "HookTraits.h"
#include <cstddef>
#include <cstdint>
#include <functional>

namespace PyEng::Hooks
{
    /**
     * @brief Type-safe hook identifier
     */
    struct HookInfo
    {
        Category category;
        uint32 value;

        constexpr bool operator==(HookInfo const& other) const noexcept
        {
            return category == other.category && value == other.value;
        }
        constexpr bool operator!=(HookInfo const& other) const noexcept { return !(*this == other); }
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
        static_assert(IsValidHookV<HookEnum>, "Unknown hook enum type - did you add it with DEFINE_HOOK_TRAIT?");

        return HookInfo{HookTrait<HookEnum>::category, static_cast<uint32>(henum)};
    }

} // namespace PyEng::Hooks

namespace std
{
    /**
     * @brief Hash specialization for HookInfo using 8-bit compact shift.
     * Memory layout: [category (8-bit)] [value (8-bit)] = 16-bit hash.
     *
     * @warning If hook values exceed 255, increase category_shift to 16
     */
    template<>
    struct hash<PyEng::Hooks::HookInfo>
    {
        size_t operator()(PyEng::Hooks::HookInfo const& hinfo) const noexcept
        {
            using PyEng::Hooks::Category;

            static constexpr size_t category_shift = 8;
            static constexpr uint32 value_mask = 0xFF;

            static_assert(sizeof(Category) == 1, "Category must be uint8");
            static_assert(category_shift <= 24, "Shift must fit in size_t");

            return (static_cast<size_t>(hinfo.category) << category_shift) |
                   (static_cast<size_t>(hinfo.value) & value_mask);
        }
    };
}

#endif // MOD_PYTHON_ENGINE_HOOK_INFO_H
