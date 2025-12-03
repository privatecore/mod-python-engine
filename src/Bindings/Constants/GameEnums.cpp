#include "PythonHeaders.h"
#include "SharedDefines.h"

namespace bp = boost::python;

/**
 * @brief Export game enums to Python
 */
void export_game_constants()
{
    // enum Gender
    bp::enum_<Gender>("Gender")
        .value("Male",          GENDER_MALE)        // 0
        .value("Female",        GENDER_FEMALE)      // 1
        .export_values();

    // enum Races (ChrRaces.dbc)
    bp::enum_<Races>("Race")
        .value("Human",         RACE_HUMAN)          // 1
        .value("Orc",           RACE_ORC)            // 2
        .value("Dwarf",         RACE_DWARF)          // 3
        .value("Nightelf",      RACE_NIGHTELF)       // 4
        .value("Undead",        RACE_UNDEAD_PLAYER)  // 5
        .value("Tauren",        RACE_TAUREN)         // 6
        .value("Gnome",         RACE_GNOME)          // 7
        .value("Troll",         RACE_TROLL)          // 8
        .value("Bloodelf",      RACE_BLOODELF)       // 10
        .value("Draenei",       RACE_DRAENEI)        // 11
        .export_values();

    // enum Classes (ChrClasses.dbc)
    bp::enum_<Classes>("Class")
        .value("Warrior",       CLASS_WARRIOR)      // 1
        .value("Paladin",       CLASS_PALADIN)      // 2
        .value("Hunter",        CLASS_HUNTER)       // 3
        .value("Rogue",         CLASS_ROGUE)        // 4
        .value("Priest",        CLASS_PRIEST)       // 5
        .value("DeathKnight",   CLASS_DEATH_KNIGHT) // 6
        .value("Shaman",        CLASS_SHAMAN)       // 7
        .value("Mage",          CLASS_MAGE)         // 8
        .value("Warlock",       CLASS_WARLOCK)      // 9
        .value("Druid",         CLASS_DRUID)        // 11
        .export_values();

    // enum Stats
    bp::enum_<Stats>("Stat")
        .value("Strength",      STAT_STRENGTH)      // 0
        .value("Agility",       STAT_AGILITY)       // 1
        .value("Stamina",       STAT_STAMINA)       // 2
        .value("Intellect",     STAT_INTELLECT)     // 3
        .value("Spirit",        STAT_SPIRIT)        // 4
        .export_values();

    // enum Powers
    bp::enum_<Powers>("Power")
        .value("Mana",          POWER_MANA)         // 0
        .value("Rage",          POWER_RAGE)         // 1
        .value("Focus",         POWER_FOCUS)        // 2
        .value("Energy",        POWER_ENERGY)       // 3
        .value("Happiness",     POWER_HAPPINESS)    // 4
        .value("Rune",          POWER_RUNE)         // 5
        .value("RunicPower",    POWER_RUNIC_POWER)  // 6
        .export_values();
}
