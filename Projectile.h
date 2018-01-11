#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "ImageObject.h"

namespace deflection {

/**
 * Represents a projectile in the game, with a velocity x and a velocity y, and
 * is derived from ImageObject.
 * @author Trevor Day
 */
class Projectile : public ImageObject {
public:

    /**
     * Constructs a new Projectile using the given arguments.
     * @param imageIndex is an unsigned int representing the index of the image
     * loaded in SDL that should be used when rendering this Projectile.
     * @param x is a double representing an x coordinate.
     * @param y is a double representing a y coordinate.
     * @param vx is the velocity in the x axis.
     * @param vy is the velocity in the y axis.
     * @param sideLength is the length of the sides of the projectile square.
     */
    Projectile(unsigned int imageIndex, double x, double y, double vx,
            double vy, double sideLength) noexcept;

    /**
     * Returns the number of collisions of this Projectile.
     * @return an int representing the number of collisions.
     */
    int getNumCollisions() const noexcept;

    /**
     * Moves this Projectile according to the given delta, also checks for
     * collisions with the vector of Walls and the top, bottom, and sides of
     * the screen, and bounces it accordingly. Also increments
     * the number of collisions if necessary.
     * @param delta is the delta of time to move this Projectile by.
     * @param walls is the vector of Walls to check for collisions.
     * @param screenWidth is the width of the screen.
     * @param screenHeight is the height of the screen.
     */
    void move(double delta, const std::vector<ImageObject>& walls,
            const unsigned int screenWidth, const unsigned int screenHeight) noexcept;

private:

    /** An int representing the number of collisions of this Projectile. */
    int numCollisions_ = 0;

    /** The x velocity of this Projectile. */
    double vx_ = 0.0;

    /** The y velocity of this Projectile. */
    double vy_ = 0.0;
};
}

#endif /* PROJECTILE_H */
