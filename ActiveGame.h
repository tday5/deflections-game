#ifndef ACTIVEGAME_H
#define ACTIVEGAME_H

#include <random>
#include "Player.h"
#include "Projectile.h"

namespace deflection {

/**
 * Represents the state of the active game, managing its player, target, walls,
 * and projectiles. Can generate levels, update the game, and check if it has
 * been won.
 * 
 * @author Trevor Day
 */
class ActiveGame {
public:

    /**
     * Constructs a new active game, using the given parameters.
     * @param screenWidth is an unsigned int representing the width of the screen
     * in pixels.
     * @param screenHeight is an unsigned int representing the height of the screen
     * in pixels.
     * @param playerImageIndex is an unsigned int representing the index of the
     * image for the player loaded in SDL.
     * @param targetImageIndex is an unsigned int representing the index of the
     * image for the target loaded in SDL.
     * @param wallImageIndex is an unsigned int representing the index of the
     * image for the wall loaded in SDL.
     * @param projectileImageIndex is an unsigned int representing the index of the
     * image for the projectile loaded in SDL.
     * @param numWalls is the number of walls that should be generated in the game
     */
    ActiveGame(unsigned int screenWidth, unsigned int screenHeight,
            unsigned int playerImageIndex, unsigned int targetImageIndex,
            unsigned int wallImageIndex, unsigned int projectileImageIndex,
            unsigned int numWalls) noexcept;

    /**
     * Returns a vector ImageObjects which are all the drawable objects in this
     * game.
     * @return a vector of ImageObjects. 
     */
    std::vector<ImageObject> getImagesToDraw() const noexcept;

    /**
     * Updates the state of the game, moving any projectiles the correct amount
     * and removing projectiles that have hit too many walls.
     */
    void updateState() noexcept;

    /**
     * Has the player of this active game fire towards the given coordinates.
     * @param x is the x coordinate to fire towards.
     * @param y is the y coordinate to fire towards.
     */
    void playerFire(int x, int y) noexcept;

    /**
     * Determines whether any projectile is in contact with the target, which
     * indicates that the game has been won.
     * @return true if the game has been won, false otherwise.
     */
    bool checkGameWon() const noexcept;

    /**
     * Starts a new game with a randomly placed player, randomly placed target,
     * and randomly placed and sized walls. All objects are guaranteed to not
     * overlap.
     */
    void startNewGame() noexcept;

private:

    /** An unsigned int representing the width of the screen. */
    const unsigned int screenWidth_;

    /** An unsigned int representing the height of the screen. */
    const unsigned int screenHeight_;

    /** An unsigned int representing the number of walls in this game. */
    const unsigned int numWalls_;

    /** An unsigned int representing the index of the wall image loaded in SDL. */
    const unsigned int wallImageIndex_;

    /** An unsigned int representing the index of the player image loaded in SDL. */
    const unsigned int playerImageIndex_;

    /** An unsigned int representing the index of the target image loaded in SDL. */
    const unsigned int targetImageIndex_;

    /** An unsigned int representing the index of the projectile image loaded in SDL. */
    const unsigned int projectileImageIndex_;

    /** The random device used to seed the random number generator. */
    std::random_device rd_;

    /** The random number generator used to randomly generate levels. */
    std::mt19937 r_;

    /** The distribution for random generation of any x values. */
    std::uniform_int_distribution<int> distrX_;

    /** The distribution for random generation of any y values. */
    std::uniform_int_distribution<int> distrY_;

    /** The distribution for random generation of angles. */
    std::uniform_int_distribution<int> distrA_;


    /** The Player of this ActiveGame. */
    Player player_;

    /** The ImageObject representing the target of this ActiveGame. */
    ImageObject target_;

    /** The vector of ImageObjects representing walls in this ActiveGame. */
    std::vector<ImageObject> walls_;

    /** The vector of Projectiles in this ActiveGame. */
    std::vector<Projectile> projectiles_;
};
}

#endif /* ACTIVEGAME_H */
