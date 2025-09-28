#include "logic.h"
#include "enemy/blob/blob.h"
#include "enemy/skeleton/skeleton.h"

Logic::Logic() {}

Logic::Logic(Map* _map)
	: map(_map){
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
