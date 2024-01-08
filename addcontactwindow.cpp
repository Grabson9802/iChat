#include "addcontactwindow.h"

#include "databasemanager.h"
#include "globalstate.h"

#include <QVBoxLayout>

AddContactWindow::AddContactWindow(QWidget *parent)
    : QMainWindow{parent} {

    usernameLineEdit = new QLineEdit();
    usernameLineEdit->setPlaceholderText("Type username to add");

    sendInvitationButton = new QPushButton("Send invitation", this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(usernameLineEdit);
    layout->addWidget(sendInvitationButton);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    setCentralWidget(widget);

    connect(sendInvitationButton, &QPushButton::clicked, this, &AddContactWindow::addContact);
}

void AddContactWindow::addContact() {
    QString usernameToAdd = usernameLineEdit->text();
    QString userLogged = GlobalState::getInstance().getCurrentUser();
    DatabaseManager databaseManager;
    bool successfullyAdded = databaseManager.addContact(userLogged, usernameToAdd);

    if(successfullyAdded) {
        refresh_user_list();
        close();
    }
}
