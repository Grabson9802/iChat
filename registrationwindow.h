#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit RegistrationWindow(QWidget *parent = nullptr);

signals:
    void registrationComplete(const QString &username);

private slots:
    void onRegisterButtonClicked();

private:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *registerButton;
};

#endif // REGISTRATIONWINDOW_H
