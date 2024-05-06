#include "qoorderitemtable.h"

QOOrderItemTable::QOOrderItemTable(QObject *parent) : SQLiteTableBase(parent)
{

}

bool QOOrderItemTable::insert(const EntityOrderItem &eoi)
{
    QSqlQuery query;
    query.prepare("INSERT INTO ORDER_ITEMS_TABLE (order_id, item_id, quantity, item_size) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(QVariant(eoi.orderId()));
    query.addBindValue(QVariant(eoi.itemId()));
    query.addBindValue(QVariant(eoi.quantity()));
    query.addBindValue(QVariant(eoi.itemSize()));
    query.exec();
    qDebug() << query.lastError();
    return query.lastError().text().isEmpty();
}

bool QOOrderItemTable::remove(const QString &id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ORDER_ITEMS_TABLE WHERE order_item_id=?");
    query.addBindValue(QVariant(id));
    query.exec();
    qDebug() << query.lastError();
    return query.lastError().text().isEmpty();
}

QList<EntityOrderItem *> QOOrderItemTable::getAll()
{
    QList<EntityOrderItem*> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM ORDER_ITEMS_TABLE");
    query.exec();
    while (query.next()) {
        EntityOrderItem* eoi = new EntityOrderItem();
        eoi->setOrderItemId(query.value("order_item_id").toInt());
        eoi->setItemId(query.value("order_id").toInt());
        eoi->setItemId(query.value("item_id").toInt());
        eoi->setQuantity(query.value("quantity").toInt());
        eoi->printDebug();
        res.append(eoi);
    }

    return res;
}
