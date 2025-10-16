#include "input.h"
#include <raylib.h>
#include "../towers/turret/turret.h"
#include "../towers/sniper/sniper.h"
#include "../towers/bomber/bomber.h"

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
		case Tower::BOMBER:
		    price = Constants::Towers::BOMBER_PRICE;
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
			case Tower::BOMBER:
			    tile->tower = new Bomber();
				break;
		}
	}
}

void Input::HandleGui() {
    Logic::GuiElement hoveredElement = Logic::GuiElement::NONE;

    if(HandleTowerBoxInput(Constants::Gui::TURRET_BOX_1_X, Tower::TURRET)) {
        hoveredElement = Logic::GuiElement::TURRET_SELECT_ELEMENT;
    }
    else if(HandleTowerBoxInput(Constants::Gui::TURRET_BOX_2_X, Tower::SNIPER)) {
        hoveredElement = Logic::GuiElement::SNIPER_SELECT_ELEMENT;
    }
    else if(HandleTowerBoxInput(Constants::Gui::TURRET_BOX_3_X, Tower::BOMBER)) {
        hoveredElement = Logic::GuiElement::BOMBER_SELECT_ELEMENT;
    }

    logic->SetCurrentHoveredGuiElement(hoveredElement);
}

bool Input::HandleTowerBoxInput(float xPos, Tower::TowerType towerType) {
    if(CheckCollisionPointRec(GetMousePosition(), {xPos, Constants::Gui::TURRET_BOX_Y, Constants::Gui::TURRET_BOX_WIDTH, Constants::Gui::TURRET_BOX_HEIGHT})) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            logic->SetCurrentTurretSelection(towerType);
        }
        return true;
    }

    return false;
}
