#pragma once

#include "map.h"
#include "logic.h"

class Renderer {
public:
	Renderer();
	Renderer(Map* map, Logic* logic);
	Renderer(Renderer &&) = default;
	Renderer(const Renderer &) = default;
	Renderer &operator=(Renderer &&) = default;
	Renderer &operator=(const Renderer &) = default;
	~Renderer();
	
	void Update();
private:
	Map* map;
	Logic* logic;
};
