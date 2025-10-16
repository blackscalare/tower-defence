#pragma once
#include "../tower.h"

class Bomber : public Tower {
public:
    Bomber();
    Bomber(Bomber &&) = default;
    Bomber(const Bomber &) = default;
    Bomber &operator=(Bomber &&) = default;
    Bomber &operator=(const Bomber&) = default;
    ~Bomber() {};

    TowerType GetTowerType() override {
	    return BOMBER;
	}

private:
};
