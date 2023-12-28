#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    openDatabase();
    createUsersTable(); // Call this function to create the table when the database is opened
}

void DatabaseManager::createUsersTable() {
    QSqlQuery query;

    // SQL statement to create the users table
    const QString createTableQuery = "CREATE TABLE IF NOT EXISTS users ("
                                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                     "username TEXT NOT NULL UNIQUE, "
                                     "password TEXT NOT NULL)";

    if (query.exec(createTableQuery)) {
        qDebug() << "Users table created successfully!";
    } else {
        qDebug() << "Error creating users table:" << query.lastError().text();
    }
}

bool DatabaseManager::createUser(const QString &username, const QString &password) {
    // Check if the username already exists
    if (usernameExists(username)) {
        qDebug() << "Error: Username already exists!";
        return false;
    }

    QSqlQuery query;

    // Use a prepared statement to avoid SQL injection
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        qDebug() << "User created successfully!";
        return true;
    } else {
        qDebug() << "Error creating user:" << query.lastError().text();
        return false;
    }
}

bool DatabaseManager::usernameExists(const QString &username) {
    QSqlQuery query;

    // Use a prepared statement to avoid SQL injection
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", username);

    return query.exec() && query.next();
}

bool DatabaseManager::loginUser(const QString &username, const QString &password) {
    QSqlQuery query;

    // Use a prepared statement to avoid SQL injection
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        // If a row is returned, the login is successful
        qDebug() << "User login successful!";
        return true;
    } else {
        // No matching user found
        qDebug() << "User login failed:" << query.lastError().text();
        return false;
    }
}

void DatabaseManager::openDatabase() {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("iChatDB.db");

    if (!database.open()) {
        qDebug() << "Error: Unable to open database";
    }
}

void DatabaseManager::closeDatabase() {
    database.close();
}
