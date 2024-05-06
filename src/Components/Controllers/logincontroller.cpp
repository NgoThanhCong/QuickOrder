#include "logincontroller.h"

LoginController::LoginController(QObject *parent) : IController(parent)
{
    m_userTable = new QOUserTable(this);
}

LoginController::LoginController(const QString &tag, QObject *parent) : IController(tag,parent)
{

}

void LoginController::handle_On_TitleBar_Changed(QString title)
{

}

void LoginController::login(const QString &id, const QString &pw)
{
    qDebug() << __FUNCTION__ << " - " << id  << " - " << pw;
    DatabaseManager* db = DatabaseManager::getInstance();
    LoginModel* model = getModel<LoginModel>();

    NavigationBarModel* modelNavi = getModel<NavigationBarModel>();
    if(!db->isConnected())
    {
        model->setIdWarning("[ERROR DB-001] DATABASE INTERNAL ERROR");
        return;
    }

    EntityUser* user = m_userTable->getByUserName(id);
    if(user == nullptr){
        model->setIdWarning("Username doesn't exist !");
        qCritical() << "ID not found";
    }else{
        bool isCorrectPw = comparePw(pw, user->password());
        if(!isCorrectPw) model->setPwWarning("Wrong Password !");
        model->setCurrentUser(user);
        model->setIsLogin(isCorrectPw);
    }

}

void LoginController::logout()
{
    LoginModel* model = getModel<LoginModel>();
    model->setIsLogin(false);
}

void LoginController::recoverPassword()
{
    qDebug() << __FUNCTION__;
}

void LoginController::syncData()
{
    qDebug() << "LoginController " << __FUNCTION__;
}

bool LoginController::comparePw(QString input, QString hash)
{
    QString hashInput = Misc::Utilities::getInstance().string2has(input);
    qDebug() << __FUNCTION__ << hash << " - " << hashInput;
    return (hash.compare(hashInput) == 0);
}
