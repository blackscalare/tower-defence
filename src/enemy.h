#pragma once

#include <raylib.h>
#include <vector>

class Enemy{
public:
	Enemy();
	Enemy(std::vector<Vector2> tileWaypoints);
	Enemy(Enemy &&) = default;
	Enemy(const Enemy &) = default;
	Enemy &operator=(Enemy &&) = default;
	Enemy &operator=(const Enemy &) = default;
	~Enemy();

	void Update(float deltaTime);
private:
	std::vector<Vector2> waypoints;
	int currentWaypointIndex = 0;
	bool reachedGoal = false;
	Vector2 position = {0, 0};
	float speed = 5.0f;
};


