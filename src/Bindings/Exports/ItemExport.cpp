#include "PythonHeaders.h"
#include "ItemAdapter.h"

namespace bp = boost::python;

/**
 * @brief ItemTemplate struct - Contains static item database data
 */
void export_item_template_struct()
{
    bp::class_<ItemTemplate> item_template_struct("ItemTemplate", bp::no_init);

    // data value
    item_template_struct.def_readonly("Id", &ItemTemplate::ItemId);
    item_template_struct.def_readonly("Class", &ItemTemplate::Class);
    item_template_struct.def_readonly("SubClass", &ItemTemplate::SubClass);
    item_template_struct.def_readonly("Name", &ItemTemplate::Name1);
    item_template_struct.def_readonly("Quality", &ItemTemplate::Quality);
    item_template_struct.def_readonly("BuyCount", &ItemTemplate::BuyCount);
    item_template_struct.def_readonly("BuyPrice", &ItemTemplate::BuyPrice);
    item_template_struct.def_readonly("SellPrice", &ItemTemplate::SellPrice);
    item_template_struct.def_readonly("InventoryType", &ItemTemplate::InventoryType);
    item_template_struct.def_readonly("AllowableClass", &ItemTemplate::AllowableClass);
    item_template_struct.def_readonly("AllowableRace", &ItemTemplate::AllowableRace);
    item_template_struct.def_readonly("ItemLevel", &ItemTemplate::ItemLevel);
    item_template_struct.def_readonly("MaxCount", &ItemTemplate::MaxCount);
    item_template_struct.def_readonly("Stackable", &ItemTemplate::Stackable);
}

/**
 * @brief Item Class - Represents game items (armor, weapons, consumables, etc.)
 */
void export_item_class()
{
    bp::class_<Item, boost::noncopyable> item_class("Item", bp::no_init);

    // data ref
    item_class.def("GetTemplate", &Item::GetTemplate, bp::return_internal_reference<>());

    // common
    item_class.def("GetEntry", &Item::GetEntry);
    item_class.def("GetCount", &Item::GetCount);
    item_class.def("GetSlot", &Item::GetSlot);
    item_class.def("GetBagSlot", &Item::GetBagSlot);
}
