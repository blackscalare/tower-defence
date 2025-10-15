#include "renderer.h"
#include "logic.h"
#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include <raymath.h>
#include "utils/enum_utils.hpp"

Renderer::Renderer(Map* map, Logic* logic) {
	this->map = map;
	this->logic = logic;
	Image arrowImage = LoadImage("assets/turret/arrow.png");
	Image skeletonImage = LoadImage("assets/enemies/skeleton/skeleton.bmp");

	if(arrowImage.data == nullptr) {
		TraceLog(LOG_ERROR, "Failed to load arrow image");
	}
	if(skeletonImage.data == nullptr) {
		TraceLog(LOG_ERROR, "Failed to load skeleton image");
	}

	ImageResize(&arrowImage, 16, 8);

	textures.insert(std::pair(ARROW, LoadTextureFromImage(arrowImage)));
	textures.insert(std::pair(SKELETON, LoadTextureFromImage(skeletonImage)));

	for(const auto& texture : textures) {
		if(texture.second.id == 0) {
			TraceLog(LOG_ERROR, "Failed to load %s", TextureNameToString(texture.first));
		}
	}

	UnloadImage(arrowImage);
	UnloadImage(skeletonImage);
}

void Renderer::Update() {
	DrawTiles();
	DrawGameObjects();
	DrawGui();
	DrawDebug();
}

void Renderer::DrawTiles() {
	for(const Map::Tile& tile : map->GetWalkableTiles()) {
		DrawRectangleLines(tile.pos.x, tile.pos.y, tile.width, tile.height, BROWN);
		DrawText(TextFormat("%d", tile.order), tile.pos.x + 30.0/2, tile.pos.y + 30.0/2, 4, WHITE);
	}
	for(auto tile : map->GetWallTiles()) {
		DrawRectangleLines(tile->pos.x, tile->pos.y, tile->width, tile->height, GREEN);
		if(tile->has_placement) {
			DrawCircle(tile->pos.x + 30.0/2, tile->pos.y + 30.0/2, 10, WHITE);
		}
	}
}

void Renderer::DrawGameObjects() {
	for(SPTR<Enemy>& enemy : logic->GetEnemies()) {
		Vector2 pos = enemy->GetPosition();
		DrawCircle(pos.x, pos.y, 5, RED);
		DrawTexturePro(textures.at(SKELETON), {0, 0, 32, 32}, {32, 0, 32, 32}, pos, 0, WHITE);
	}

	for(auto& projectile : map->GetProjectiles()) {
		switch(projectile->type) {
			case Map::TURRET_TILE:
				DrawProjectileWithRotation(&textures.at(ARROW), projectile->pos, projectile->goal);
				break;
			default:
                TraceLog(LOG_DEBUG, "Tile %s does not have a projectile implemented", TileMapToString(projectile->type));
                break;
		}
	}
}

void Renderer::DrawProjectileWithRotation(Texture* texture, const Vector2& pos, const Vector2& goal) {
	Vector2 dir = Vector2Subtract(goal, pos);

	float angleRad = atan2f(dir.y, dir.x);
	float angleDeg = angleRad * (180.0f / PI);

	Rectangle source = { 0, 0, 16.0, 8.0 };
	Rectangle dest = { pos.x, pos.y, 16.0, 8.0 };

	Vector2 origin = { 16 / 2.0f, 8 / 2.0f };

	// Center destination rect at pos
	dest.x -= origin.x;
	dest.y -= origin.y;

	DrawTexturePro(*texture, source, dest, origin, angleDeg, WHITE);
}

void Renderer::DrawGui() {
	const char* goldText = TextFormat("Gold: %ld", logic->GetGold());
	DrawText(goldText, Constants::Window::WIDTH - MeasureText(goldText, 24) - 30, 50, 24, GOLD);

	const char* healthText = TextFormat("HP: %ld", logic->GetHealth());
	DrawText(healthText, Constants::Window::WIDTH - MeasureText(goldText, 24) - 30 - 100 - MeasureText(healthText, 24), 50, 24, RED);

	const char* timeText = TextFormat("Time: %0.1f", logic->GetCurrentGameTime());
	DrawText(timeText, Constants::Window::WIDTH / 2 - MeasureText(timeText, 24), 50, 24, WHITE);

	DrawText(TextFormat("Wave: %d", logic->GetWaveNumber()), 10, 10, 20, WHITE);
}

void Renderer::DrawDebug() {
	for(const Map::Waypoint& waypoint : map->GetWaypoints()) {
		DrawCircle(waypoint.pos.x, waypoint.pos.y, 2, GREEN);

		if(CheckCollisionPointCircle(GetMousePosition(), waypoint.pos, 2)) {
			DrawText(TextFormat("Waypoint: %d", waypoint.index), GetMousePosition().x + 10, GetMousePosition().y, 24, WHITE);
		}
	}
}
