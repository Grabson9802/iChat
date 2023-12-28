#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class RegistrationWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit RegistrationWindow(QWidget *parent = nullptr);

private slots:
    void onRegisterButtonClicked();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *registerButton;
    QLabel *messageLabel;
};

#endif // REGISTRATIONWINDOW_H
