#include "PythonHeaders.h"
#include "ItemAdapter.h"

namespace bp = boost::python;

/**
 * @brief Item Class - Represents game items (armor, weapons, consumables, etc.)
 */
void export_item_class()
{
    bp::class_<Item, boost::noncopyable>("Item", bp::no_init)
        .def("GetEntry", &Item::GetEntry);
}
