#include "contactlist.h"

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
}

void ContactList::addContact(const QString &contactUsername) {
    // Dodaj kontakt do listy
    QListWidgetItem *contactItem = new QListWidgetItem(contactUsername);
    contactListWidget->addItem(contactItem);
}
