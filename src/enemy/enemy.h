#pragma once

#include <raylib.h>
#include <vector>

class Enemy {
public:
	Enemy();
	Enemy(std::vector<Vector2> tileWaypoints, long id);
	Enemy(Enemy &&) = default;
	Enemy(const Enemy &) = default;
	Enemy &operator=(Enemy &&) = default;
	Enemy &operator=(const Enemy &) = default;
	~Enemy();

	void Update(float deltaTime);
	Vector2 GetPosition() { return position; }
	// TODO: fix
	Vector2 GetHitboxPosition() { return {position.x + (5 / 2), position.y + (5 / 2)}; }
	void TakeDamage(int damage);
	bool isAtEnd() { return currentWaypointIndex == waypoints.size(); }
	int GetDamage() { return damage; }
	long GetId() { return id; }
	bool operator=(const Enemy& o) const { return id == o.id; }
	bool operator<(const Enemy& rhs) const { return currentWaypointIndex < rhs.currentWaypointIndex; }
	bool operator<=(const Enemy& rhs) const { return currentWaypointIndex <= rhs.currentWaypointIndex; }
	bool operator>(const Enemy& rhs) const { return currentWaypointIndex > rhs.currentWaypointIndex; }

protected:
	float speed = 30.0f;
	int health = 100;
	int value = 10;
	int damage = 5;
private:
	long id;
	std::vector<Vector2> waypoints;
	std::size_t currentWaypointIndex = 0;
	bool reachedGoal = false;
	Vector2 position = {0, 0};
};
