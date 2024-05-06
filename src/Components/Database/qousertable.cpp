#include "qousertable.h"

QOUserTable::QOUserTable(QObject *parent)
{

}

bool QOUserTable::insert(const EntityUser &user)
{
    QSqlQuery query;
    query.prepare("INSERT INTO USER_TABLE (user_type, name, dob, address, phone, "
                                          "user_name, password, avatar, hire_date) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(QVariant(user.userType()));
    query.addBindValue(QVariant(user.name()));
    query.addBindValue(QVariant(user.dob()));
    query.addBindValue(QVariant(user.adr()));
    query.addBindValue(QVariant(user.phone()));
    query.addBindValue(QVariant(user.userName()));
    query.addBindValue(QVariant(user.password()));
    query.addBindValue(QVariant(user.avatar()));
    query.addBindValue(QVariant(user.hireDate()));
    query.exec();
    qDebug() << query.lastError();
    return query.lastError().isValid();
}

bool QOUserTable::remove(const QString &userId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM USER_TABLE WHERE user_id=?");
    query.addBindValue(QVariant(userId));
    query.exec();
    qDebug() << query.lastError();
    return true;
}

bool QOUserTable::update(const EntityUser &user)
{
    QSqlQuery query;
    query.prepare("UPDATE USER_TABLE "
                  "SET dob = ?, "
                  "    address = ?, "
                  "    phone = ?, "
                  "    avatar = ?, "
                  "    hire_date = ?, "
                  "    name = ? "
                  "WHERE user_name = ?");

    query.addBindValue(QVariant(user.dob()));
    query.addBindValue(QVariant(user.adr()));
    query.addBindValue(QVariant(user.phone()));
    query.addBindValue(QVariant(user.avatar()));
    query.addBindValue(QVariant(user.hireDate()));
    query.addBindValue(QVariant(user.name()));
    query.addBindValue(QVariant(user.userName()));
    query.exec();
    qDebug() << query.lastError();
    return true;
}

QList<EntityUser *> QOUserTable::getAll()
{
    QList<EntityUser*> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM USER_TABLE");
    query.exec();
    while (query.next()) {
        EntityUser* user = new EntityUser();
        fillDataFromQuery(query, user);
        user->printDebug();
        res.append(user);
    }

    return res;
}

EntityUser *QOUserTable::getByUserName(const QString &id)
{
    qDebug() << __FUNCTION__ << id;
    EntityUser* res = nullptr;
    QSqlQuery que;
    que.prepare("SELECT * FROM USER_TABLE WHERE user_name=?");
    que.addBindValue(QVariant(id));
    que.exec();
    if(que.next()){
        res = new EntityUser();
        fillDataFromQuery(que, res);
        res->printDebug();
    }
    qCritical() << __FUNCTION__ << " : " << que.lastError().text() << " >< " << que.lastQuery();
    return res;
}

void QOUserTable::fillDataFromQuery(const QSqlQuery &src, EntityUser *dst)
{
    dst->setUserId(src.value("user_id").toInt());
    dst->setUserType(src.value("user_type").toInt());
    dst->setName(src.value("name").toString());
    dst->setDob(src.value("dob").toString());
    dst->setAdr(src.value("address").toString());
    dst->setPhone(src.value("phone").toString());
    dst->setUserName(src.value("user_name").toString());
    dst->setPassword(src.value("password").toString());
    dst->setAvatar(Utils.formatPathImage(src.value("avatar").toString()));
    dst->setHireDate(src.value("hire_date").toString());
}
