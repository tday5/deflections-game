#include <utility>
#include <cmath>
#include "Projectile.h"

using namespace std;
using namespace deflection;

Projectile::Projectile(unsigned int imageIndex, double x,
        double y, double vx, double vy, double sideLength) noexcept
: ImageObject(imageIndex, x, y, sideLength, sideLength, 0.0), vx_(vx), vy_(vy) {
}

int Projectile::getNumCollisions() const noexcept {
    return numCollisions_;
}

void Projectile::move(double delta, const std::vector<ImageObject>& walls,
        const unsigned int screenWidth, const unsigned int screenHeight) noexcept {

    double sideLength = width_ / 2.0;

    // Bounce against screen edges

    if (cx_ < sideLength) {
        cx_ = 2 * sideLength - cx_;
        vx_ = -vx_;
        numCollisions_ += 1;
    }
    if (cy_ < sideLength) {
        cy_ = 2 * sideLength - cy_;
        vy_ = -vy_;
        numCollisions_ += 1;
    }
    if (cx_ > screenWidth - sideLength) {
        cx_ = 2 * (screenWidth - sideLength) - cx_;
        vx_ = -vx_;
        numCollisions_ += 1;
    }
    if (cy_ > screenHeight - sideLength) {
        cy_ = 2 * (screenHeight - sideLength) - cy_;
        vy_ = -vy_;
        numCollisions_ += 1;
    }

    // Bounce against walls
    for (const ImageObject& w : walls) {
        if (hits(w)) {
            pair<double, double> temp = bounce(w, vx_, vy_);
            vx_ = get<0>(temp);
            vy_ = get<1>(temp);
            // Normalize returned velocity
            double total = abs(vx_) + abs(vy_);
            vx_ = vx_ / total;
            vy_ = vy_ / total;

            // Increment collisions
            numCollisions_ += 1;
        }
    }

    // Update position
    cx_ += delta * vx_;
    cy_ += delta * vy_;
}
