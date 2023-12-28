#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "registrationwindow.h"
#include "contactlist.h"
#include "databasemanager.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    setWindowTitle("iChat - Log in");

    // Tworzenie elementów interfejsu użytkownika
    usernameLineEdit = new QLineEdit();
    usernameLineEdit->setPlaceholderText("Username");

    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setPlaceholderText("Password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Log in", this);

    messageLabel = new QLabel("", this);

    registerButton = new QPushButton("Register", this);

    // Układanie elementów interfejsu użytkownika
    QBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);
    layout->addWidget(messageLabel);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    setCentralWidget(widget);

    // Połączenie sygnału i slotu dla przycisku logowania
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &MainWindow::onRegisterButtonClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onLoginButtonClicked() {
    // Tutaj powinieneś dodać logikę weryfikacji danych logowania
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    DatabaseManager databaseManager;
    bool userExist = databaseManager.loginUser(username, password);

    if (userExist) {
        // Successful login
        messageLabel->setText("Logged in successfully!");

        ContactList *contactList = new ContactList(this);
        contactList->show();
    } else {
        // Login error
        messageLabel->setText("Login failed. Please try again.");
    }
}

void MainWindow::onRegisterButtonClicked() {
    // Otwórz nowe okno rejestracji
    RegistrationWindow *registrationWindow = new RegistrationWindow(this);
    registrationWindow->show();
}
