#ifndef QOUSERTABLE_H
#define QOUSERTABLE_H

#include <QObject>
#include <QVariant>
#include "sqlitetablebase.h"
#include "entity/entityuser.h"

class QOUserTable : public SQLiteTableBase
{
    Q_OBJECT
public:
    explicit QOUserTable(QObject *parent = nullptr);

    bool insert(const EntityUser& user);
    bool remove(const QString& userId);
    bool update(const EntityUser& user);
    QList<EntityUser*> getAll();
    EntityUser* getByUserName(const QString& id);
private:
    void fillDataFromQuery(const QSqlQuery& src, EntityUser* dst);

};

#endif // QOUSERTABLE_H
