#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include "imodel.h"
#include "../Database/entity/entityuser.h"

class UserModel : public IModel
{
    Q_OBJECT
public:
    explicit UserModel(QObject *parent = nullptr);
    UserModel(const QString& name);

    const QList<EntityUser *> &users() const;
    QVariantList getUsers();
    void setUsers(const QList<EntityUser *> &newUsers);

signals:
    void usersChanged();

private:
    void init();

    QList<EntityUser*> m_users;
    Q_PROPERTY(QVariantList users READ getUsers NOTIFY usersChanged)
};

#endif // USERMODEL_H
