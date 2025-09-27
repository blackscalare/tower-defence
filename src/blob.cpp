#include "blob.h"
#include <vector>

Blob::Blob() {}

Blob::Blob(std::vector<Vector2> tileWaypoints)
	: Enemy(tileWaypoints) {
	health = 20;
}

Blob::~Blob() {
}
