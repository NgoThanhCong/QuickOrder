#ifndef LOGINMODEL_H
#define LOGINMODEL_H
#include "imodel.h"
#include "../Database/entity/entityuser.h"

class LoginModel : public IModel
{
    Q_OBJECT
public:
    explicit LoginModel();
    LoginModel(const QString& name);
    ~LoginModel();
    void init();

    const QString &projectName() const;
    void setProjectName(const QString &newProjectName);

    const QString &idWarning() const;
    void setIdWarning(const QString &newIdWarning);

    const QString &pwWarning() const;
    void setPwWarning(const QString &newPwWarning);

    bool isLogin() const;
    void setIsLogin(bool newIsLogin);

    EntityUser *currentUser() const;
    void setCurrentUser(EntityUser *newCurrentUser);

signals:
    void projectNameChanged();

    void idWarningChanged();

    void pwWarningChanged();

    void isLoginChanged();

    void currentUserChanged();

public slots:
    bool isAdmin();

private:
    QString m_projectName;
    QString m_idWarning;
    QString m_pwWarning;
    bool m_isLogin;
    EntityUser* m_currentUser;


    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
    Q_PROPERTY(QString idWarning READ idWarning WRITE setIdWarning NOTIFY idWarningChanged)
    Q_PROPERTY(QString pwWarning READ pwWarning WRITE setPwWarning NOTIFY pwWarningChanged)
    Q_PROPERTY(bool isLogin READ isLogin WRITE setIsLogin NOTIFY isLoginChanged)
    Q_PROPERTY(EntityUser * currentUser READ currentUser WRITE setCurrentUser NOTIFY currentUserChanged)
};

#endif // LOGINMODEL_H
