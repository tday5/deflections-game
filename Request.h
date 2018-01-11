#ifndef REQUEST_H
#define REQUEST_H

#include <memory>

namespace deflection {

/**
 * User Request.  This is the abstract base class
 * of the user request hierarchy.
 *
 * @author Original: Ken Baclawski, Modifications By: Trevor Day
 */
class Request : virtual public std::enable_shared_from_this<Request> {
public:
    /**
     * Default constructor for invalid request.
     */
    Request();

    /**
     * Constructor specifying whether this request
     * is valid.
     */
    Request(/** Whether the request is valid. */
            bool isValid);

    /** Destructor. */
    virtual ~Request();

    /**
     * Whether this request is valid.
     * @return true if the request is valid.
     */
    virtual bool isValid() const noexcept;

    /** 
     * Whether the user asked the program to quit.
     * This is a pure virtual function.  Every
     * subclass must define this function.
     * @return true if the user asked to terminate
     * the program.
     */
    virtual bool shouldQuit() const noexcept = 0;

    /**
     * Whether the user asked the game to restart.
     * @return true if the user asked to restart the game.
     */
    virtual bool shouldRestart() const noexcept;

    /**
     * Whether the user pressed the left button.
     * @return true if the user pressed the left
     * button.
     */
    virtual bool pressedButton() const noexcept;

    /**
     * Whether the user released the left button.
     * @return true if the user released the left
     * button.
     */
    virtual bool releasedButton() const noexcept;

    /**
     * Get the x-coordinate of the mouse position.
     * @return The x-coordinate of the mouse
     * position if the left button is being pressed
     * or 0 otherwise.
     */
    virtual int xPosition() const noexcept;

    /**
     * Get the y-coordinate of the mouse position.
     * @return The y-coordinate of the mouse
     * position if the left button is being pressed
     * or 0 otherwise.
     */
    virtual int yPosition() const noexcept;

protected:
    /** Whether this request is valid. */
    bool isValid_ = false;

};

}

#endif
