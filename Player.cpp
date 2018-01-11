#include <cmath>
#include "Player.h"

#include <iostream>
using namespace std;
using namespace deflection;

Player::Player(unsigned int imageIndex, double x, double y, double sideLength) noexcept
: ImageObject(imageIndex, x, y, sideLength, sideLength, 0.0) {
}

Projectile Player::fire(int x, int y, unsigned int projectileImageIndex) const noexcept {
    // Normalize the velocities as fractions of 1
    double total = abs(x - cx_) + abs(y - cy_);
    double vx = (x - cx_) / total;
    double vy = (y - cy_) / total;

    return Projectile(projectileImageIndex, cx_, cy_, vx, vy, 10);
}
