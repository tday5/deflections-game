#ifndef PLAYER_H
#define PLAYER_H

#include "Projectile.h"

namespace deflection {

/**
 * Represents a Player in the deflection game, which can fire and also derives
 * from ImageObject.
 * @author Trevor Day
 */
class Player : public ImageObject {
public:

    /**
     * Constructs a new Player with the given arguments.
     * @param imageIndex is an unsigned int representing the index of the image
     * loaded in SDL that should be used when rendering this Player.
     * @param x is a double representing an x coordinate.
     * @param y is a double representing a y coordinate.
     * @param sideLength is a double representing the length of the sides of the
     * player square.
     */
    Player(unsigned int imageIndex, double x, double y, double sideLength) noexcept;

    /**
     * Returns a projectile fired from this Player towards the given coordinates,
     * with the proper velocity.
     * @param x is the x coordinate to fire towards.
     * @param y is the y coordinate to fire towards.
     * @param projectileImageIndex is the index of the image loaded in SDL to
     * use for projectiles.
     * @return a new Projectile which has the correct normalized velocity,
     * according to the position of the player and the position towards which
     * it is fired.
     */
    Projectile fire(int x, int y, unsigned int projectileImageIndex) const noexcept;
};
}


#endif /* PLAYER_H */
