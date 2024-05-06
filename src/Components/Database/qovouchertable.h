#ifndef QOVOUCHERTABLE_H
#define QOVOUCHERTABLE_H

#include <QObject>
#include "sqlitetablebase.h"
#include "entity/entityvoucher.h"

class QOVoucherTable : public SQLiteTableBase
{
    Q_OBJECT
public:
    explicit QOVoucherTable(QObject *parent = nullptr);

    bool insert(const EntityVoucher& ev);
    bool remove(int id);
    bool updateStatus(EntityVoucher* ev);
    QList<EntityVoucher*> getAll();
    EntityVoucher* getVoucherByCode(const QString& code);

signals:

};

#endif // QOVOUCHERTABLE_H
