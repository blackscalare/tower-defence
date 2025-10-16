#pragma once
#include "../map/map.h"
#include "../towers/tower.h"
#include <raylib.h>

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

static inline const char* ProjectileTypeToString(Map::ProjectileType projectileType) {
    switch(projectileType) {
        case Map::ProjectileType::ARROW: return "Arrow";
        case Map::ProjectileType::BOMB: return "Bomb";
    }
}

static inline const char* TowerTypeToString(Tower::TowerType towerType) {
    switch(towerType) {
        case Tower::TURRET: return "Turret";
        case Tower::SNIPER: return "Sniper";
        case Tower::BOMBER: return "BOMBER";
        default:
            TraceLog(LOG_ERROR, "%s: TowerType %d does not exist",__PRETTY_FUNCTION__, towerType);
    }
}
