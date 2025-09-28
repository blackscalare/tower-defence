#include "renderer.h"
#include "logic.h"
#include <cstdio>
#include <cstdlib>
#include <raylib.h>
Renderer::Renderer(Map* map, Logic* logic) {
	this->map = map;
	this->logic = logic;
}

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::Update() {
	for(const Map::Tile& tile : map->GetWalkableTiles()) {
		DrawRectangleLines(tile.pos.x, tile.pos.y, tile.width, tile.height, BROWN);
	}

	// for(int i = 0; i < map->GetWaypoints().size(); ++i) {
	// 	char* c = (char*)malloc(8 * sizeof(char));
	// 	snprintf(c, 8, "%d", i);
	// 	DrawText(c, map->GetWaypoints()[i].x, map->GetWaypoints()[i].y, 10, RED);
	// }
	//
	// for(const Vector2& v : map->GetWaypoints()) {
	// 	DrawCircle(v.x, v.y, 5, RED);
	// }
	//
	for(Enemy* enemy : logic->GetEnemies()) {
		Vector2 pos = enemy->GetPosition();
		DrawCircle(pos.x, pos.y, 5, RED);
	}
}
