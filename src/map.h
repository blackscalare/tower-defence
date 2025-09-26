#pragma once
#include <raylib.h>
#include <vector>

class Map {
public:
	struct Tile {
		float width;
		float height;
		Vector2 pos;
		bool filled;
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

	void Reload();
	std::vector<Tile> GetWalkableTiles() {return walkableTiles;}
	std::vector<Vector2> GetWaypoints() {return waypoints;}

private:
	void Init();
	void InitWalkableTiles();
	void InitWalls();
	void GenerateWaypoints(const std::vector<Vector2>& path);

	void CenterPointInTile(Vector2& v);

	std::vector<Tile> walls;
	std::vector<Tile> walkableTiles;
	std::vector<Vector2> waypoints;

	Tile CreateTile(Vector2 pos);
};


