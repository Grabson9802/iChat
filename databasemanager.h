#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>

class DatabaseManager {
public:
    DatabaseManager();

    bool createUser(const QString &username, const QString &password);
    bool loginUser(const QString &username, const QString &password);

private:
    QSqlDatabase database;

    void openDatabase();
    void closeDatabase();
    void createUsersTable();
    bool usernameExists(const QString &username);
};

#endif // DATABASEMANAGER_H
