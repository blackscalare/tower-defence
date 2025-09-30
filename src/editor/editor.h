#pragma once
#include <map>
#include <raylib.h>
#include <unordered_map>
#include <vector>

class Editor {
public:
	enum Selection {
		WALKABLE_TILE,
		TURRET_TILE,
		WAYPOINT
	};

	struct Tile {
		Selection type;
		int order;
	};

	Editor ();
	Editor (Editor  &&) = default;
	Editor (const Editor  &) = default;
	Editor  &operator=(Editor  &&) = default;
	Editor  &operator=(const Editor  &) = default;
	~Editor ();
	void Update();
private:
	void HandleDrawingRectangles(int x, int y, bool isColliding);
	void HandleInput(int x, int y, bool isColliding);
	bool TileIsFree(int x, int y);
	void SaveMap();
	void LoadMap();

	Selection currentSelection = WALKABLE_TILE;
	std::map<std::pair<int, int>, Tile> placedTiles;
	// TODO: switch to optimzed placedTiles
	std::unordered_map<int, std::unordered_map<int, Tile>> optimized_placedTiles;
	// TODO: Investigate TileType tileGrid[ROWS][COLS]
	
	int currentWaypointIndex = 0;
	bool dirty = false;
	bool justLoadedMap = false;
};
