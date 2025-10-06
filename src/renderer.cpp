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
	for(auto tile : map->GetWallTiles()) {
		DrawRectangleLines(tile->pos.x, tile->pos.y, tile->width, tile->height, GREEN);
		if(tile->has_placement) {
			DrawCircle(tile->pos.x + 30/2, tile->pos.y + 30/2, 10, WHITE);
		}
	}

	// for(int i = 0; i < map->GetWaypoints().size(); ++i) {
	// 	char* c = (char*)malloc(8 * sizeof(char));
	// 	snprintf(c, 8, "%d", i);
	// 	DrawText(c, map->GetWaypoints()[i].x, map->GetWaypoints()[i].y, 10, RED);
	// 	free(c);
	// }
	
	for(const Vector2& v : map->GetWaypoints()) {
		DrawCircle(v.x, v.y, 5, RED);
	}

	for(SPTR<Enemy>& enemy : logic->GetEnemies()) {
		Vector2 pos = enemy->GetPosition();
		DrawCircle(pos.x, pos.y, 5, RED);
	}

	for(auto& projectile : map->GetProjectiles()) {
		DrawCircle(projectile->pos.x, projectile->pos.y, 2, YELLOW);
	}

	const char* goldText = TextFormat("Gold: %ld", logic->GetGold());
	DrawText(goldText, Constants::Window::WIDTH - MeasureText(goldText, 24) - 30, 50, 24, GOLD);

	const char* healthText = TextFormat("HP: %ld", logic->GetHealth());
	DrawText(healthText, Constants::Window::WIDTH - MeasureText(goldText, 24) - 30 - 100 - MeasureText(healthText, 24), 50, 24, RED);
	
	const char* timeText = TextFormat("Time: %0.1f", GetTime());
	DrawText(timeText, Constants::Window::WIDTH / 2 - MeasureText(timeText, 24), 50, 24, WHITE);

	DrawText(TextFormat("Wave: %d", logic->GetWaveNumber()), 10, 10, 20, WHITE);
}
