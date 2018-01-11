#include <string>
#include "QuitRequest.h"
using namespace deflection;

QuitRequest::QuitRequest() : Request(true) {
}

QuitRequest::~QuitRequest() {
}

bool QuitRequest::shouldQuit() const noexcept {
    return true;
}
