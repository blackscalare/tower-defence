#pragma once
#include "enemy.h"
#include "map.h"

class Logic {
public:
	Logic();
	Logic(Map* map);
	Logic(Logic &&) = default;
	Logic(const Logic &) = default;
	Logic &operator=(Logic &&) = default;
	Logic &operator=(const Logic &) = default;
	~Logic();

	void Update(float deltaTime);
	std::vector<Enemy*> GetEnemies() { return enemies; }
private:
	Map* map;
	std::vector<Enemy*> enemies;

};


