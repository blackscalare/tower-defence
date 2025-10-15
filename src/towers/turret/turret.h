#pragma once

#include "../tower.h"

class Turret : public Tower {
public:
	Turret();
	Turret(Turret &&) = default;
	Turret(const Turret &) = default;
	Turret &operator=(Turret &&) = default;
	Turret &operator=(const Turret &) = default;
	~Turret();

private:
};
