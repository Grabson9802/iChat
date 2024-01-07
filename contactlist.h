#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include "databasemanager.h"

#include <QMainWindow>
#include <QString>
#include <QListWidget>
#include <QPushButton>

class ContactList : public QMainWindow {
    Q_OBJECT
public:
    explicit ContactList(QWidget *parent = nullptr);
private:
    QListWidget *contactListWidget;
    QPushButton *addContactButton;
    QPushButton *closeButton;
    DatabaseManager databaseManager;
    void loadContacts();
    void showAddContactWindow();
};

#endif // CONTACTLIST_H
