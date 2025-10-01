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
				if(logic->BuyItem(10))
					tile->has_placement = true;
			}
		} 
	}
}
