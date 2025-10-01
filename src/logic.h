#pragma once
#include "enemy/enemy.h"
#include "map/map.h"

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
	long GetGold() { return gold; }
	bool BuyItem(long price) { 
		if(price > gold) return false;
		gold -= price;
		return true;
	}
private:
	Map* map;
	std::vector<Enemy*> enemies;
	long gold = 100;
};


