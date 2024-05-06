#include "loginmodel.h"

LoginModel::LoginModel()
{
    init();
}

LoginModel::LoginModel(const QString &name) : IModel(name), m_currentUser(nullptr)
{
    init();
}

LoginModel::~LoginModel()
{
    if(m_currentUser != nullptr){
        delete m_currentUser;
        m_currentUser = nullptr;
    }
}

void LoginModel::init()
{
    m_isLogin = false;
}

const QString &LoginModel::projectName() const
{
    return m_projectName;
}

void LoginModel::setProjectName(const QString &newProjectName)
{
    if (m_projectName == newProjectName)
        return;
    m_projectName = newProjectName;
    emit projectNameChanged();
}

const QString &LoginModel::idWarning() const
{
    return m_idWarning;
}

void LoginModel::setIdWarning(const QString &newIdWarning)
{
    m_idWarning = newIdWarning;
    emit idWarningChanged();
}

const QString &LoginModel::pwWarning() const
{
    return m_pwWarning;
}

void LoginModel::setPwWarning(const QString &newPwWarning)
{
    if (m_pwWarning == newPwWarning)
        return;
    m_pwWarning = newPwWarning;
    emit pwWarningChanged();
}

bool LoginModel::isLogin() const
{
    return m_isLogin;
}

void LoginModel::setIsLogin(bool newIsLogin)
{
    if (m_isLogin == newIsLogin)
        return;
    m_isLogin = newIsLogin;
    emit isLoginChanged();
}

EntityUser *LoginModel::currentUser() const
{
    return m_currentUser;
}

void LoginModel::setCurrentUser(EntityUser *newCurrentUser)
{
    if (m_currentUser == newCurrentUser)
        return;
    m_currentUser = newCurrentUser;
    emit currentUserChanged();
}

bool LoginModel::isAdmin()
{
    if(m_currentUser != nullptr){
        return m_currentUser->userType() == 0;
    }
    return false;
}
