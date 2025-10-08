#include "enemy.h"
#include <raymath.h>

Enemy::Enemy() {}
Enemy::~Enemy() {}

Enemy::Enemy(std::vector<Map::Waypoint> tileWaypoints, long id) 
	: waypoints(tileWaypoints), position(waypoints[0].pos), id(id) {
}

void Enemy::Update(float deltaTime) {
	if(currentWaypointIndex >= waypoints.size()) {
		reachedGoal = true;
		return;
	}

	Vector2 target = waypoints[currentWaypointIndex].pos;
	Vector2 direction = Vector2Normalize(target - position);
	position = position + direction * speed * deltaTime;
	
	if(Vector2Distance(position, target) <= 1.0f) {
		currentWaypointIndex++;
	}
}

void Enemy::TakeDamage(int damage) {
	health -= damage;
	if(health <= 0) {
		dead = true;
	}
}

void Enemy::ScaleStats(float healthMultiplier, float speedMultiplier) {
	health = static_cast<int>(health * healthMultiplier);
	speed *= speedMultiplier;
}
