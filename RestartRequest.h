#ifndef RESTARTREQUEST_H
#define RESTARTREQUEST_H

#include "Request.h"

namespace deflection {

/**
 * Represents a user restart request, virtually derived from Request.
 * @author Trevor Day
 */
class RestartRequest : virtual public Request {
public:

    /**
     * Constructs a new RestartRequest.
     */
    RestartRequest();

    /**
     * Destructor.
     */
    virtual ~RestartRequest();

    /**
     * Whether the user asked the program to quit.
     * @return always false for this class.
     */
    virtual bool shouldQuit() const noexcept override;

    /**
     * Whether the user asked the game to restart.
     * @return always true for this class.
     */
    virtual bool shouldRestart() const noexcept override;
};
}

#endif /* RESTARTREQUEST_H */
