#include "qoordertable.h"

QOOrderTable::QOOrderTable(QObject *parent) : SQLiteTableBase(parent)
{

}

bool QOOrderTable::insert(const EntityOrder &eo)
{
    QSqlQuery query;
    query.prepare("INSERT INTO ORDER_TABLE (order_id, order_date_time, total_amount, "
                  "voucher_id, user_id, cash, change)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(QVariant(eo.orderId()));
    query.addBindValue(QVariant(eo.orderDateTime()));
    query.addBindValue(QVariant(eo.totalAmount()));
    query.addBindValue(QVariant(eo.voucherId()));
    query.addBindValue(QVariant(eo.userId()));
    query.addBindValue(QVariant(eo.cash()));
    query.addBindValue(QVariant(eo.change()));

    query.exec();
    qDebug() << query.lastError();
    return query.lastError().text().isEmpty();
}

bool QOOrderTable::remove(const QString &id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ORDER_TABLE WHERE order_id=?");
    query.addBindValue(QVariant(id));
    query.exec();
    qDebug() << query.lastError();
    return query.lastError().text().isEmpty();
}

int QOOrderTable::getNextId()
{
    int res = 0;
    QSqlQuery query;
    query.prepare("SELECT order_id FROM ORDER_TABLE ORDER BY order_id DESC LIMIT 1");
    query.exec();
    if(query.next()){
        res = query.value("order_id").toInt() + 1;
    }
    qDebug() << query.lastError();
    return res;
}

QList<EntityOrder *> QOOrderTable::getAll()
{
    QList<EntityOrder*> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM CATEGORY_TABLE");
    query.exec();
    while (query.next()) {
        EntityOrder* eo = new EntityOrder();
        eo->setOrderId(query.value("order_id").toInt());
        eo->setOrderDateTime(query.value("order_date_time").toString());
        eo->setTotalAmount(query.value("total_amount").toFloat());
        eo->setVoucherId(query.value("voucher_id").toInt());
        eo->setUserId(query.value("user_id").toInt());
        eo->setCash(query.value("cash").toFloat());
        eo->setChange(query.value("change").toFloat());
        eo->printDebug();

        res.append(eo);
    }

    return res;
}
