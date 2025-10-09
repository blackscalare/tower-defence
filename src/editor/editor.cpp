#include "editor.h"
#include "../constants.h"
#include <cstdint>
#include <cstdio>
#include <raylib.h>

Editor ::Editor () {
}

Editor ::~Editor () {
}

void Editor::Update() {
	for(int y = 0; y < Constants::Window::HEIGHT; y += 30) {
		for(int x = 0; x < Constants::Window::WIDTH; x += 30) {
			bool isColliding = CheckCollisionPointRec(GetMousePosition(), {static_cast<float>(x), static_cast<float>(y), 30, 30});
			HandleDrawingRectangles(x, y, isColliding);
			HandleInput(x, y, isColliding);
		}
	}
}

void Editor::HandleDrawingRectangles(int x, int y, bool isColliding) {
	auto key = std::make_pair(x, y);
	
	auto it = placedTiles.find(key);
	if(it != placedTiles.end()) {
		Color tileColor = WHITE;

		switch(it->second.type) {
			case WALKABLE_TILE:
				tileColor = BROWN;
				break;
			case TURRET_TILE:
				tileColor = GREEN;
				break;
		}

		DrawRectangle(x, y, 30, 30, tileColor);
		DrawText(TextFormat("%d", it->second.order), x + 30/2, y + 30/2, 24, WHITE);
	}
	else if(isColliding) {
		Color tileColor = WHITE;
		switch(currentSelection) {
			case WALKABLE_TILE:
				tileColor = BROWN;
				break;
			case TURRET_TILE:
				tileColor = GREEN;
				break;
		}
		DrawRectangle(x, y, 30, 30, tileColor);
		if(currentSelection == WALKABLE_TILE) {
			DrawText(TextFormat("%d", currentWaypointIndex), x + 30/2, y + 30/2, 24, WHITE);
		}
	} else {
		DrawRectangleLines(x, y, 30, 30, WHITE);
	}
}

void Editor::HandleInput(int x, int y, bool isColliding) {
	if(IsKeyPressed(KEY_ONE)) {
		currentSelection = WALKABLE_TILE;
	}

	if(IsKeyPressed(KEY_TWO)) {
		currentSelection = TURRET_TILE;
	}

	if(IsKeyPressed(KEY_THREE)) {
		currentSelection = WAYPOINT;
	}

	bool tileFree = TileIsFree(x, y);

	// Add square
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isColliding && tileFree) {
		// Do not place a square if it already exists
		if(placedTiles.find({x, y}) != placedTiles.end()) return;

		if(currentSelection == WALKABLE_TILE)
			placedTiles[{x, y}] = {currentSelection, currentWaypointIndex++};
		else
			placedTiles[{x, y}] = {currentSelection, -1};
		dirty = true;
		justLoadedMap = false;
	}

	// Remove square
	if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && isColliding && !tileFree) {
		// Do not continue if nothing is removed
		if(placedTiles.erase({x, y}) == 0) return;
		
		currentWaypointIndex--;
		dirty = true;
		justLoadedMap = false;
	}

	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
		SaveMap();
	}

	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_L)) {
		LoadMap();
	}

	if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Z)) {
	}
}

bool Editor::TileIsFree(int x, int y) {
	return placedTiles.find(std::make_pair(x, y)) == placedTiles.end();
}

void Editor::SaveMap() {
	if(!dirty) return;
	std::vector<int32_t> data;
	data.reserve(1 + placedTiles.size() * 4);
	data.push_back(static_cast<int32_t>(placedTiles.size()));

	for(const auto& [pos, tile] : placedTiles) {
		data.push_back(static_cast<int32_t>(pos.first));
		data.push_back(static_cast<int32_t>(pos.second));
		data.push_back(static_cast<int32_t>(tile.type));
		data.push_back(static_cast<int32_t>(tile.order));
	}

	SaveFileData("map.dat", data.data(), data.size() * sizeof(int32_t));
	dirty = false;
}

void Editor::LoadMap() {
	if(justLoadedMap) return;

	int bytesRead = 0;
	unsigned char* rawData = (LoadFileData("map.dat", &bytesRead));
	if(!rawData) return;

	int32_t* data = reinterpret_cast<int32_t*>(rawData);

	placedTiles.clear();
	
	int tileCount = data[0];
	for(int i = 0; i < tileCount; ++i) {
		int32_t x = data[1 + i * 4 + 0];
		int32_t y = data[1 + i * 4 + 1];
		Selection type = static_cast<Selection>(data[1 + i * 4 + 2]);
		int32_t order = data[1 + i * 4 + 3];

		placedTiles[{x, y}] = Tile{type, order};
	}

	UnloadFileData(rawData);
	currentWaypointIndex = placedTiles.size();
	justLoadedMap = true;
}
