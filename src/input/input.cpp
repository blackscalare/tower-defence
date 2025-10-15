#include "input.h"
#include <raylib.h>
#include "../towers/turret/turret.h"
#include "../towers/sniper/sniper.h"

Input::Input(Map* map, Logic* logic)
	:map(map), logic(logic) {
}

Input::~Input() {
}

void Input::Update() {
	HandleMapInputs();
	HandleGui();
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
	Tower::TowerType tileType = logic->GetCurrentTurretSelection();
	int price = -1;

	switch(tileType) {
		case Tower::TURRET:
			price = Constants::Towers::TURRET_PRICE;
		    break;
		case Tower::SNIPER:
		    price = Constants::Towers::SNIPER_PRICE;
		    break;
	}

	if(price == -1) return;

	if(logic->BuyItem(price)) {
	    tile->has_placement = true;
		switch(tileType) {
			case Tower::TURRET:
			    tile->tower = new Turret();
			    break;
			case Tower::SNIPER:
                tile->tower = new Sniper();
			    break;
		}
	}
}

void Input::HandleGui() {
    if(CheckCollisionPointRec(GetMousePosition(), {Constants::Gui::TURRET_BOX_1_X, Constants::Gui::TURRET_BOX_Y, Constants::Gui::TURRET_BOX_WIDTH, Constants::Gui::TURRET_BOX_HEIGHT})) {
        logic->SetCurrentHoveredGuiElement(Logic::GuiElement::TURRET_SELECT_ELEMENT);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            logic->SetCurrentTurretSelection(Tower::TURRET);
    } else if(CheckCollisionPointRec(GetMousePosition(), {Constants::Gui::TURRET_BOX_2_X, Constants::Gui::TURRET_BOX_Y, Constants::Gui::TURRET_BOX_WIDTH, Constants::Gui::TURRET_BOX_HEIGHT})) {
        logic->SetCurrentHoveredGuiElement(Logic::GuiElement::SNIPER_SELECT_ELEMENT);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            logic->SetCurrentTurretSelection(Tower::SNIPER);
    } else {
        logic->SetCurrentHoveredGuiElement(Logic::GuiElement::NONE);
    }
}
