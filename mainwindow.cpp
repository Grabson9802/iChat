#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    // Układanie elementów interfejsu użytkownika
    QBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);
    layout->addWidget(messageLabel);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    setCentralWidget(widget);

    // Połączenie sygnału i slotu dla przycisku logowania
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoginButtonClicked() {
    // Tutaj powinieneś dodać logikę weryfikacji danych logowania
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if (username == "username" && password == "password") {
        // Successful login
        messageLabel->setText("Logged in successfully!");
    } else {
        // Login error
        messageLabel->setText("Login failed. Please try again.");
    }
}
