#include "logic.h"
#include "blob.h"
#include "skeleton.h"

Logic::Logic() {}

Logic::Logic(Map* map) {
	enemies.push_back(new Blob(map->GetWaypoints()));
	enemies.push_back(new Skeleton(map->GetWaypoints()));
}

Logic::~Logic() {
}

void Logic::Update(float deltaTime) {
	for(Enemy* enemy : enemies) {
		enemy->Update(deltaTime);
	}
}
