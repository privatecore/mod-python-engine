#ifndef MOD_PYTHON_ENGINE_CONVERTER_H
#define MOD_PYTHON_ENGINE_CONVERTER_H

#include "PythonAPI.h"
#include <string>
#include <utility>

namespace PyEng::Bridge
{
    /**
     * @brief Converts C++ types to Python objects
     */
    class Converter
    {
    public:
        // Generic value conversion
        template<typename T>
        static API::Object ToPython(T&& value)
        {
            return API::Object(std::forward<T>(value));
        }

        // Pointer conversion
        template<typename T>
        static API::Object ToPython(T* ptr)
        {
            if (!ptr)
                return API::Object();
            return API::Object(API::Ptr(ptr));
        }

        // String conversions
        static API::Object ToPython(const char* str) { return API::FromString(std::string(str)); }
        static API::Object ToPython(const std::string& str) { return API::FromString(str); }

    private:
        Converter() = delete;
    };

} // namespace PyEng::Bridge

#endif // MOD_PYTHON_ENGINE_CONVERTER_H
