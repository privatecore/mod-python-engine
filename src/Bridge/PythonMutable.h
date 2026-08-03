#ifndef MOD_PYTHON_ENGINE_MUTABLE_H
#define MOD_PYTHON_ENGINE_MUTABLE_H

#include "Define.h"
#include <string>

namespace PyEng::Bridge
{
    /**
     * @brief Wrapper for mutable primitive references
     *
     * Wraps references to primitives (int, float, etc.) so they can be passed
     * through Boost.Python and modified from Python scripts.
     */
    template<typename T>
    class Mutable
    {
    public:
        explicit Mutable(T& ref) : m_ref(ref) {}

        Mutable(Mutable const&) = default;
        Mutable& operator=(Mutable const&) = delete;

        /**
         * @brief Get current value of the referenced variable
         */
        T get() const { return m_ref; }

        /**
         * @brief Set new value to the referenced variable
         */
        void set(T value) { m_ref = value; }

        /**
         * @brief Implicit conversion for convenience
         */
        operator T() const { return m_ref; }

        /**
         * @brief String representation for Python __repr__
         */
        std::string repr() const { return "<Mutable: " + std::to_string(static_cast<int64>(m_ref)) + ">"; }

    private:
        T& m_ref;
    };

    // Type aliases for common primitives
    using Int8Ref = Mutable<int8>;
    using Int16Ref = Mutable<int16>;
    using Int32Ref = Mutable<int32>;
    using Int64Ref = Mutable<int64>;
    using UInt8Ref = Mutable<uint8>;
    using UInt16Ref = Mutable<uint16>;
    using UInt32Ref = Mutable<uint32>;
    using UInt64Ref = Mutable<uint64>;
    using FloatRef = Mutable<float>;
    using DoubleRef = Mutable<double>;
    using BoolRef = Mutable<bool>;

} // namespace PyEng::Bridge

#endif // MOD_PYTHON_ENGINE_MUTABLE_H
