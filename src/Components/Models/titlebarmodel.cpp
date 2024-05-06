#include "titlebarmodel.h"

TitleBarModel::TitleBarModel()
{
    init();
}

TitleBarModel::TitleBarModel(const QString &name) : IModel(name)
{    
    init();
}

const QString &TitleBarModel::appName() const
{
    return m_appName;
}

void TitleBarModel::setAppName(const QString &newAppName)
{
    if (m_appName == newAppName)
        return;
    m_appName = newAppName;
    emit appNameChanged();
}

const QString &TitleBarModel::version() const
{
    return m_version;
}

void TitleBarModel::setVersion(const QString &newVersion)
{
    if (m_version == newVersion)
        return;
    m_version = newVersion;
    emit versionChanged();
}

void TitleBarModel::init()
{
    m_appName = "Quick Order";
    m_version = "Quick Order 1.0";
}
