#ifndef QOCATEGORYTABLE_H
#define QOCATEGORYTABLE_H

#include <QObject>
#include "sqlitetablebase.h"
#include "entity/entitycategory.h"

class QOCategoryTable : public SQLiteTableBase
{
    Q_OBJECT
public:
    explicit QOCategoryTable(QObject *parent = nullptr);

    bool insert(const EntityCategory& category);
    bool remove(int id);
    bool update(const EntityCategory& category);
    QList<EntityCategory*> getAll();

};

#endif // QOCATEGORYTABLE_H
