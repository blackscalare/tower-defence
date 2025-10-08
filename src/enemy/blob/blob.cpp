#include "blob.h"
#include <vector>

Blob::Blob() {}

Blob::Blob(std::vector<Map::Waypoint> tileWaypoints, long id)
	: Enemy(tileWaypoints, id) {
	health = 20;
	value = 2;
}

Blob::~Blob() {
}
