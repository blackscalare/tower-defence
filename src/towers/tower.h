#pragma once

class Tower {
public:
	Tower();
	Tower(Tower &&) = default;
	Tower(const Tower &) = default;
	Tower &operator=(Tower &&) = default;
	Tower &operator=(const Tower &) = default;
	~Tower();

	void Update();
	int GetCost() { return cost; }
	int GetAttackSpeed() { return attackSpeed; }
	double GetLastAttackTime() { return lastAttackTime; }
	void SetLastAttackTime(double time) { lastAttackTime = time; }
	float GetRange() { return range; }
protected:
	int cost = 30;
	double attackSpeed = 1.5;
	double lastAttackTime = 0.0;
	float range = 100.0f;
private:
	
};

