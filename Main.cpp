#include <cmath>
#include <iostream>
#include <stdexcept>

#include "ImageObject.h"
#include "Display.h"
#include "Request.h"
#include "ActiveGame.h"

using namespace std;
using namespace deflection;

/**
 * @namespace deflection The deflection package is a game where the player
 * must fire projectiles to attempt to hit a target before the projectiles disappear.
 * Projectiles disappear after bouncing off walls a certain number of times. Players
 * can specify the number of walls they would like in their game before they start.
 * Levels are randomly generated. They are not generated in a way that guarantees
 * they are winnable, and due to this players may generate a new level at any
 * time by pressing the space bar.
 *
 * @author Trevor Day
 */

/**
 * Main program for the deflection game.
 * @return The status code. Status code 0 means
 * the program succeeds, and nonzero status code
 * means the program failed.
 */
int main() {
    try {

        // Set up a temp variable to hold the number and prompt the player
        // to input a number
        int numWalls = 0;
        cout << "Please enter a number of walls, greater than zero and less than eleven:" << endl;

        // Keep reading inputs until one of them matches the necessary range
        while (cin >> numWalls) {
            if (numWalls >= 1 && numWalls <= 10) {
                break;
            }
        }

        // Initialize the graphical display
        Display display;

        // Add some images to the display
        int playerImageIndex = display.addImage("graphics/blue.bmp");
        int targetImageIndex = display.addImage("graphics/green.bmp");
        int wallImageIndex = display.addImage("graphics/black.bmp");
        int projectileImageIndex = display.addImage("graphics/red.bmp");

        // Start the game with the proper variables
        ActiveGame game(640, 480, playerImageIndex, targetImageIndex,
                wallImageIndex, projectileImageIndex, numWalls);
        
        // Keep track of the number of levels they have beaten
        int numLevelsBeaten = 0;

        // Run until quit.
        for (;;) {

            // Check all pending requests.
            for (;;) {
                shared_ptr<Request> request = display.getNextRequest();
                if (!request) {
                    break;
                }
                if (request->shouldQuit()) {
                    // Request to close the window
                    cout << "User closed the window" << endl;
                    return 0;
                } else if (request->shouldRestart()) {
                    // Request to reset the game
                    game.startNewGame();
                } else if (request->pressedButton()) {
                    // Pressed the left mouse button
                    game.playerFire(request->xPosition(), request->yPosition());
                }
            }

            // Update the state of the game and redraw the graphics, and
            // check if the game has been won
            game.updateState();
            display.refresh(game.getImagesToDraw());
            if (game.checkGameWon()) {
                // Increment levels beaten
                numLevelsBeaten += 1;
                // Output number of levels beaten
                cout << "Beat level! Number of levels beaten: " << numLevelsBeaten << endl;
                // Generate new level
                game.startNewGame();
            }
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
}
