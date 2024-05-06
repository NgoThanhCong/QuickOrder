#ifndef QOORDERITEMTABLE_H
#define QOORDERITEMTABLE_H

#include <QObject>
#include "sqlitetablebase.h"
#include "entity/entityorderitem.h"

class QOOrderItemTable : public SQLiteTableBase
{
    Q_OBJECT
public:
    explicit QOOrderItemTable(QObject *parent = nullptr);

    bool insert(const EntityOrderItem& eoi);
    bool remove(const QString& id);
    QList<EntityOrderItem*> getAll();


private:

};

#endif // QOORDERITEMTABLE_H
