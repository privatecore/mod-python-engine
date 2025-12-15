#ifndef MOD_PYTHON_ENGINE_EXCEPTION_H
#define MOD_PYTHON_ENGINE_EXCEPTION_H

#include "PythonHeaders.h"

namespace PyEng::Bridge
{
    /**
     * @brief Utility class for extracting and formatting Python exceptions
     *
     * This class mimics Pythons' traceback module functionality, extracting full
     * traceback with file names, line numbers, and function names. All methods
     * require the Global Interpreter Lock (GIL) to be held!
     *
     * @see https://docs.python.org/3/c-api/exceptions.html
     * @see https://docs.python.org/3/library/traceback.html
     */
    class ExceptionHandler
    {
    public:
        /**
         * @brief Formats the current Python exception with full traceback
         *
         * Extracts exception information and formats it similar to Pythons'
         * traceback.format_exception(). The output includes:
         * - Exception type (ex., ValueError, TypeError)
         * - Exception message/value
         * - Complete traceback (file, line, function)
         *
         * @return Formatted string with traceback, or empty string if no exception
         */
        static std::string FormatException();

    private:
        ExceptionHandler() = delete;

        // Internal helpers
        static std::string FormatTraceback(PyObject* traceback);
        static std::string FormatExceptionOnly(PyObject* excType, PyObject* excValue);
        static std::string FormatFrame(PyObject* frame);
        static std::string ExtractTypeName(PyObject* excType);
        static std::string SafeStr(PyObject* obj);
    };

} // namespace PyEng::Bridge

#endif // MOD_PYTHON_ENGINE_EXCEPTION_H
