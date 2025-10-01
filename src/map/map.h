#pragma once
#include <raylib.h>
#include <vector>

class Map {
public:
	enum TileType {
		WALKABLE_TILE,
		TURRET_TILE,
		WAYPOINT
	};

	struct Tile {
		float width;
		float height;
		Vector2 pos;
		TileType type;
		int order;
		bool has_placement;
		
		Tile(float width, float height, Vector2 pos, TileType type, int order) 
			: width(width), height(height), pos(pos), type(type), order(order), has_placement(false){}
		Tile(float width, float height, Vector2 pos, TileType type, int order, bool has_placement)
			: width(width), height(height), pos(pos), type(type), order(order), has_placement(has_placement){}

		bool operator<(const Tile& rhs) const { return order < rhs.order; }
		bool operator<=(const Tile& rhs) const { return order <= rhs.order; }
		bool operator>(const Tile& rhs) const { return order > rhs.order; }
	};

	struct Vector2Int {
		int x, y;
	};

	Map();
	Map(Map &&) = default;
	Map(const Map &) = default;
	Map &operator=(Map &&) = default;
	Map &operator=(const Map &) = default;
	~Map();

	std::vector<Tile> GetWalkableTiles() {return walkableTiles;}
	std::vector<Vector2> GetWaypoints() {return waypoints;}
	std::vector<Tile*> GetWallTiles() { return walls; }

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
	std::vector<Vector2> waypoints;

	Tile CreateTile(Vector2 pos, TileType type, int order);
	Tile* CreateTilePtr(Vector2 pos, TileType type, int order);
};


