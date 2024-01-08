#include "contactlist.h"
#include "addcontactwindow.h"
#include "globalstate.h"

#include <QVBoxLayout>
#include <QMessageBox>

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
    connect(contactListWidget, &QListWidget::itemDoubleClicked, this, &ContactList::onContactDoubleClicked);

    loadContacts();
}

void ContactList::onContactDoubleClicked(QListWidgetItem *item) {
    QString contactUsername = item->text();
    QString currentUser = GlobalState::getInstance().getCurrentUser();

    // Prompt the user for confirmation or show a confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Delete Contact",
        "Are you sure you want to delete the contact: " + contactUsername + "?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        // User confirmed, remove the contact from the database
        if (databaseManager.removeContact(currentUser, contactUsername)) {
            // Successfully removed the contact from the database
            // Update the UI or take other actions as needed
            // ...

            // Remove the item from the QListWidget
            delete item;
        } else {
            // Failed to remove the contact, handle the error
            // ...
        }
    }
}

void ContactList::loadContacts() {
    QString username = GlobalState::getInstance().getCurrentUser();
    QStringList contacts = databaseManager.loadContacts(username);
    contactListWidget->clear();
    contactListWidget->addItems(contacts);
    qDebug() << "loadContacts()";
}

void ContactList::showAddContactWindow() {
    AddContactWindow *addContactWindow = new AddContactWindow();
    connect(addContactWindow, &AddContactWindow::refresh_user_list, this, &ContactList::contact_added);
    addContactWindow->show();
}

void ContactList::contact_added() {
    loadContacts();
}
void ContactList::addContact(const QString &contactUsername) {
    // Dodaj kontakt do listy
    QListWidgetItem *contactItem = new QListWidgetItem(contactUsername);
    contactListWidget->addItem(contactItem);
}
