#ifndef GLOBALSTATE_H
#define GLOBALSTATE_H

#include <QString>

class GlobalState {
public:
    static GlobalState& getInstance();

    QString getCurrentUser() const;
    void setCurrentUser(const QString &username);

private:
    GlobalState();  // Private constructor to enforce singleton pattern
    QString currentUser;
};

#endif // GLOBALSTATE_H
