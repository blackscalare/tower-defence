#pragma once
#include "constants.h"
#include "enemy/enemy.h"
#include "map/map.h"
#include "towers/turret/turret.h"
#include <memory>

class Logic {
public:
	Logic();
	Logic(Map* map);
	Logic(Logic &&) = default;
	Logic(const Logic &) = default;
	Logic &operator=(Logic &&) = default;
	Logic &operator=(const Logic &) = default;
	~Logic();

	void Update(float deltaTime);
	std::vector<SPTR<Enemy>> GetEnemies() { return enemies; }
	long GetGold() { return gold; }
	long GetHealth() { return health;}
	bool BuyItem(long price) { 
		if(price > gold) return false;
		gold -= price;
		return true;
	}
	void TakeDamage(int damage) {
		health -= damage;
		if(health < 0) {
			gameOver = true;
		} 
	}
	Map::TileType GetCurrentlySelectedTile() { return currentlySelectedTile; }
	int GetWaveNumber() { return waveNumber; }
private:
	void HandleEnemies(float deltaTime);
	void HandleTowers();
	void HandleProjectiles(float deltaTime);
	Vector2 FindNearestEnemyInRange(Map::Tile* tile);
	void StartNextWave();
	void SpawnEnemyForWave();

	Map* map;
	std::vector<SPTR<Enemy>> enemies;
	long gold = 100;
	Map::TileType currentlySelectedTile = Map::TURRET_TILE;
	long health = 100;
	bool gameOver = false;
	long enemyId = 0L;

	// TODO: Start at 0
	int waveNumber = 1;
	double timeSinceLastWave = 0.0;
	double waveInterval = 10.0;

	bool spawningWave = false;
	int enemiesToSpawn = 0;
	double spawnDelay = 0.5;
	double spawnTimer = 0.0;
};


