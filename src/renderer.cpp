#include "renderer.h"
#include "constants.h"
#include "logic.h"
#include <cstdio>
#include <cstdlib>
#include <raylib.h>
#include <raymath.h>
#include "towers/tower.h"
#include "utils/color_utils.hpp"
#include "utils/enum_utils.hpp"

Renderer::Renderer(Map* map, Logic* logic) {
	this->map = map;
	this->logic = logic;
	Image arrowImage = LoadImage("assets/towers/turret/arrow.bmp");
	Image skeletonImage = LoadImage("assets/enemies/skeleton/skeleton.bmp");
	Image turretImage = LoadImage("assets/towers/turret/turret.bmp");
	Image sniperImage = LoadImage("assets/towers/sniper/sniper.bmp");

	if(arrowImage.data == nullptr) {
		TraceLog(LOG_ERROR, "Failed to load arrow image");
	}
	if(skeletonImage.data == nullptr) {
		TraceLog(LOG_ERROR, "Failed to load skeleton image");
	}
	if(turretImage.data == nullptr) {
	    TraceLog(LOG_ERROR, "Failed to load turret image");
	}
	if(sniperImage.data == nullptr) {
	    TraceLog(LOG_ERROR, "Failed to load sniper image");
	}

	ImageResize(&arrowImage, 16, 8);

	textures.insert(std::pair(ARROW, LoadTextureFromImage(arrowImage)));
	textures.insert(std::pair(SKELETON, LoadTextureFromImage(skeletonImage)));
	textures.insert(std::pair(TURRET, LoadTextureFromImage(turretImage)));
	textures.insert(std::pair(SNIPER, LoadTextureFromImage(sniperImage)));

	for(const auto& texture : textures) {
		if(texture.second.id == 0) {
			TraceLog(LOG_ERROR, "Failed to load %s", TextureNameToString(texture.first));
		}
	}

	UnloadImage(arrowImage);
	UnloadImage(skeletonImage);
	UnloadImage(turretImage);
	UnloadImage(sniperImage);
}

void Renderer::Update() {
	DrawTiles();
	DrawGameObjects();
	DrawGui();
	DrawHoverEffect();
	DrawTowerPlacementEffect();
	DrawDebug();
}

void Renderer::DrawTiles() {
	for(const Map::Tile& tile : map->GetWalkableTiles()) {
		DrawRectangleLines(tile.pos.x, tile.pos.y, tile.width, tile.height, BROWN);
		DrawText(TextFormat("%d", tile.order), tile.pos.x + 30.0/2, tile.pos.y + 30.0/2, 4, WHITE);
	}
	for(auto tile : map->GetWallTiles()) {
		DrawRectangleLines(tile->pos.x, tile->pos.y, tile->width, tile->height, GREEN);
		if(tile->tower != nullptr) {
		    if(tile->tower->GetTowerType() == Tower::TURRET) {
				DrawTexture(textures.at(TURRET), tile->pos.x, tile->pos.y, WHITE);
			}

			if(tile->tower->GetTowerType() == Tower::SNIPER) {
                DrawTexture(textures.at(SNIPER), tile->pos.x, tile->pos.y, WHITE);
			}
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

	DrawTowerBoxes();
}

void Renderer::DrawTowerBoxes() {
    DrawRectangleLines(Constants::Gui::TURRET_BOX_1_X, Constants::Gui::TURRET_BOX_Y, Constants::Gui::TURRET_BOX_WIDTH, Constants::Gui::TURRET_BOX_HEIGHT, WHITE);
    // TODO: replace with turret texture
    DrawCircle(Constants::Window::WIDTH / 2 - ((100 / 2) / 2 - 25), Constants::Window::HEIGHT - 100 / 2, 25, WHITE);

    DrawRectangleLines(Constants::Gui::TURRET_BOX_2_X, Constants::Gui::TURRET_BOX_Y, Constants::Gui::TURRET_BOX_WIDTH, Constants::Gui::TURRET_BOX_HEIGHT, WHITE);
    // TODO: replace with sniper texture
    DrawCircle(Constants::Window::WIDTH / 2 - ((100 / 2) / 2 - 25) + 125, Constants::Window::HEIGHT - 100 / 2, 25, YELLOW);
}

void Renderer::DrawHoverEffect() {
    switch(logic->GetCurrentlyHoveredGuiElement()) {
        case Logic::TURRET_SELECT_ELEMENT:
            DrawRectangle(Constants::Gui::TURRET_BOX_1_X, Constants::Gui::TURRET_BOX_Y, Constants::Gui::TURRET_BOX_WIDTH, Constants::Gui::TURRET_BOX_HEIGHT, Constants::Colors::HOVER_EFFECT);
            break;
        case Logic::SNIPER_SELECT_ELEMENT:
            DrawRectangle(Constants::Gui::TURRET_BOX_2_X, Constants::Gui::TURRET_BOX_Y, Constants::Gui::TURRET_BOX_WIDTH, Constants::Gui::TURRET_BOX_HEIGHT, Constants::Colors::HOVER_EFFECT);
            break;
        case Logic::NONE:
            break;
    }

    // TODO: make smarter or change the appearence of selection
    switch(logic->GetCurrentTurretSelection()) {
        case Tower::TURRET:
            DrawRectangle(Constants::Gui::TURRET_BOX_1_X, Constants::Gui::TURRET_BOX_Y, Constants::Gui::TURRET_BOX_WIDTH, Constants::Gui::TURRET_BOX_HEIGHT, Constants::Colors::HOVER_EFFECT);
            break;
        case Tower::SNIPER:
            DrawRectangle(Constants::Gui::TURRET_BOX_2_X, Constants::Gui::TURRET_BOX_Y, Constants::Gui::TURRET_BOX_WIDTH, Constants::Gui::TURRET_BOX_HEIGHT, Constants::Colors::HOVER_EFFECT);
            break;

    }
}

void Renderer::DrawTowerPlacementEffect() {
    for(Map::Tile* tile : map->GetWallTiles()) {
		if(CheckCollisionPointRec(GetMousePosition(), {tile->pos.x, tile->pos.y, tile->width, tile->height})) {
			if(tile->tower == nullptr) {
			    switch(logic->GetCurrentTurretSelection()) {
					case Tower::TURRET:
						DrawTexture(textures.at(TURRET), tile->pos.x, tile->pos.y, ChangeAlpha(WHITE, 150));
						DrawCircleLines(tile->pos.x + (float)textures.at(TURRET).width / 2, tile->pos.y + (float)textures.at(TURRET).height / 2, Constants::Towers::TURRET_RANGE, ChangeAlpha(WHITE, 100));
						DrawCircle(tile->pos.x + (float)textures.at(TURRET).width / 2, tile->pos.y + (float)textures.at(TURRET).height / 2, Constants::Towers::TURRET_RANGE, ChangeAlpha(WHITE, 50));
					    break;
					case Tower::SNIPER:
	                    DrawTexture(textures.at(SNIPER), tile->pos.x, tile->pos.y, ChangeAlpha(WHITE, 150));
						DrawCircleLines(tile->pos.x + (float)textures.at(SNIPER).width / 2, tile->pos.y + (float)textures.at(SNIPER).height / 2, Constants::Towers::SNIPER_RANGE, ChangeAlpha(WHITE, 100));
						DrawCircle(tile->pos.x + (float)textures.at(SNIPER).width / 2, tile->pos.y + (float)textures.at(SNIPER).height / 2, Constants::Towers::SNIPER_RANGE, ChangeAlpha(WHITE, 50));
					    break;
				}
			}
		}
	}
}

void Renderer::DrawDebug() {
	for(const Map::Waypoint& waypoint : map->GetWaypoints()) {
		DrawCircle(waypoint.pos.x, waypoint.pos.y, 2, GREEN);

		if(CheckCollisionPointCircle(GetMousePosition(), waypoint.pos, 2)) {
			DrawText(TextFormat("Waypoint: %d", waypoint.index), GetMousePosition().x + 10, GetMousePosition().y, 24, WHITE);
		}
	}
}
