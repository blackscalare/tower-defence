#include "renderer.h"
#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include <stdio.h>
Renderer::Renderer(Map* map) {
	this->map = map;
}

void Renderer::Update() {
	for(const Map::Tile& tile : map->GetWalkableTiles()) {
		DrawRectangleLines(tile.pos.x, tile.pos.y, tile.width, tile.height, BROWN);
	}

	for(int i = 0; i < map->GetWaypoints().size(); ++i) {
		char* c = (char*)malloc(8 * sizeof(char));
		snprintf(c, 8, "%d", i);
		DrawText(c, map->GetWaypoints()[i].x, map->GetWaypoints()[i].y, 10, RED);
	}

	for(const Vector2& v : map->GetWaypoints()) {
		DrawCircle(v.x, v.y, 5, RED);
	}
}
