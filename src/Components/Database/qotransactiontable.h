#ifndef QOTRANSACTIONTABLE_H
#define QOTRANSACTIONTABLE_H

#include <QObject>
#include "sqlitetablebase.h"
#include "entity/entitytransaction.h"

class QOTransactionTable : public SQLiteTableBase
{
    Q_OBJECT
public:
    explicit QOTransactionTable(QObject *parent = nullptr);

    bool insert(const EntityTransaction& trans);
    bool remove(const QString& id);
    QList<EntityTransaction*> getAll();

};

#endif // QOTRANSACTIONTABLE_H
