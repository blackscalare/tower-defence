#include "map.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

Map::Map() {
	Init();
}

Map::~Map() {
}

void Map::Init() {
	// InitWalkableTiles();
	// InitWalls();
	LoadMap();
}
void Map::LoadMap() {
	int bytesRead = 0;
	unsigned char* rawData = (LoadFileData("map.dat", &bytesRead));
	if(!rawData) return;

	int32_t* data = reinterpret_cast<int32_t*>(rawData);
	
	int tileCount = data[0];
	for(int i = 0; i < tileCount; ++i) {
		int32_t x = data[1 + i * 4 + 0];
		int32_t y = data[1 + i * 4 + 1];
		TileType type = static_cast<TileType>(data[1 + i * 4 + 2]);
		int32_t order = data[1 + i * 4 + 3];

		if(type == WALKABLE_TILE)
			walkableTiles.push_back(CreateTile({static_cast<float>(x), static_cast<float>(y)}, type, order));
		else if(type == TURRET_TILE)
			walls.push_back(CreateTilePtr({static_cast<float>(x), static_cast<float>(y)}, type, -1));
		
	}

	UnloadFileData(rawData);
	
	GenerateWaypoints();
}

void Map::InitWalls() {
}

void Map::GenerateWaypoints() {
	if(walkableTiles.empty()) return;
	
	std::sort(walkableTiles.begin(), walkableTiles.end(),
		   [] (const Tile& lhs, const Tile& rhs) -> bool {return lhs < rhs; });

	Vector2 firstPoint = walkableTiles.front().pos;
	Vector2 _firstPoint = GetV2CenterPoint(firstPoint);
	waypoints.push_back(_firstPoint);
	
	for(size_t i = 1; i < walkableTiles.size() - 1; ++i) {
		Vector2 prev = walkableTiles[i - 1].pos;
		Vector2 curr = walkableTiles[i].pos;
		Vector2 next = walkableTiles[i + 1].pos;

		// Direction vectors
		Vector2 dir1 = {curr.x - prev.x, curr.y - prev.y};
		Vector2 dir2 = {next.x - curr.x, next.y - prev.y};

		// Normalize direction
		if (dir1.x != 0) dir1.x /= std::abs(dir1.x);
        if (dir1.y != 0) dir1.y /= std::abs(dir1.y);
        if (dir2.x != 0) dir2.x /= std::abs(dir2.x);
        if (dir2.y != 0) dir2.y /= std::abs(dir2.y);

        // If direction changes, add current as a waypoint
        if (dir1.x != dir2.x || dir1.y != dir2.y) {
			Vector2 _curr = GetV2CenterPoint(curr);	
			waypoints.push_back(_curr);
        }
	}

	Vector2 lastPoint = walkableTiles.back().pos;
	Vector2 _lastPoint = GetV2CenterPoint(lastPoint);
	waypoints.push_back(_lastPoint);
}

void Map::CenterPointInTile(Vector2& v) {
	v.x += 30/2;
	v.y += 30/2;
}

Vector2 Map::GetV2CenterPoint(const Vector2& v) {
	float x = v.x + 30/2;
	float y = v.y + 30/2;
	return {x, y};
}

Map::Tile Map::CreateTile(Vector2 pos, TileType type, int order) {
	return Tile(30.0f, 30.0f, pos, type, order);
}

Map::Tile* Map::CreateTilePtr(Vector2 pos, TileType type, int order) {
	return new Tile(30.0f, 30.0f, pos, type, order);
}
