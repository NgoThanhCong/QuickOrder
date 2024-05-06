#include "qomenuitemtable.h"

QOMenuItemTable::QOMenuItemTable(QObject *parent) : SQLiteTableBase(parent)
{

}

bool QOMenuItemTable::insert(const EntityMenuItem &emi)
{
    QSqlQuery query;
    query.prepare("INSERT INTO MENU_TABLE (name, description, category_id, image, price, price_medium, price_large) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(QVariant(emi.name()));
    query.addBindValue(QVariant(emi.description()));
    query.addBindValue(QVariant(emi.categoryId()));
    query.addBindValue(QVariant(emi.image()));
    query.addBindValue(QVariant(emi.price()));
    query.addBindValue(QVariant(emi.priceM()));
    query.addBindValue(QVariant(emi.priceL()));

    bool res = query.exec();
    qDebug() << query.lastError();
    return res;
}

bool QOMenuItemTable::remove(const int &id)
{
    qDebug() << "Remove Menu Item: " <<id;
    QSqlQuery query;
    query.prepare("DELETE FROM MENU_TABLE WHERE item_id=?");
    query.addBindValue(QVariant(id));
    bool res = query.exec();
    qDebug() << query.lastError();
    return res;
}

bool QOMenuItemTable::update(const EntityMenuItem &emi)
{
    QSqlQuery query;
    query.prepare("UPDATE MENU_TABLE "
                  "SET name = ?, "
                  "    category_id = ?, "
                  "    description = ?, "
                  "    image = ?, "
                  "    price = ?, "
                  "    price_medium = ?, "
                  "    price_large = ? "
                  "WHERE item_id = ?");

    query.addBindValue(QVariant(emi.name()));
    query.addBindValue(QVariant(emi.categoryId()));
    query.addBindValue(QVariant(emi.description()));
    query.addBindValue(QVariant(emi.image()));
    query.addBindValue(QVariant(emi.price()));
    query.addBindValue(QVariant(emi.priceM()));
    query.addBindValue(QVariant(emi.priceL()));
    query.addBindValue(QVariant(emi.itemId()));

    query.exec();
    qDebug() << query.lastError();
    return query.lastError().text().isEmpty();
}

bool QOMenuItemTable::removeByCatId(int catId)
{
    qDebug() << "Remove Menu Item By CatID: " <<catId;
    QSqlQuery query;
    query.prepare("DELETE FROM MENU_TABLE WHERE category_id=?");
    query.addBindValue(QVariant(catId));

    bool res = query.exec();
    qDebug() << query.lastError();
    return res;
}

EntityMenuItem *QOMenuItemTable::getMenuItemById(int id)
{
    qDebug() << __FUNCTION__ << id;
    EntityMenuItem* ec = nullptr;
    QSqlQuery query;
    query.prepare("SELECT * FROM MENU_TABLE WHERE item_id=?");
    query.addBindValue(QVariant(id));
    query.exec();
    if(query.next()){
        ec = new EntityMenuItem();
        ec->setItemId(query.value("item_id").toInt());
        ec->setName(query.value("name").toString());
        ec->setDescription(query.value("description").toString());
        ec->setCategoryId(query.value("category_id").toInt());
        ec->setImage(Utils.formatPathImage(query.value("image").toString()));
        ec->setPrice(query.value("price").toFloat());
        ec->setPriceM(query.value("price_medium").toFloat());
        ec->setPriceL(query.value("price_large").toFloat());
        ec->printDebug();
    }
    qCritical() << __FUNCTION__ << " : " << query.lastError().text() << " >< " << query.lastQuery();
    return ec;
}

QList<EntityMenuItem *> QOMenuItemTable::getAll()
{
    QList<EntityMenuItem*> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM MENU_TABLE");
    query.exec();
    while (query.next()) {
        EntityMenuItem* ec = new EntityMenuItem();
        ec->setItemId(query.value("item_id").toInt());
        ec->setName(query.value("name").toString());
        ec->setDescription(query.value("description").toString());
        ec->setCategoryId(query.value("category_id").toInt());
        ec->setImage(Utils.formatPathImage(query.value("image").toString()));
        ec->setPrice(query.value("price").toFloat());
        ec->setPriceM(query.value("price_medium").toFloat());
        ec->setPriceL(query.value("price_large").toFloat());

        ec->printDebug();
        res.append(ec);
    }

    return res;
}
