#include "qovouchertable.h"

QOVoucherTable::QOVoucherTable(QObject *parent) : SQLiteTableBase(parent)
{

}

bool QOVoucherTable::insert(const EntityVoucher &ev)
{
    QSqlQuery query;
    query.prepare("INSERT INTO VOUCHER_TABLE (voucher_code, valid_date, discount_value, status) "
                  "VALUES (?, ?, ? ,?)");
    query.addBindValue(QVariant(ev.voucherCode()));
    query.addBindValue(QVariant(ev.validDate()));
    query.addBindValue(QVariant(ev.discountValue()));
    query.addBindValue(QVariant(ev.status()));
    query.exec();
    qDebug() << query.lastError();
    return query.lastError().text().isEmpty();
}

bool QOVoucherTable::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM VOUCHER_TABLE WHERE voucher_id=?");
    query.addBindValue(QVariant(id));
    query.exec();
    qDebug() << query.lastError();
    return query.lastError().text().isEmpty();
}

bool QOVoucherTable::updateStatus(EntityVoucher* ev)
{
    QSqlQuery query;
    query.prepare("UPDATE VOUCHER_TABLE "
                  "SET status = ? "
                  "WHERE voucher_id = ?");
    query.addBindValue(QVariant(ev->status()));
    query.addBindValue(QVariant(ev->voucherId()));
    query.exec();
    qDebug() << query.lastError();
    return query.lastError().text().isEmpty();
}

QList<EntityVoucher *> QOVoucherTable::getAll()
{
    QList<EntityVoucher*> res;
    QSqlQuery query;
    query.prepare("SELECT * FROM VOUCHER_TABLE");
    query.exec();
    while (query.next()) {
        if(query.value("voucher_id").toInt() == 0) continue;
        EntityVoucher* ev = new EntityVoucher();
        ev->setVoucherId(query.value("voucher_id").toInt());
        ev->setStatus(query.value("status").toInt());
        ev->setVoucherCode(query.value("voucher_code").toString());
        ev->setValidDate(query.value("valid_date").toString());
        ev->setDiscountValue(query.value("discount_value").toInt());

        ev->printDebug();
        res.append(ev);
    }

    return res;
}

EntityVoucher *QOVoucherTable::getVoucherByCode(const QString &code)
{
    qDebug() << __FUNCTION__ << code;
    EntityVoucher* ev = nullptr;
    QSqlQuery query;
    query.prepare("SELECT * FROM VOUCHER_TABLE WHERE voucher_code=?");
    query.addBindValue(QVariant(code));
    query.exec();
    if(query.next()){
        ev = new EntityVoucher();
        ev->setVoucherId(query.value("voucher_id").toInt());
        ev->setStatus(query.value("status").toInt());
        ev->setVoucherCode(query.value("voucher_code").toString());
        ev->setValidDate(query.value("valid_date").toString());
        ev->setDiscountValue(query.value("discount_value").toInt());
    }
    qCritical() << __FUNCTION__ << " : " << query.lastError().text() << " >< " << query.lastQuery();
    return ev;
}
