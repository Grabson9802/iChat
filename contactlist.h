#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QMainWindow>
#include <QString>
#include <QListWidget>
#include <QPushButton>

class ContactList : public QMainWindow {
    Q_OBJECT
public:
    explicit ContactList(QWidget *parent = nullptr);

private slots:
    void addContact(const QString &contactUsername);

private:
    QListWidget *contactListWidget;
    QPushButton *addContactButton;
    QPushButton *closeButton;
};

#endif // CONTACTLIST_H
