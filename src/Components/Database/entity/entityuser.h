#ifndef ENTITYUSER_H
#define ENTITYUSER_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

class EntityUser : public QObject
{
    Q_OBJECT
public:
    explicit EntityUser(QObject *parent = nullptr);

    int userId() const;
    void setUserId(int newUserId);

    int userType() const;
    void setUserType(int newUserType);

    const QString &name() const;
    void setName(const QString &newName);

    const QString dob() const;
    void setDob(const QString &newDob);

    const QString &adr() const;
    void setAdr(const QString &newAdr);

    const QString &phone() const;
    void setPhone(const QString &newPhone);

    const QString &userName() const;
    void setUserName(const QString &newUserName);

    const QString &password() const;
    void setPassword(const QString &newPassword);

    const QString hireDate() const;
    void setHireDate(const QString &newHireDate);

    const QString &avatar() const;
    void setAvatar(const QString &newAvatar);

    void printDebug();

signals:
    void userIdChanged();

    void userTypeChanged();

    void nameChanged();

    void dobChanged();

    void adrChanged();

    void phoneChanged();

    void userNameChanged();

    void passwordChanged();

    void hireDateChanged();

    void avatarChanged();

private:
    int m_userId;
    int m_userType;
    QString m_name;
    QDateTime m_dob;
    QString m_adr;
    QString m_phone;
    QString m_userName;
    QString m_password;
    QString m_avatar;
    QDateTime m_hireDate;
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(int userType READ userType WRITE setUserType NOTIFY userTypeChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString dob READ dob WRITE setDob NOTIFY dobChanged)
    Q_PROPERTY(QString adr READ adr WRITE setAdr NOTIFY adrChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString hireDate READ hireDate WRITE setHireDate NOTIFY hireDateChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
};

#endif // ENTITYUSER_H
