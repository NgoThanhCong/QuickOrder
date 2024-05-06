#include "usercontroller.h"

UserController::UserController(QObject *parent) : IController(parent)
{

}

UserController::UserController(const QString &tag, QObject *parent) : IController(tag,parent)
{
    m_userTable = new QOUserTable(this);
}

void UserController::removeUser(QString id)
{
    m_userTable->remove(id);
    syncData();
}

void UserController::addUser(QString name, QString dob, QString address, QString phone, QString userName, QString password, QString avatar, QString hireDate)
{
    EntityUser user;
    user.setName(name);
    user.setUserType(1); //Staff
    user.setDob(dob);
    user.setAdr(address);
    user.setPhone(phone);
    user.setUserName(userName);
    user.setPassword(Misc::Utilities::getInstance().string2has(password));
    if(avatar != "qrc:/images/avt_dummy.png"){
        avatar = storeImage(avatar);
        qDebug() << "Image is stored:" << avatar;
    }
    user.setAvatar(avatar);
    user.setHireDate(hireDate);
    m_userTable->insert(user);
}

bool UserController::updateUser(QString userName, QString name, QString dob, QString address, QString phone, QString hireDate, QString avatar)
{
    EntityUser* user = m_userTable->getByUserName(userName);
    if(user){
        user->setName(name);
        user->setDob(dob);
        user->setAdr(address);
        user->setPhone(phone);
        user->setHireDate(hireDate);
        if(avatar != "qrc:/images/avt_dummy.png"){
            avatar = storeImage(avatar);
            qDebug() << "Image is stored:" << avatar;
        }
        user->setAvatar(avatar);
        bool res = m_userTable->update(*user);
        delete user;
        return res;
    }else{
        qDebug() << "[USER UPDATE] USER NAME DOES NOT EXIST !";
        return false;
    }
}

void UserController::syncData()
{
    qDebug() << "[User Syncing]";
    UserModel* model = getModel<UserModel>();
    model->setUsers(m_userTable->getAll());
}

bool UserController::checkUserNameExisted(QString userName)
{
    EntityUser* user = m_userTable->getByUserName(userName);
    bool isExisted = (user == nullptr);
    delete user;
    return isExisted;
}
