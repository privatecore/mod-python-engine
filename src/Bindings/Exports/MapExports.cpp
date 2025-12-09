#include "PythonHeaders.h"
#include "Map.h"
#include "Player.h"
#include "Creature.h"
#include "GameObject.h"

namespace bp = boost::python;

/**
 * @brief Map Class - Represents a game map (world, dungeon, battleground, etc.)
 */
void export_map_class()
{
    bp::class_<Map, boost::noncopyable> map_class("Map", bp::no_init);

    // common
    map_class.def("GetId", &Map::GetId);
    map_class.def("GetMapName", &Map::GetMapName);

    // type checks
    map_class.def("Instanceable", &Map::Instanceable);
    map_class.def("IsDungeon", &Map::IsDungeon);
    map_class.def("IsNonRaidDungeon", &Map::IsNonRaidDungeon);
    map_class.def("IsRaid", &Map::IsRaid);
    map_class.def("IsRaidOrHeroicDungeon", &Map::IsRaidOrHeroicDungeon);
    map_class.def("IsHeroic", &Map::IsHeroic);
    map_class.def("Is25ManRaid", &Map::Is25ManRaid);
    map_class.def("IsBattleground", &Map::IsBattleground);
    map_class.def("IsBattleArena", &Map::IsBattleArena);
    map_class.def("IsBattlegroundOrArena", &Map::IsBattlegroundOrArena);
    map_class.def("IsWorldMap", &Map::IsWorldMap);

    // entity
    map_class.def("GetCreature", &Map::GetCreature, bp::return_value_policy<bp::reference_existing_object>());
    map_class.def("GetGameObject", &Map::GetGameObject, bp::return_value_policy<bp::reference_existing_object>());

    // location
    map_class.def("GetHeight", static_cast<float (Map::*)(float, float, float, bool, float) const>(&Map::GetHeight));
    map_class.def("GetAreaId", &Map::GetAreaId);
    map_class.def("GetZoneId", &Map::GetZoneId);
}
