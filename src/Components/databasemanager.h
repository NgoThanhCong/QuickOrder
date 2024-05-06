#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QApplication>
#include "const.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QTextDecoder>
#include "Database/qousertable.h"
#include "Database/qocategorytable.h"
#include "Database/qomenuitemtable.h"
#include "Database/qoorderitemtable.h"
#include "const.h"


class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager* getInstance(){
        static DatabaseManager instance ;
        return & instance ;
    }

    bool connectToDb();

    static QString getDbPath(){
        QString dbPath = QCoreApplication::applicationDirPath().append("/").append(DB_NAME);
        qDebug() << __FUNCTION__ << ": " << dbPath;
        return dbPath;
    }

    static QString base64ToQString(const QString& base64String) {
        QByteArray decodedData = QByteArray::fromBase64(base64String.toUtf8());
        QString decodedString = QTextCodec::codecForName("UTF-8")->toUnicode(decodedData);
        return decodedString;
    }

    bool isConnected() const;
    void setIsConnected(bool newIsConnected);

signals:
    void isConnectedChanged(bool);

private:
    explicit DatabaseManager(QObject *parent = nullptr);
    QSqlDatabase m_db;
    bool m_isConnected;

    bool openDb();
    void createTables();
    bool isTableExisted(const QString&);

    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)
};

#endif // DATABASEMANAGER_H
