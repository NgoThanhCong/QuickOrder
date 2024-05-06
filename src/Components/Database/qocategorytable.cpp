#include "qocategorytable.h"

QOCategoryTable::QOCategoryTable(QObject *parent) : SQLiteTableBase(parent)
{

}

bool QOCategoryTable::insert(const EntityCategory &category)
{
    QSqlQuery query;
    query.prepare("INSERT INTO CATEGORY_TABLE (name) "
                  "VALUES (?)");
    query.addBindValue(QVariant(category.name()));
    bool res = query.exec();
    qDebug() << query.lastError();
    return res;
}

bool QOCategoryTable::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CATEGORY_TABLE WHERE category_id=?");
    query.addBindValue(QVariant(id));
    bool res = query.exec();
    qDebug() << query.lastError();
    return res;
}

bool QOCategoryTable::update(const EntityCategory &category)
{
    QSqlQuery query;
    query.prepare("UPDATE CATEGORY_TABLE "
                  "SET name = ? "
                  "WHERE category_id = ?");
    query.addBindValue(QVariant(category.name()));
    query.addBindValue(QVariant(category.categoryId()));
    bool res = query.exec();
    qDebug() << query.lastError();
    return res;
}

QList<EntityCategory *> QOCategoryTable::getAll()
{
    QList<EntityCategory*> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM CATEGORY_TABLE");
    query.exec();
    while (query.next()) {
        EntityCategory* ec = new EntityCategory();
        ec->setCategoryId(query.value("category_id").toInt());
        ec->setName(query.value("name").toString());
        ec->printDebug();
        res.append(ec);
    }

    return res;
}
