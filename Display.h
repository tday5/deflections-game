#ifndef DEFLECTION_DISPLAY_H
#define DEFLECTION_DISPLAY_H

#include <memory>
#include "ImageObject.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

namespace deflection {

class Request;

/**
 * SDL Display. The purpose of this class is to
 * encapsulate all uses of SDL2 by this program.
 * Note that SDL.h was not included so that other
 * classes will not have direct access to SDL2.
 * All uses of SDL2 must be made through this
 * class.
 *
 * @author Original: Ken Baclawski, Modifications By: Trevor Day
 */
class Display {
public:
    /**
     * Create a graphical display with specified size.
     * @throw domain_error if the display could not
     * be created and initialized.
     */
    Display(/** Display width. */ int width = 640,
            /** Display height. */ int height = 480);

    /**
     * Destruct the graphical display.  This closes
     * the display.
     */
    ~Display();

    /**
     * Close the graphical display and release the
     * resources.
     */
    void close() noexcept;

    /**
     * Add an image to the collection.
     */
    int addImage(/** The location of the file. */
            const std::string& fileLocation) noexcept;

    /**
     * Get the number of images.
     */
    unsigned int getImageCount() const noexcept;

    /**
     * Get the next request from the user.  If quit
     * is requested, the display is closed and
     * deleted.  If a button is pressed, then the
     * window title is changed.
     * @return The request event that occurred or
     * null if no event occurred.  
     */
    std::shared_ptr<Request> getNextRequest() noexcept;

    /**
     * Refresh the display.
     * @throw domain_error if the display could not
     * be refreshed.
     */
    void refresh(/** The ImageObjects to display. */
            const std::vector<ImageObject>& images);

private:
    /** The display window. */
    SDL_Window* window_ = nullptr;

    /** The display rendering tool. */
    SDL_Renderer* renderer_ = nullptr;

    /** The collection of images. */
    std::vector<SDL_Texture*> images_;

    /** The width of the window. */
    const int width_ = 0;

    /** The height of the window. */
    const int height_ = 0;

    /**
     * Clear the background to opaque white.
     */
    void clearBackground();
};

}

#endif
