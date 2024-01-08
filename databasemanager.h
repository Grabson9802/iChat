#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>

class DatabaseManager {
public:
    DatabaseManager();

    bool createUser(const QString &username, const QString &password);
    bool loginUser(const QString &username, const QString &password);
    bool addContact(const QString &username, const QString &contactUsername);
    bool removeContact(const QString &username, const QString &contactUsername);
    QStringList loadContacts(const QString &username);

private:
    QSqlDatabase database;

    void openDatabase();
    void closeDatabase();
    void createUsersTable();
    bool usernameExists(const QString &username);
    void createContactsTable();
    int getUserId(const QString &username);
    bool contactExists(int userId, int contactId);
};

#endif // DATABASEMANAGER_H
