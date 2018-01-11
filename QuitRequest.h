#ifndef QUITREQUEST_H
#define QUITREQUEST_H

#include <string>
#include "Request.h"

namespace deflection {

/**
 * User Quit Request.
 * @author Ken Baclawski
 */
class QuitRequest : virtual public Request {
public:
    /**
     * Default constructor.
     */
    QuitRequest();

    /** Destructor. */
    virtual ~QuitRequest();

    /** 
     * Whether the user asked the program to quit.
     * @return always true for this class.
     */
    virtual bool shouldQuit() const noexcept;
};

}

#endif
