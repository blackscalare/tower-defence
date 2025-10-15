#pragma once

#include "../tower.h"

class Sniper : public Tower {
public:
    Sniper();
    Sniper(Sniper &&) = default;
    Sniper(const Sniper &) = default;
    Sniper &operator=(Sniper &&) = default;
    Sniper &operator=(const Sniper&) = default;
    ~Sniper() {};

    TowerType GetTowerType() override {
	    return SNIPER;
	}

private:
};
