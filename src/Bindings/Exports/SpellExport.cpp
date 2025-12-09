#include "PythonHeaders.h"
#include "SpellInfo.h"
#include "Spell.h"
#include "Corpse.h"
#include "Item.h"

namespace bp = boost::python;

/**
 * @brief SpellInfo Class - Contains static spell database information
 */
void export_spellinfo_class()
{
    bp::class_<SpellInfo> spellinfo_class("SpellInfo", bp::no_init);

    // data value
    spellinfo_class.def_readonly("Id", &SpellInfo::Id);
    spellinfo_class.def_readonly("SpellName", &SpellInfo::SpellName);
    spellinfo_class.def_readonly("Rank", &SpellInfo::Rank);
    spellinfo_class.def_readonly("SchoolMask", &SpellInfo::SchoolMask);
    spellinfo_class.def_readonly("DmgClass", &SpellInfo::DmgClass);
    spellinfo_class.def_readonly("Dispel", &SpellInfo::Dispel);
    spellinfo_class.def_readonly("Mechanic", &SpellInfo::Mechanic);
    spellinfo_class.def_readonly("ManaCost", &SpellInfo::ManaCost);
    spellinfo_class.def_readonly("ManaCostPercentage", &SpellInfo::ManaCostPercentage);
    spellinfo_class.def_readonly("PowerType", &SpellInfo::PowerType);
    spellinfo_class.def_readonly("RecoveryTime", &SpellInfo::RecoveryTime);
    spellinfo_class.def_readonly("CategoryRecoveryTime", &SpellInfo::CategoryRecoveryTime);
    spellinfo_class.def_readonly("StackAmount", &SpellInfo::StackAmount);

    // type checks
    spellinfo_class.def("IsPassive", &SpellInfo::IsPassive);
    spellinfo_class.def("IsChanneled", &SpellInfo::IsChanneled);
    spellinfo_class.def("IsPositive", &SpellInfo::IsPositive);

    // helpers
    spellinfo_class.def("GetDuration", &SpellInfo::GetDuration);
    spellinfo_class.def("GetMaxRange", &SpellInfo::GetMaxRange);
    spellinfo_class.def("CalcCastTime", &SpellInfo::CalcCastTime);
}

/**
 * @brief SpellCastTargets Class - Represents targeting information for spell casts
 */
void export_spellcast_targets_class()
{
    bp::class_<SpellCastTargets> spellcast_targets_class("SpellCastTargets", bp::no_init);

    // target ref
    spellcast_targets_class.def("GetUnitTarget", &SpellCastTargets::GetUnitTarget,
                                bp::return_value_policy<bp::reference_existing_object>());
    spellcast_targets_class.def("GetObjectTarget", &SpellCastTargets::GetObjectTarget,
                                bp::return_value_policy<bp::reference_existing_object>());
    spellcast_targets_class.def("GetCorpseTarget", &SpellCastTargets::GetCorpseTarget,
                                bp::return_value_policy<bp::reference_existing_object>());
    spellcast_targets_class.def("GetItemTarget", &SpellCastTargets::GetItemTarget,
                                bp::return_value_policy<bp::reference_existing_object>());

    // target guid
    spellcast_targets_class.def("GetUnitTargetGUID", &SpellCastTargets::GetUnitTargetGUID);
    spellcast_targets_class.def("GetObjectTargetGUID", &SpellCastTargets::GetObjectTargetGUID);
    spellcast_targets_class.def("GetCorpseTargetGUID", &SpellCastTargets::GetCorpseTargetGUID);
    spellcast_targets_class.def("GetItemTargetGUID", &SpellCastTargets::GetItemTargetGUID);
}
