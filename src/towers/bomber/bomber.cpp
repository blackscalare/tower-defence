#include "bomber.h"
Bomber::Bomber() {
    cost = Constants::Towers::BOMBER_PRICE;
    attackSpeed = 4.0;
    range = Constants::Towers::BOMBER_RANGE;
    projectileSpeed = 4.0f;
    attackDamage = 50.0f;
}
