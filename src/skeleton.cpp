#include "skeleton.h"

Skeleton::Skeleton() {
}

Skeleton::Skeleton(std::vector<Vector2> tileWaypoints)
	: Enemy(tileWaypoints) {
	health = 50;
	speed = 50.0f;
}

Skeleton::~Skeleton() {
}
