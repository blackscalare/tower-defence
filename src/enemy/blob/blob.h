#pragma once
#include "../enemy.h"

class Blob : public Enemy {
public:
	Blob();
	Blob(std::vector<Map::Waypoint> tileWaypoints, long id);
	Blob(Blob &&) = default;
	Blob(const Blob &) = default;
	Blob &operator=(Blob &&) = default;
	Blob &operator=(const Blob &) = default;
	~Blob();

private:
	
};
