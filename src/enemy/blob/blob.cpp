#include "blob.h"
#include <vector>

Blob::Blob() {}

Blob::Blob(std::vector<Vector2> tileWaypoints, long id)
	: Enemy(tileWaypoints, id) {
	health = 20;
	value = 2;
}

Blob::~Blob() {
}
