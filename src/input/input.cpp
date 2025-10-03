#include "input.h"
#include <raylib.h>

Input::Input(Map* map, Logic* logic)
	:map(map), logic(logic) {
}

Input::~Input() {
}

void Input::Update() {
	HandleMapInputs();
}

void Input::HandleMapInputs() {
	for(Map::Tile* tile : map->GetWallTiles()) {
		if(CheckCollisionPointRec(GetMousePosition(), {tile->pos.x, tile->pos.y, tile->width, tile->height})) {
			if(!tile->has_placement && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				HandleBuyTile(tile);
			}
		} 
	}
}

void Input::HandleBuyTile(Map::Tile* tile) {
	Map::TileType tileType = logic->GetCurrentlySelectedTile();
	switch(tileType) {
		case Map::TURRET_TILE:
			tile->tower = new Turret();
			break;
	}
	if(logic->BuyItem(tile->tower->GetCost()))
		tile->has_placement = true;
	else
		delete tile->tower;
}
