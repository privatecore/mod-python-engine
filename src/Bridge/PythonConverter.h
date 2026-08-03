#ifndef MOD_PYTHON_ENGINE_CONVERTER_H
#define MOD_PYTHON_ENGINE_CONVERTER_H

#include "PythonAPI.h"
#include "PythonMutable.h"
#include <functional>
#include <string>
#include <type_traits>
#include <utility>

namespace PyEng::Bridge
{
    /**
     * @brief Converts C++ types to Python objects
     */
    class Converter
    {
    public:
        /**
         * @brief Handles std::reference_wrapper - wraps mutable primitives/enums
         *
         * This overload method is triggered when std::ref() is explicitly used,
         * indicating the parameter should be mutable in Python.
         *
         * @tparam T The referenced type
         * @param ref The reference wrapper containing the reference
         * @return API::Object Python object
         */
        template<typename T>
        static API::Object ToPython(std::reference_wrapper<T> ref)
        {
            T& value = ref.get();

            if constexpr (std::is_arithmetic<T>::value && !std::is_const<T>::value)
            {
                return API::Object(Mutable<T>(value));
            }
            else if constexpr (std::is_enum<T>::value && !std::is_const<T>::value)
            {
                using UnderlyingType = std::underlying_type_t<T>;
                return API::Object(Mutable<UnderlyingType>(reinterpret_cast<UnderlyingType&>(value)));
            }

            return API::Object(std::forward<T&>(value));
        }

        /**
         * @brief Generic conversion that forwards values to Python
         *
         * This handles all types that are NOT wrapped in std::reference_wrapper.
         * Values and unmarked references are passed directly to Python w/o wrapping.
         *
         * @tparam T The value type
         * @param value The value to convert
         * @return API::Object Python object created from the forwarded value
         */
        template<typename T>
        static API::Object ToPython(T&& value)
        {
            return API::Object(std::forward<T>(value));
        }

        /**
         * @brief Converts pointers to Python, handling null pointers safely
         *
         * @tparam T The pointed-to type
         * @param ptr The pointer to convert (may be null)
         * @return API::Object Python object wrapping the pointer, or empty if null
         */
        template<typename T>
        static API::Object ToPython(T* ptr)
        {
            if (!ptr)
                return API::Object();

            return API::Object(API::Ptr(ptr));
        }

        /**
         * @brief Converts C-style string literal to Python string
         *
         * @param str C-style string literal
         * @return API::Object Python string object
         */
        static API::Object ToPython(char const* str) { return API::FromString(std::string(str)); }

        /**
         * @brief Converts std::string to Python string
         *
         * @param str std::string to convert
         * @return API::Object Python string object
         */
        static API::Object ToPython(std::string const& str) { return API::FromString(str); }

    private:
        Converter() = delete;
    };

} // namespace PyEng::Bridge

#endif // MOD_PYTHON_ENGINE_CONVERTER_H
