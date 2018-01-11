#include "ActiveGame.h"

using namespace std;
using namespace deflection;

ActiveGame::ActiveGame(unsigned int screenWidth, unsigned int screenHeight,
        unsigned int playerImageIndex, unsigned int targetImageIndex,
        unsigned int wallImageIndex, unsigned int projectileImageIndex, unsigned int numWalls) noexcept
: screenWidth_(screenWidth), screenHeight_(screenHeight), r_(rd_()),
distrX_(0, screenWidth), distrY_(0, screenHeight), distrA_(0, 180),
walls_(), projectiles_(), numWalls_(numWalls), wallImageIndex_(wallImageIndex),
playerImageIndex_(playerImageIndex), targetImageIndex_(targetImageIndex),
projectileImageIndex_(projectileImageIndex), player_(Player(0, 0, 0, 0)), target_(0, 0, 0, 0, 0, 0) {
    startNewGame();
}

vector<ImageObject> ActiveGame::getImagesToDraw() const noexcept {
    // Create a temporary vector to store the ImageObjects
    vector<ImageObject> temp;
    // Add the player
    temp.push_back(player_);
    // Add the target
    temp.push_back(target_);
    // Add the walls
    for (ImageObject w : walls_) {
        temp.push_back(w);
    }
    // Add the projectiles
    for (Projectile p : projectiles_) {
        temp.push_back(p);
    }
    return temp;
}

void ActiveGame::updateState() noexcept {
    // Iterate through the projectiles, moving them and checking if the
    // number of collisions is too great, and if so removes them
    for (auto i = projectiles_.begin(); i != projectiles_.end();) {
        (*i).move(5, walls_, screenWidth_, screenHeight_);
        if ((*i).getNumCollisions() > numWalls_) {
            projectiles_.erase(i);
        } else {
            i += 1;
        }
    }
}

void ActiveGame::playerFire(int x, int y) noexcept {
    // Adds the projectile that the player fires to the vector of projectiles
    projectiles_.push_back(player_.fire(x, y, projectileImageIndex_));
}

bool ActiveGame::checkGameWon() const noexcept {
    bool temp = false;
    for (Projectile p : projectiles_) {
        // Check if any projectiles are hitting the target
        temp = p.hits(target_);
    }
    return temp;
}

void ActiveGame::startNewGame() noexcept {
    // Randomly generate a player and a target
    player_ = Player(playerImageIndex_, distrX_(r_), distrY_(r_), 30);
    target_ = ImageObject(targetImageIndex_, distrX_(r_), distrY_(r_), 20, 20, 0);
    // Clear the vectors of projectiles and walls
    projectiles_.clear();
    walls_.clear();
    // Randomly generate walls, only adding them if they
    // don't collide with the player or the target
    for (unsigned int i = 0; i < numWalls_; i += 1) {
        for (;;) {
            ImageObject w(wallImageIndex_, distrX_(r_), distrY_(r_), 10, distrX_(r_), distrA_(r_));
            if (!w.hits(target_) && !w.hits(player_)) {
                bool check = true;
                for (const ImageObject& wall : walls_) {
                    if (w.hits(wall)) {
                        check = false;
                    }
                }
                if (check) {
                    walls_.push_back(w);
                    break;
                }
            }
        }
    }
}
