#include "entityuser.h"

EntityUser::EntityUser(QObject *parent) : QObject(parent)
{

}

int EntityUser::userId() const
{
    return m_userId;
}

void EntityUser::setUserId(int newUserId)
{
    if (m_userId == newUserId)
        return;
    m_userId = newUserId;
    emit userIdChanged();
}

int EntityUser::userType() const
{
    return m_userType;
}

void EntityUser::setUserType(int newUserType)
{
    if (m_userType == newUserType)
        return;
    m_userType = newUserType;
    emit userTypeChanged();
}

const QString &EntityUser::name() const
{
    return m_name;
}

void EntityUser::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

const QString EntityUser::dob() const
{
    return m_dob.toString("dd/MM/yyyy");
}

void EntityUser::setDob(const QString &newDob)
{
    m_dob = QDateTime::fromString(newDob,"dd/MM/yyyy");
    emit dobChanged();
}

const QString &EntityUser::adr() const
{
    return m_adr;
}

void EntityUser::setAdr(const QString &newAdr)
{
    if (m_adr == newAdr)
        return;
    m_adr = newAdr;
    emit adrChanged();
}

const QString &EntityUser::phone() const
{
    return m_phone;
}

void EntityUser::setPhone(const QString &newPhone)
{
    if (m_phone == newPhone)
        return;
    m_phone = newPhone;
    emit phoneChanged();
}

const QString &EntityUser::userName() const
{
    return m_userName;
}

void EntityUser::setUserName(const QString &newUserName)
{
    if (m_userName == newUserName)
        return;
    m_userName = newUserName;
    emit userNameChanged();
}

const QString &EntityUser::password() const
{
    return m_password;
}

void EntityUser::setPassword(const QString &newPassword)
{
    if (m_password == newPassword)
        return;
    m_password = newPassword;
    emit passwordChanged();
}

const QString EntityUser::hireDate() const
{
    return m_hireDate.toString("dd/MM/yyyy");
}

void EntityUser::setHireDate(const QString &newHireDate)
{
    m_hireDate = QDateTime::fromString(newHireDate,"dd/MM/yyyy");;
    emit hireDateChanged();
}

const QString &EntityUser::avatar() const
{
    return m_avatar;
}

void EntityUser::setAvatar(const QString &newAvatar)
{
    if(newAvatar.isEmpty()){
        m_avatar = "qrc:/images/avt_dummy.png";
    }else{
        m_avatar = newAvatar;
    }
    emit avatarChanged();
}

void EntityUser::printDebug()
{
    qDebug() << m_name;
    qDebug() << m_dob;
    qDebug() << m_userName;
    qDebug() << m_password;

}
