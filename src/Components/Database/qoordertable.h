#ifndef QOORDERTABLE_H
#define QOORDERTABLE_H

#include <QObject>
#include <QDebug>
#include "sqlitetablebase.h"
#include "entity/entityorder.h"

class QOOrderTable : public SQLiteTableBase
{
    Q_OBJECT
public:
    explicit QOOrderTable(QObject *parent = nullptr);

    bool insert(const EntityOrder& eo);
    bool remove(const QString& id);
    int getNextId();
    QList<EntityOrder*> getAll();


};

#endif // QOORDERTABLE_H
