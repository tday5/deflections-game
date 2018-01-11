#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>
#include <memory>

#include "Display.h"
#include "Request.h"
#include "QuitRequest.h"
#include "ButtonRequest.h"
#include "RestartRequest.h"

using namespace std;
using namespace deflection;

Display::Display(int width, int height)
: width_(width), height_(height) {

    // Initialize SDL2

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw domain_error(string("SDL Initialization failed due to: ") + SDL_GetError());
    }

    // Construct the screen window

    window_ = SDL_CreateWindow("Display", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width_, height_, SDL_WINDOW_SHOWN);
    if (!window_) {
        close();
        throw domain_error(string("Unable to create the window due to: ") + SDL_GetError());
    }

    // Construct the renderer

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        close();
        throw domain_error(string("Unable to create the renderer due to: ") + SDL_GetError());
    }

    // Clear the window

    clearBackground();
}

Display::~Display() {
    close();
}

void Display::close() noexcept {

    // Delete the SDL2 resources in reverse order of
    // their construction, starting with the images

    for (SDL_Texture* image : images_) {
        if (image) {
            SDL_DestroyTexture(image);
        }
    }

    // Clear the collection of images to ensure
    // idempotence

    images_.clear();

    // Destroy the renderer and window, and set the
    // variables to nullptr to ensure idempotence

    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    // The last step is to quit SDL

    SDL_Quit();
}

int Display::addImage(const string& fileLocation) noexcept {
    if (renderer_) {

        // Load the image from the file

        SDL_Surface* imageSurface = SDL_LoadBMP(fileLocation.c_str());
        if (imageSurface) {

            // Convert the image to a texture

            SDL_Texture* imageTexture =
                    SDL_CreateTextureFromSurface(renderer_, imageSurface);
            if (imageTexture) {

                // Add the image to the collection

                images_.push_back(imageTexture);
            } else {
                cerr << "Unable to load the image file at " << fileLocation
                        << " due to: " << SDL_GetError() << endl;
            }

            // The surface is not longer needed

            SDL_FreeSurface(imageSurface);
            return images_.size() - 1;
        } else {
            cerr << "Unable to load the image file at " << fileLocation
                    << " due to: " << SDL_GetError() << endl;
        }
    }
    return -1;
}

unsigned int Display::getImageCount() const noexcept {
    return images_.size();
}

shared_ptr<Request> Display::getNextRequest() noexcept {

    // Remove one event from the queue

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {

        // The type determines what kind of request
        // occurred

        switch (event.type) {

                // The user Xed out the window

            case SDL_QUIT:
                close();
                return make_shared<QuitRequest>();

                // The user pressed a mouse button

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    const string title = "Fired towards: (" +
                            to_string(event.button.x) + ", " + to_string(event.button.y) + ")";
                    SDL_SetWindowTitle(window_, title.c_str());
                    return make_shared<ButtonRequest>(event.button.x, event.button.y, true);
                }
                break;

                // The user released a mouse button

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    return make_shared<ButtonRequest>(event.button.x, event.button.y, false);
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        SDL_SetWindowTitle(window_, "Level reset");
                        return make_shared<RestartRequest>();
                    default:
                        break;
                }
                break;

                // All other events are ignored

            default:
                break;
        }
    }
    return shared_ptr<Request>();
}

void Display::refresh(const vector<ImageObject>& images) {
    if (renderer_) {

        // Clear the window

        clearBackground();

        // Draw all of the ImageObjects

        for (const ImageObject& i : images) {

            // The location of the ImageObject is a square

            SDL_Rect destination = {i.getTopLeftXCoordinate(), i.getTopLeftYCoordinate(),
                i.getWidth(), i.getLength()};

            // Get the image index and check that it is valid

            unsigned int imageIndex = i.getImageIndex();
            if (imageIndex < images_.size()) {

                // Get the image for the ImageObject

                SDL_Texture* imageTexture = images_.at(imageIndex);
                if (imageTexture) {

                    // Render the image at the location,
                    // rotated by its angle

                    if (SDL_RenderCopyEx(renderer_, imageTexture, nullptr,
                            &destination, i.getAngle(),
                            nullptr, SDL_FLIP_NONE) != 0) {
                        close();
                        throw domain_error(string("Unable to render a ImageObject due to: ")
                                + SDL_GetError());
                    }
                } else {
                    close();
                    throw domain_error("Missing image texture at index "
                            + to_string(imageIndex));
                }
            } else {
                close();
                throw domain_error("Invalid image index "
                        + to_string(imageIndex));
            }
        }
        SDL_RenderPresent(renderer_);
    }
}

void Display::clearBackground() {
    if (renderer_) {

        // Clear the window to opaque white

        if (SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff) != 0) {
            close();
            throw domain_error(string("Unable to set the background color due to: ")
                    + SDL_GetError());
        }
        if (SDL_RenderClear(renderer_) != 0) {
            close();
            throw domain_error(string("Unable to set the background color due to: ")
                    + SDL_GetError());
        }
    }
}
