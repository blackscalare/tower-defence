#pragma once

#include "map.h"

class Renderer {
public:
	Renderer();
	Renderer(Map* map);
	Renderer(Renderer &&) = default;
	Renderer(const Renderer &) = default;
	Renderer &operator=(Renderer &&) = default;
	Renderer &operator=(const Renderer &) = default;
	~Renderer();
	
	void Update();
private:
	Map* map;
};
