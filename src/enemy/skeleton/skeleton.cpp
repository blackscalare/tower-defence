#include "skeleton.h"

Skeleton::Skeleton() {
}

Skeleton::Skeleton(std::vector<Map::Waypoint> tileWaypoints, long id)
	: Enemy(tileWaypoints, id) {
	health = 50;
	speed = 50.0f;
	value = 5;
	damage = 10;
}

Skeleton::~Skeleton() {
}
