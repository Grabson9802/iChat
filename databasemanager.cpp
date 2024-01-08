#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    openDatabase();
    createUsersTable(); // Call this function to create the table when the database is opened
    createContactsTable();  // Create contacts table
}

bool DatabaseManager::removeContact(const QString &username, const QString &contactUsername) {
    // Get user IDs for the provided usernames
    int userId = getUserId(username);
    int contactId = getUserId(contactUsername);

    if (userId == -1 || contactId == -1) {
        qDebug() << "Error: User or contact not found!";
        return false;
    }

    QSqlQuery query;

    // Use a prepared statement to avoid SQL injection
    query.prepare("DELETE FROM contacts WHERE user_id = :user_id AND contact_id = :contact_id");
    query.bindValue(":user_id", userId);
    query.bindValue(":contact_id", contactId);

    if (query.exec()) {
        qDebug() << "Contact removed successfully!";
        return true;
    } else {
        qDebug() << "Error removing contact:" << query.lastError().text();
        return false;
    }
}

QStringList DatabaseManager::loadContacts(const QString &username) {
    QStringList contacts;

    // Get user ID for the provided username
    int userId = getUserId(username);

    if (userId == -1) {
        qDebug() << "Error: User not found!";
        return contacts;
    }

    QSqlQuery query;

    // Use a prepared statement to avoid SQL injection
    query.prepare("SELECT u.username "
                  "FROM contacts c "
                  "JOIN users u ON c.contact_id = u.id "
                  "WHERE c.user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (query.exec()) {
        while (query.next()) {
            // Add each contact username to the list
            contacts.append(query.value("username").toString());
        }
    } else {
        qDebug() << "Error loading contacts:" << query.lastError().text();
    }

    return contacts;
}

void DatabaseManager::createContactsTable() {
    QSqlQuery query;

    // SQL statement to create the contacts table
    const QString createTableQuery = "CREATE TABLE IF NOT EXISTS contacts ("
                                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                     "user_id INTEGER, "
                                     "contact_id INTEGER, "
                                     "FOREIGN KEY(user_id) REFERENCES users(id), "
                                     "FOREIGN KEY(contact_id) REFERENCES users(id))";

    if (query.exec(createTableQuery)) {
        qDebug() << "Contacts table created successfully!";
    } else {
        qDebug() << "Error creating contacts table:" << query.lastError().text();
    }
}

bool DatabaseManager::addContact(const QString &username, const QString &contactUsername) {
    // Get user IDs for the provided usernames
    int userId = getUserId(username);
    int contactId = getUserId(contactUsername);

    if (userId == -1 || contactId == -1) {
        qDebug() << "Error: User or contact not found!";
        return false;
    }

    // Check if the contact already exists
    if (contactExists(userId, contactId)) {
        qDebug() << "Error: Contact already exists!";
        return false;
    }

    QSqlQuery query;

    // Use a prepared statement to avoid SQL injection
    query.prepare("INSERT INTO contacts (user_id, contact_id) VALUES (:user_id, :contact_id)");
    query.bindValue(":user_id", userId);
    query.bindValue(":contact_id", contactId);

    if (query.exec()) {
        qDebug() << "Contact added successfully!";
        return true;
    } else {
        qDebug() << "Error adding contact:" << query.lastError().text();
        return false;
    }
}

int DatabaseManager::getUserId(const QString &username) {
    QSqlQuery query;

    // Use a prepared statement to avoid SQL injection
    query.prepare("SELECT id FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        return query.value("id").toInt();
    } else {
        return -1;  // User not found
    }
}

bool DatabaseManager::contactExists(int userId, int contactId) {
    QSqlQuery query;

    // Use a prepared statement to avoid SQL injection
    query.prepare("SELECT * FROM contacts WHERE user_id = :user_id AND contact_id = :contact_id");
    query.bindValue(":user_id", userId);
    query.bindValue(":contact_id", contactId);

    return query.exec() && query.next();
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
