#pragma once
#include "../map/map.h"

static inline const char* TileMapToString(Map::TileType tileType) {
    switch (tileType) {
        case Map::TURRET_TILE:
            return "TURRET_TILE";
        case Map::WALKABLE_TILE:
            return "WALKABLE_TILE";
        case Map::WAYPOINT:
            return "WAYPOINT";
        default:
            return "NON_EXISTANT";
    }
}
