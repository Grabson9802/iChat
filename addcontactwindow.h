#ifndef ADDCONTACTWINDOW_H
#define ADDCONTACTWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class AddContactWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit AddContactWindow(QWidget *parent = nullptr);
signals:
    void refresh_user_list();
private:
    QLineEdit *usernameLineEdit;
    QPushButton *sendInvitationButton;
    void addContact();
};

#endif // ADDCONTACTWINDOW_H
