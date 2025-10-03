#pragma once

#include "../map/map.h"
#include "../logic.h"

class Input {
public:
	Input(Map* map, Logic* logic);
	Input(Input &&) = default;
	Input(const Input &) = default;
	Input &operator=(Input &&) = default;
	Input &operator=(const Input &) = default;
	~Input();
	
	void Update();
private:
	Map* map;
	Logic* logic;

	void HandleMapInputs();
	void HandleBuyTile(Map::Tile* tile);
};
