#ifndef TITLEBARMODEL_H
#define TITLEBARMODEL_H
#include "imodel.h"

class TitleBarModel : public IModel
{
    Q_OBJECT
    Q_PROPERTY(QString appName READ appName WRITE setAppName NOTIFY appNameChanged)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged)
public:
    TitleBarModel();
    TitleBarModel(const QString& name);
    void init();

    const QString &appName() const;
    void setAppName(const QString &newAppName);

    const QString &version() const;
    void setVersion(const QString &newVersion);

signals:
    void appNameChanged();

    void versionChanged();

private:
    QString m_appName;
    QString m_version;   
};

#endif // TITLEBARMODEL_H
