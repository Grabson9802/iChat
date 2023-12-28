#include "registrationwindow.h"
#include "databasemanager.h"

#include <QVBoxLayout>

RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("iChat - Registration");

    // Tworzenie elementów interfejsu użytkownika
    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("New username");

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("New password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    registerButton = new QPushButton("Register", this);

    messageLabel = new QLabel("");

    // Układanie elementów interfejsu użytkownika
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(registerButton);
    layout->addWidget(messageLabel);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    setCentralWidget(widget);

    // Połączenie sygnału i slotu dla przycisku rejestracji
    connect(registerButton, &QPushButton::clicked, this, &RegistrationWindow::onRegisterButtonClicked);
}

void RegistrationWindow::onRegisterButtonClicked() {
    // Pobieranie danych rejestracyjnych
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    DatabaseManager databaseManager;
    bool userIsCreated = databaseManager.createUser(username, password);

    if (userIsCreated) {
        // Zamknij okno rejestracji
        close();
    } else {
        messageLabel->setText("Username already exists!");
    }
}
