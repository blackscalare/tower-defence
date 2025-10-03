#include "logic.h"
#include "enemy/blob/blob.h"
#include "enemy/skeleton/skeleton.h"
#include <algorithm>
#include <raylib.h>

Logic::Logic() {}

Logic::Logic(Map* _map)
	: map(_map) {
	SPTR<Enemy> initialBlob = std::make_shared<Blob>(map->GetWaypoints(), enemyId++);
	SPTR<Enemy> initialSkeleton = std::make_shared<Skeleton>(map->GetWaypoints(), enemyId++);
	enemies.push_back(initialBlob);
	enemies.push_back(initialSkeleton);
}

Logic::~Logic() {
}

void Logic::Update(float deltaTime) {
	HandleEnemies(deltaTime);
	// for(Enemy* enemy : enemies) {
	// 	enemy->Update(deltaTime);
	// 	if(enemy->isAtEnd()) {
	// 		TakeDamage(enemy->GetDamage());
	// 	}
	// }
	HandleTowers();
	HandleProjectiles(deltaTime);
}

void Logic::HandleEnemies(float deltaTime) {
	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(),
				 [&](SPTR<Enemy> enemy) {
				 	enemy->Update(deltaTime);
				 	if(enemy->isAtEnd()) {
				 		TakeDamage(enemy->GetDamage());
						return true;
				 	}
				 	return false;
				 }
	), enemies.end());
}

void Logic::HandleTowers() {
	for(Map::Tile* tile : map->GetWallTiles()) {
		if(tile->tower) {
			Tower* t = tile->tower;
			double currentTime = GetTime();
			double x = t->GetLastAttackTime();
			double y = t->GetAttackSpeed();

			if(std::abs(t->GetLastAttackTime() - currentTime) >= t->GetAttackSpeed()) {
				Vector2 nearestEnemyPos = FindNearestEnemyInRange(tile);
				if(nearestEnemyPos.x > -1 && nearestEnemyPos.y > -1) {
					map->CreateProjectile(tile, nearestEnemyPos, 5.0f);
					t->SetLastAttackTime(currentTime);
				}
			}
		}
	}
}

void Logic::HandleProjectiles(float deltaTime) {
	for(auto& projectile : map->GetProjectiles()) {
		projectile->Update(deltaTime);
	}
}

Vector2 Logic::FindNearestEnemyInRange(Map::Tile* tile) {
	std::vector<SPTR<Enemy>> foundEnemies;
	for(auto enemy : enemies) {
		if(CheckCollisionCircles(tile->pos, tile->tower->GetRange(), enemy->GetPosition(), 5)) {
			foundEnemies.push_back(enemy);
		}
	}
	if(std::empty(foundEnemies)) return {-1, -1};
	std::sort(foundEnemies.begin(), foundEnemies.end(), [](SPTR<Enemy> a, SPTR<Enemy> b)
		   {
		   	return a > b;
		   });
	
	return foundEnemies[0]->GetHitboxPosition();
}
