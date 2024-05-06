#ifndef SQLITETABLEBASE_H
#define SQLITETABLEBASE_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "Misc/Utilities.h"

class SQLiteTableBase : public QObject
{
    Q_OBJECT
public:
    explicit SQLiteTableBase(QObject *parent = nullptr);
    virtual ~SQLiteTableBase();

    bool isDbConnected();
};

#endif // SQLITETABLEBASE_H
