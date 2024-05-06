#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "icontroller.h"
#include "../Database/qousertable.h"

class UserController : public IController
{
    Q_OBJECT
public:
    explicit UserController(QObject *parent = nullptr);
    UserController(const QString &tag, QObject* parent = nullptr);

public slots:
    void removeUser(QString id);
    void addUser(QString name, QString dob, QString address, QString phone,
                 QString userName, QString password, QString avatar, QString hireDate);

    bool updateUser(QString userName, QString name, QString dob, QString address,
                    QString phone, QString hireDate, QString avatar);

    void syncData();
    bool checkUserNameExisted(QString userName);

private:
    QOUserTable* m_userTable;
};

#endif // USERCONTROLLER_H
