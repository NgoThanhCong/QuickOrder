#include "qotransactiontable.h"

QOTransactionTable::QOTransactionTable(QObject *parent) : SQLiteTableBase(parent)
{

}

bool QOTransactionTable::insert(const EntityTransaction &trans)
{
    QSqlQuery query;
    query.prepare("INSERT INTO TRANSACTION_TABLE (order_id, payment_method, amount) "
                  "VALUES (?, ?, ?)");
    query.addBindValue(QVariant(trans.order_id()));
    query.addBindValue(QVariant(trans.payment_method()));
    query.addBindValue(QVariant(trans.amount()));
    query.exec();
    qDebug() << query.lastError();
    return query.lastError().text().isEmpty();
}

bool QOTransactionTable::remove(const QString &id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM TRANSACTION_TABLE WHERE transaction_id=?");
    query.addBindValue(QVariant(id));
    query.exec();
    qDebug() << query.lastError();
    return query.lastError().text().isEmpty();
}

QList<EntityTransaction *> QOTransactionTable::getAll()
{
    QList<EntityTransaction*> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM TRANSACTION_TABLE");
    while (query.next()) {
        EntityTransaction* et = new EntityTransaction();
        et->setTransactionId(query.value("transaction_id").toInt());
        et->setOrder_id(query.value("order_id").toInt());
        et->setPayment_method(query.value("payment_method").toInt());
        et->setAmount(query.value("amount").toFloat());
        et->printDebug();
        res.append(et);
    }
    return res;
}
