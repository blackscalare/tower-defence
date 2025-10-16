#pragma once
#include "constants.h"
#include "enemy/enemy.h"
#include "map/map.h"
#include <memory>

class Logic {
public:
	Logic() {};
	Logic(Map* map);
	Logic(Logic &&) = default;
	Logic(const Logic &) = default;
	Logic &operator=(Logic &&) = default;
	Logic &operator=(const Logic &) = default;
	~Logic() {};

	enum GuiElement {
	    NONE,
	    TURRET_SELECT_ELEMENT,
		SNIPER_SELECT_ELEMENT,
		BOMBER_SELECT_ELEMENT
	};

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
	void SetCurrentlySelectedTile(Map::TileType tileType) { currentlySelectedTile = tileType; }
	int GetWaveNumber() { return waveNumber; }
	double GetCurrentGameTime() { return currentGameTime; }
	void SetCurrentHoveredGuiElement(GuiElement element) { currentlyHoveredElement = element; };
	GuiElement GetCurrentlyHoveredGuiElement() { return currentlyHoveredElement; }
	Tower::TowerType GetCurrentTurretSelection() { return currentTurretSelection; }
	void SetCurrentTurretSelection(Tower::TowerType turretSelection) { currentTurretSelection = turretSelection; }
private:
	void HandleEnemies(float deltaTime);
	bool UpdateEnemy(float deltaTime, SPTR<Enemy>& enemy);
	void HandleTowers();
	void HandleProjectiles(float deltaTime);
	Vector2 FindEnemyNearestToEnd(Map::Tile* tile);
	int GetTileProgressIndex(const Vector2& pos);
	void StartNextWave();
	void SpawnEnemyForWave();

	Map* map;
	std::vector<SPTR<Enemy>> enemies;
	long gold = 100;
	Map::TileType currentlySelectedTile = Map::TURRET_TILE;
	long health = 100;
	bool gameOver = false;
	long enemyId = 0L;

	int waveNumber = 0;
	double timeSinceLastWave = 0.0;
	double waveInterval = 10.0;

	bool spawningWave = false;
	int enemiesToSpawn = 0;
	double spawnDelay = 0.5;
	double spawnTimer = 0.0;

	double currentGameTime = 0.0;

	GuiElement currentlyHoveredElement;
	Tower::TowerType currentTurretSelection = Tower::TURRET;
};
