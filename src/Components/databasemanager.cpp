#include "databasemanager.h"

bool DatabaseManager::connectToDb()
{
    return openDb();
}

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{

}

bool DatabaseManager::isConnected() const
{
    return m_isConnected;
}

void DatabaseManager::setIsConnected(bool newIsConnected)
{
    m_isConnected = newIsConnected;
    emit isConnectedChanged(m_isConnected);
}

bool DatabaseManager::openDb()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(getDbPath());
    qDebug() << QSqlDatabase::drivers();
    if(m_db.open() && m_db.isValid())
    {
        qDebug() << __FUNCTION__ << " ==== DB OK ==== ";
        if(!isTableExisted(USER_TABLE)) createTables();
        setIsConnected(true);
        return true;
    }else{
        qCritical() << __FUNCTION__ << m_db.lastError();
        setIsConnected(false);
        return false;
    }
}

void DatabaseManager::createTables()
{
    qDebug() << __FUNCTION__ ;
    QString createTableQuery = base64ToQString("QkVHSU4gVFJBTlNBQ1RJT047CkNSRUFURSBUQUJMRSBJRiBOT1QgRVhJU1RTICJUUkFOU0FDVElP\
                                               Tl9UQUJMRSIgKAoJInRyYW5zYWN0aW9uX2lkIglJTlRFR0VSLAoJIm9yZGVyX2lkIglJTlRFR0VS\
                                               LAoJInBheW1lbnRfbWV0aG9kIglJTlRFR0VSLAoJImFtb3VudCIJSU5URUdFUgopOwpDUkVBVEUg\
                                               VEFCTEUgSUYgTk9UIEVYSVNUUyAiT1JERVJfVEFCTEUiICgKCSJvcmRlcl9pZCIJSU5URUdFUiwK\
                                               CSJvcmRlcl9kYXRlX3RpbWUiCVRFWFQgTk9UIE5VTEwsCgkidG90YWxfYW1vdW50IglSRUFMIE5P\
                                               VCBOVUxMLAoJInZvdWNoZXJfaWQiCUlOVEVHRVIsCgkidXNlcl9pZCIJSU5URUdFUiBOT1QgTlVM\
                                               TCwKCSJjYXNoIglSRUFMIE5PVCBOVUxMLAoJImNoYW5nZSIJUkVBTCBOT1QgTlVMTCwKCSJ0cmFu\
                                               c2FjdGlvbl9pZCIJSU5URUdFUiBOT1QgTlVMTCwKCVBSSU1BUlkgS0VZKCJvcmRlcl9pZCIpLAoJ\
                                               Rk9SRUlHTiBLRVkoInVzZXJfaWQiKSBSRUZFUkVOQ0VTICJVU0VSX1RBQkxFIigidXNlcl9pZCIp\
                                               LAoJRk9SRUlHTiBLRVkoInRyYW5zYWN0aW9uX2lkIikgUkVGRVJFTkNFUyAiVFJBTlNBQ1RJT05f\
                                               VEFCTEUiKCJ0cmFuc2FjdGlvbl9pZCIpLAoJRk9SRUlHTiBLRVkoInZvdWNoZXJfaWQiKSBSRUZF\
                                               UkVOQ0VTICJWT1VDSEVSX1RBQkxFIigidm91Y2hlcl9pZCIpCik7CkNSRUFURSBUQUJMRSBJRiBO\
                                               T1QgRVhJU1RTICJDQVRFR09SWV9UQUJMRSIgKAoJImNhdGVnb3J5X2lkIglJTlRFR0VSLAoJIm5h\
                                               bWUiCVRFWFQgTk9UIE5VTEwsCglQUklNQVJZIEtFWSgiY2F0ZWdvcnlfaWQiIEFVVE9JTkNSRU1F\
                                               TlQpCik7CkNSRUFURSBUQUJMRSBJRiBOT1QgRVhJU1RTICJNRU5VX1RBQkxFIiAoCgkiaXRlbV9p\
                                               ZCIJSU5URUdFUiwKCSJuYW1lIglURVhUIE5PVCBOVUxMLAoJInByaWNlIglSRUFMIE5PVCBOVUxM\
                                               LAoJImRlc2NyaXB0aW9uIglURVhULAoJImNhdGVnb3J5X2lkIglJTlRFR0VSIE5PVCBOVUxMLAoJ\
                                               ImltYWdlIglURVhUCik7CkNSRUFURSBUQUJMRSBJRiBOT1QgRVhJU1RTICJPUkRFUl9JVEVNU19U\
                                               QUJMRSIgKAoJIm9yZGVyX2l0ZW1faWQiCUlOVEVHRVIsCgkib3JkZXJfaWQiCUlOVEVHRVIgTk9U\
                                               IE5VTEwsCgkiaXRlbV9pZCIJSU5URUdFUiBOT1QgTlVMTCwKCSJxdWFudGl0eSIJSU5URUdFUiBO\
                                               T1QgTlVMTCBERUZBVUxUIDEsCglQUklNQVJZIEtFWSgib3JkZXJfaXRlbV9pZCIgQVVUT0lOQ1JF\
                                               TUVOVCksCglGT1JFSUdOIEtFWSgib3JkZXJfaWQiKSBSRUZFUkVOQ0VTICJPUkRFUl9UQUJMRSIo\
                                               Im9yZGVyX2lkIikKKTsKQ1JFQVRFIFRBQkxFIElGIE5PVCBFWElTVFMgIlZPVUNIRVJfVEFCTEUi\
                                               ICgKCSJ2b3VjaGVyX2lkIglJTlRFR0VSLAoJInZvdWNoZXJfY29kZSIJVEVYVCBOT1QgTlVMTCwK\
                                               CSJ2YWxpZF9kYXRlIglURVhUIE5PVCBOVUxMLAoJImRpc2NvdW50X3ZhbHVlIglSRUFMIE5PVCBO\
                                               VUxMLAoJInN0YXR1cyIJSU5URUdFUiBERUZBVUxUIDAsCglQUklNQVJZIEtFWSgidm91Y2hlcl9p\
                                               ZCIgQVVUT0lOQ1JFTUVOVCkKKTsKQ1JFQVRFIFRBQkxFIElGIE5PVCBFWElTVFMgIlVTRVJfVEFC\
                                               TEUiICgKCSJ1c2VyX2lkIglJTlRFR0VSLAoJInVzZXJfdHlwZSIJSU5URUdFUiBOT1QgTlVMTCwK\
                                               CSJuYW1lIglURVhUIE5PVCBOVUxMLAoJImRvYiIJVEVYVCwKCSJhZGRyZXNzIglURVhUIE5PVCBO\
                                               VUxMLAoJInBob25lIglURVhULAoJInVzZXJfbmFtZSIJVEVYVCBOT1QgTlVMTCBVTklRVUUsCgki\
                                               cGFzc3dvcmQiCUlOVEVHRVIgTk9UIE5VTEwsCgkiYXZhdGFyIglURVhULAoJImhpcmVfZGF0ZSIJ\
                                               VEVYVCwKCVBSSU1BUlkgS0VZKCJ1c2VyX2lkIiBBVVRPSU5DUkVNRU5UKQopOwpJTlNFUlQgSU5U\
                                               TyAiVVNFUl9UQUJMRSIgVkFMVUVTICgxLDAsJ05nw7QgVGjDoG5oIEPDtG5nJywnMjgvMDgvMjAw\
                                               MCcsJ05hbSBU4burIExpw6ptJywnMDk0Nzc3MTY5OScsJ2NvbmdudCcsJzM3MTljOTUzYTQyNDBl\
                                               YTI3ZTQ2NDI5ZDJhMTEyNWNhOGExNjkzZjIzYzVmN2RmY2NjM2U1ZTAxNGI5MDYxZjgnLCdxcmM6\
                                               L2ltYWdlcy9hdnRfZHVtbXkucG5nJywnMjgvMDgvMjAyNCcpOwpDT01NSVQ7");
                                                QStringList queries = createTableQuery.split(";");
    for(QString query : qAsConst(queries)){
        if(query.isEmpty()) continue;
        query = query.append(";");
        qDebug() << query;
        QSqlQuery sqlQ(query,m_db);
        sqlQ.exec();
    }
}

bool DatabaseManager::isTableExisted(const QString& tableName)
{
    QString rawQuery = QString("SELECT COUNT(*) FROM sqlite_master WHERE type = 'table' AND name = '%1'").arg(tableName);
    QSqlQuery query(rawQuery,m_db);

    if (!query.exec()) {
        qDebug() << __FUNCTION__ << ":" << query.lastError().text();
        qDebug() << __FUNCTION__ << ":" << query.lastQuery();
        return false;
    }

    if(query.next()) return (query.value(0).toInt() == 1);
    return false;
}
