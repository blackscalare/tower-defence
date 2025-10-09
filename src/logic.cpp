#include "logic.h"
#include "enemy/blob/blob.h"
#include "enemy/skeleton/skeleton.h"
#include <algorithm>
#include <limits>
#include <raylib.h>
#include <raymath.h>

Logic::Logic() {}

Logic::Logic(Map* _map)
	: map(_map) {
}

Logic::~Logic() {
}

void Logic::Update(float deltaTime) {
	HandleEnemies(deltaTime);
	HandleTowers();
	HandleProjectiles(deltaTime);
	currentGameTime += deltaTime;
}

void Logic::HandleEnemies(float deltaTime) {
	timeSinceLastWave += deltaTime;
	if(!spawningWave && timeSinceLastWave >= waveInterval) {
		StartNextWave();
	}

	if(spawningWave) {
		spawnTimer += deltaTime;
		if(spawnTimer >= spawnDelay && enemiesToSpawn > 0) {
			SpawnEnemyForWave();
			spawnTimer = 0.0;
			enemiesToSpawn--;

			if(enemiesToSpawn == 0) {
				spawningWave = false;
				timeSinceLastWave = 0.0;
			}
		}
	}

	enemies.erase(
		std::remove_if(enemies.begin(), enemies.end(), [&](SPTR<Enemy> enemy) {
			return UpdateEnemy(deltaTime, enemy);
		}
	), enemies.end());
}

bool Logic::UpdateEnemy(float deltaTime, SPTR<Enemy>& enemy) {
	enemy->Update(deltaTime);
	if (enemy->isAtEnd()) {
		TakeDamage(enemy->GetDamage());
		return true;
	}
	if (enemy->IsDead()) {
		gold += enemy->GetValue();
		return true;
	}

	return false;
}

void Logic::StartNextWave() {
	spawningWave = true;
	enemiesToSpawn = 5 + waveNumber * 2;
	waveNumber++;
	spawnDelay = std::max(0.2, spawnDelay - 0.05);
}

void Logic::SpawnEnemyForWave() {
	SPTR<Enemy> enemy;

	if(waveNumber >= 5 && rand() % 3 == 0) {
		enemy = std::make_shared<Skeleton>(map->GetWaypoints(), enemyId++);
	} else {
		enemy = std::make_shared<Blob>(map->GetWaypoints(), enemyId++);
	}

	float healthMultiplier = 1.0f + waveNumber * 0.2f;
	float speedMultiplier = 1.0f + waveNumber * 0.05;

	enemy->ScaleStats(healthMultiplier, speedMultiplier);
	enemies.push_back(enemy);
}

void Logic::HandleTowers() {
	for(Map::Tile* tile : map->GetWallTiles()) {
		if(tile->tower) {
			Tower* t = tile->tower;
			double x = t->GetLastAttackTime();
			double y = t->GetAttackSpeed();

			if(std::abs(t->GetLastAttackTime() - currentGameTime) >= t->GetAttackSpeed()) {
				Vector2 nearestEnemyPos = FindEnemyNearestToEnd(tile);
				if(nearestEnemyPos.x > -1 && nearestEnemyPos.y > -1) {
					map->CreateProjectile(tile, nearestEnemyPos, 5.0f);
					t->SetLastAttackTime(currentGameTime);
				}
			}
		}
	}
}

void Logic::HandleProjectiles(float deltaTime) {
	auto& projectiles = map->GetProjectiles();
	projectiles.erase(
		std::remove_if(projectiles.begin(), projectiles.end(), [&](UPTR<Map::Projectile>& projectile) {
			projectile->Update(deltaTime);
			for(auto& enemy : enemies) {
				if(CheckCollisionCircles(projectile->pos, 2, enemy->GetPosition(), 5)) {
					enemy->TakeDamage(projectile->damage);
					return true;
				}
			}
			return Vector2Equals(projectile->pos, projectile->goal) ? true : false;
		}),
		projectiles.end()
	);
}

Vector2 Logic::FindEnemyNearestToEnd(Map::Tile* tile) {
	std::vector<SPTR<Enemy>> foundEnemies;
	for(auto enemy : enemies) {
		if(CheckCollisionCircles(tile->pos, tile->tower->GetRange(), enemy->GetPosition(), 5)) {
			foundEnemies.push_back(enemy);
		}
	}

	if(foundEnemies.empty()) return {-1, -1};

	std::sort(foundEnemies.begin(), foundEnemies.end(),
		   [this](const SPTR<Enemy>& a, const SPTR<Enemy>& b) {
		   		int aIndex = GetTileProgressIndex(a->GetPosition());
		   		int bIndex = GetTileProgressIndex(b->GetPosition());
		   		return aIndex > bIndex;
		   });
	return foundEnemies[0]->GetHitboxPosition();
}

int Logic::GetTileProgressIndex(const Vector2& pos) {
	int bestIndex = 0;
	float bestDist = std::numeric_limits<float>::max();

	for(size_t i = 0; i < map->GetWalkableTiles().size(); ++i) {
		Map::Tile tile = map->GetWalkableTiles()[i];
		if(CheckCollisionCircleRec(pos, 5, {tile.pos.x, tile.pos.y, 30, 30})) {
			if(tile.order > bestIndex)
				bestIndex = tile.order;
		}


		// float dist = Vector2Distance(pos, map->GetWalkableTiles()[i].pos);
		// if(dist < bestDist) {
		// 	bestDist = dist;
		// 	bestIndex = static_cast<int>(i);
		// }
	}
	return bestIndex;
}
