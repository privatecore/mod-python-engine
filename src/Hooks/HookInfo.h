#ifndef MOD_PYTHON_ENGINE_HOOK_INFO_H
#define MOD_PYTHON_ENGINE_HOOK_INFO_H

#include "Define.h"
#include <cstdint>
#include <functional>

namespace PyEng::Hooks
{
    /**
     * @brief Hook Type Categories
     */
    enum class Category : uint8
    {
        ACCOUNT,
        PLAYER,
        CREATURE,
        GAMEOBJECT,
        ITEM,
        ACHIEVEMENT,
        SERVER,
        UNIT,
        WORLD,
    };

    /**
     * @brief Type-safe hook identifier
     */
    struct HookInfo
    {
        Category category;
        uint8 value;

        constexpr bool operator==(HookInfo const& other) const noexcept
        {
            return category == other.category && value == other.value;
        }
        constexpr bool operator!=(HookInfo const& other) const noexcept
        {
            return !(*this == other);
        }
    };

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
