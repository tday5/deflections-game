#include "Request.h"
using namespace deflection;

Request::Request() {
}

Request::Request(bool isValid) : isValid_(isValid) {
}

Request::~Request() {
}

bool Request::isValid() const noexcept {
    return shared_from_this()->isValid_;
}

bool Request::shouldRestart() const noexcept {
    return false;
}

bool Request::pressedButton() const noexcept {
    return false;
}

bool Request::releasedButton() const noexcept {
    return false;
}

int Request::xPosition() const noexcept {
    return 0;
}

int Request::yPosition() const noexcept {
    return 0;
}
