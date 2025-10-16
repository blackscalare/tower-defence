#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "../towers/tower.h"
#include "../constants.h"

class Map {
public:
	enum TileType {
		WALKABLE_TILE,
		TURRET_TILE,
		WAYPOINT
	};

	enum ProjectileType {
	    ARROW,
		BOMB
	};

	struct Tile {
		float width;
		float height;
		Vector2 pos;
		TileType type;
		int order;
		bool has_placement;
		Tower* tower;

		Tile(float width, float height, Vector2 pos, TileType type, int order)
			: width(width), height(height), pos(pos), type(type), order(order), has_placement(false), tower(nullptr) {}

		Tile(float width, float height, Vector2 pos, TileType type, int order, bool has_placement, Tower* tower)
			: width(width), height(height), pos(pos), type(type), order(order), has_placement(has_placement), tower(tower) {}

		bool operator<(const Tile& rhs) const { return order < rhs.order; }
		bool operator<=(const Tile& rhs) const { return order <= rhs.order; }
		bool operator>(const Tile& rhs) const { return order > rhs.order; }
	};

	struct Projectile {
		Vector2 pos;
		Vector2 goal;
		float speed;
		int damage;
		ProjectileType type;

		Projectile(Vector2 pos, Vector2 goal, float speed, int damage, ProjectileType type)
			: pos(pos), goal(goal), speed(speed), damage(damage), type(type) {}

		void Update(float deltaTime) {
			pos = Vector2MoveTowards(pos, goal, speed);
		}

		ProjectileType TowerTypeToProjectileType(Tower::TowerType towerType) {
		    switch(towerType) {
				case Tower::TURRET:
				case Tower::SNIPER:
				    return ProjectileType::ARROW;
				case Tower::BOMBER:
				    return ProjectileType::BOMB;
				default:
				    TraceLog(LOG_ERROR, "%s Tower type %d", __PRETTY_FUNCTION__, towerType);
			}
		}
	};

	struct Waypoint {
		Vector2 pos;
		int index;
	};

	Map();
	Map(Map &&) = default;
	Map(const Map &) = default;
	Map &operator=(Map &&) = default;
	Map &operator=(const Map &) = default;
	~Map();

	std::vector<Tile> GetWalkableTiles() { return walkableTiles; }
	std::vector<Waypoint> GetWaypoints() { return waypoints; }
	std::vector<Tile*> GetWallTiles() { return walls; }
	std::vector<UPTR<Projectile>>& GetProjectiles() { return projectiles; }

	void CreateProjectile(Tile* tile, Vector2 enemyPos, float speed, float damage, Tower::TowerType towerType);

private:
	void Init();
	void LoadMap();
	void InitWalkableTiles();
	void InitWalls();
	void GenerateWaypoints();
	void CenterPointInTile(Vector2& v);
	Vector2 GetV2CenterPoint(const Vector2& v);


	std::vector<Tile*> walls;
	std::vector<Tile> walkableTiles;
	std::vector<Waypoint> waypoints;
	std::vector<UPTR<Projectile>> projectiles;

	Tile CreateTile(Vector2 pos, TileType type, int order);
	Tile* CreateTilePtr(Vector2 pos, TileType type, int order);
};
