#include "map.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "../constants.h"

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
	std::vector<Vector2> path;
	int bytesRead = 0;
	unsigned char* rawData = (LoadFileData("map.dat", &bytesRead));
	if(!rawData) return;

	int32_t* data = reinterpret_cast<int32_t*>(rawData);
	
	int tileCount = data[0];
	for(int i = 0; i < tileCount; ++i) {
		int32_t x = data[1 + i * 4 + 0];
		int32_t y = data[1 + i * 4 + 1];
		TileType type = static_cast<TileType>(data[1 + i * 4 + 2]);
		// TODO: Needs to use waypoint index that is saved
		if(type == WALKABLE_TILE)
			path.push_back({static_cast<float>(x), static_cast<float>(y)});
		else if(type == TURRET_TILE)
			walls.push_back(CreateTile({static_cast<float>(x), static_cast<float>(y)}));
			
	}

	UnloadFileData(rawData);

	// Build walkable tiles
    for (auto& p : path) {
        walkableTiles.push_back(CreateTile(p));
    }
	GenerateWaypoints(path);
}

void Map::Reload() {
	walkableTiles.clear();
	walls.clear();
	InitWalkableTiles();
}

void Map::InitWalkableTiles() {
    const int tileSize = 30;
    const int margin = 100;

    const int gridWidth  = (Constants::Window::WIDTH  - 2 * margin) / tileSize;
    const int gridHeight = (Constants::Window::HEIGHT - 2 * margin) / tileSize;

    std::vector<std::vector<int>> grid(gridHeight, std::vector<int>(gridWidth, 0));
    std::vector<Vector2> path;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Start on the left side
    int startY = std::rand() % gridHeight;
    Vector2Int current = {0, startY};
    grid[current.y][current.x] = 1;
    path.push_back({static_cast<float>(current.x * tileSize + margin), static_cast<float>(current.y * tileSize + margin)});

    int maxSteps = gridWidth * 2; // failsafe

    while (current.x < gridWidth - 1 && maxSteps-- > 0) {
        std::vector<Vector2Int> candidates;

        // Weighted direction options
        // Right x4, Up x1, Down x1
        std::vector<Vector2Int> directions = {
            {1, 0}, {1, 0}, {1, 0}, {1, 0}, // More chance to move right
            {0, -1}, {0, 1} // Sometimes move up/down
            // Optional: {-1, 0} // rarely move left (if allowed)
        };

        std::random_shuffle(directions.begin(), directions.end());

        for (auto& dir : directions) {
            Vector2Int next = {current.x + dir.x, current.y + dir.y};

            if (next.x >= 0 && next.x < gridWidth &&
                next.y >= 0 && next.y < gridHeight &&
                grid[next.y][next.x] == 0) {
                current = next;
                grid[current.y][current.x] = 1;
                path.push_back({static_cast<float>(current.x * tileSize + margin), static_cast<float>(current.y * tileSize + margin)});
                break;
            }
        }
    }

    // Build walkable tiles
    for (auto& p : path) {
        walkableTiles.push_back(CreateTile(p));
    }

	GenerateWaypoints(path);
	InitWalls();
}

void Map::InitWalls() {
}

void Map::GenerateWaypoints(const std::vector<Vector2>& path) {
	if(path.empty()) return;

	for(auto p : path) {
		CenterPointInTile(p);
		waypoints.push_back(p);
	}
	
	return;

	Vector2 firstPoint = path.front();
	CenterPointInTile(firstPoint);
	waypoints.push_back(firstPoint);
	
	for(size_t i = 1; i < path.size() - 1; ++i) {
		Vector2 prev = path[i - 1];
		Vector2 curr = path[i];
		Vector2 next = path[i + 1];

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
            CenterPointInTile(curr);
			waypoints.push_back(curr);
        }
	}

	Vector2 lastPoint = path.back();
	CenterPointInTile(lastPoint);
	waypoints.push_back(lastPoint);
}

void Map::CenterPointInTile(Vector2& v) {
	v.x += 30/2;
	v.y += 30/2;
}


Map::Tile Map::CreateTile(Vector2 pos) {
	return {30, 30, pos, false};
}
