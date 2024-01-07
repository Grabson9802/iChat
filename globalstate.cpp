#include "globalstate.h"

GlobalState& GlobalState::getInstance() {
    static GlobalState instance;
    return instance;
}

GlobalState::GlobalState() {
    // Initialize any necessary state in the constructor
}

QString GlobalState::getCurrentUser() const {
    return currentUser;
}

void GlobalState::setCurrentUser(const QString &username) {
    currentUser = username;
}
