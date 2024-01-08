#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include "databasemanager.h"
#include "addcontactwindow.h"

#include <QMainWindow>
#include <QString>
#include <QListWidget>
#include <QPushButton>

class ContactList : public QMainWindow {
    Q_OBJECT
public:
    explicit ContactList(QWidget *parent = nullptr);
public slots:
    void contact_added();
private:
    QListWidget *contactListWidget;
    QPushButton *addContactButton;
    QPushButton *closeButton;
    DatabaseManager databaseManager;
    void loadContacts();
    void showAddContactWindow();
    void onContactDoubleClicked(QListWidgetItem *item);
    void addContact(const QString &contactUsername);
};

#endif // CONTACTLIST_H
