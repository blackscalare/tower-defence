#include "enemy.h"
#include <raymath.h>

Enemy::Enemy(std::vector<Vector2> tileWaypoints) 
	: waypoints(tileWaypoints), position(waypoints[0]) {
}

void Enemy::Update(float deltaTime) {
	if(currentWaypointIndex >= waypoints.size()) {
		reachedGoal = true;
		return;
	}

	Vector2 target = waypoints[currentWaypointIndex];
	Vector2 direction = Vector2Normalize(target - position);
	position = position + direction * speed * deltaTime;
	
	if(Vector2Distance(position, target) <= 1.0f) {
		currentWaypointIndex++;
	}
}
