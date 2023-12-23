#include "registrationwindow.h"

#include <QVBoxLayout>

RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Chat App - Rejestracja");

    // Tworzenie elementów interfejsu użytkownika
    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("Nowa nazwa użytkownika");

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Nowe hasło");
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    registerButton = new QPushButton("Zarejestruj", this);

    // Układanie elementów interfejsu użytkownika
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(registerButton);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    setCentralWidget(widget);

    // Połączenie sygnału i slotu dla przycisku rejestracji
    connect(registerButton, &QPushButton::clicked, this, &RegistrationWindow::onRegisterButtonClicked);
}

void RegistrationWindow::onRegisterButtonClicked()
{
    // Pobieranie danych rejestracyjnych
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    // Tutaj powinieneś dodać logikę rejestracji, np. zapis do bazy danych
    // Po zarejestrowaniu użytkownika, emituj sygnał informujący o zakończeniu rejestracji
    emit registrationComplete(username);

    // Zamknij okno rejestracji
    close();
}
