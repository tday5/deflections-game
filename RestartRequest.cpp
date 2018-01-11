#include "RestartRequest.h"

using namespace std;
using namespace deflection;

RestartRequest::RestartRequest() : Request(true) {
}

RestartRequest::~RestartRequest() {
}

bool RestartRequest::shouldQuit() const noexcept {
    return false;
}

bool RestartRequest::shouldRestart() const noexcept {
    return true;
}
