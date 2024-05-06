#ifndef QOMENUITEMTABLE_H
#define QOMENUITEMTABLE_H

#include <QObject>
#include "sqlitetablebase.h"
#include "entity/entitymenuitem.h"

class QOMenuItemTable : public SQLiteTableBase
{
    Q_OBJECT
public:
    explicit QOMenuItemTable(QObject *parent = nullptr);

    bool insert(const EntityMenuItem& emi);
    bool remove(const int& id);
    bool update(const EntityMenuItem& emi);
    bool removeByCatId(int catId);

    EntityMenuItem* getMenuItemById(int id);
    QList<EntityMenuItem*> getAll();

};

#endif // QOMENUITEMTABLE_H
