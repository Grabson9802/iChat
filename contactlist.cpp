#include "contactlist.h"
#include "addcontactwindow.h"
#include "globalstate.h"

#include <QVBoxLayout>

ContactList::ContactList(QWidget *parent)
    : QMainWindow{parent} {

    setWindowTitle("Contact List");

    // Tworzenie elementów interfejsu użytkownika
    contactListWidget = new QListWidget(this);

    closeButton = new QPushButton("Close", this);
    addContactButton = new QPushButton("Add contact", this);

    // Układanie elementów interfejsu użytkownika
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(contactListWidget);
    layout->addWidget(addContactButton);
    layout->addWidget(closeButton);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    setCentralWidget(widget);

    // Połączenie sygnału i slotu dla przycisku zamknięcia
    connect(closeButton, &QPushButton::clicked, this, &ContactList::close);
    connect(addContactButton, &QPushButton::clicked, this, &ContactList::showAddContactWindow);
    loadContacts();
}

void ContactList::loadContacts() {
    QString username = GlobalState::getInstance().getCurrentUser();
    QStringList contacts = databaseManager.loadContacts(username);
    contactListWidget->clear();
    contactListWidget->addItems(contacts);
}

void ContactList::showAddContactWindow() {
    AddContactWindow *addContactWindow = new AddContactWindow();
    addContactWindow->show();
}
