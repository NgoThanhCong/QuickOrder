#include "usermodel.h"

UserModel::UserModel(QObject *parent) : IModel(parent)
{
    init();
}

UserModel::UserModel(const QString &name) : IModel(name)
{
    init();
}


void UserModel::init()
{

}

const QList<EntityUser *> &UserModel::users() const
{
    return m_users;
}

QVariantList UserModel::getUsers()
{
    QVariantList users;
    for(auto user : m_users){
        users.append(QVariant::fromValue<EntityUser*>(user));
    }
    return users;
}

void UserModel::setUsers(const QList<EntityUser *> &newUsers)
{
    if (m_users == newUsers)
        return;
    // Clear Old Data
    qDeleteAll(m_users);
    m_users.clear();

    // Fill data from database
    m_users.append(newUsers);
    emit usersChanged();
}
