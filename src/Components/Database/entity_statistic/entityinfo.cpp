#include "entityinfo.h"

EntityInfo::EntityInfo(QObject *parent)
    : QObject{parent}
{}

QString EntityInfo::name() const
{
    return m_name;
}

void EntityInfo::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

QString EntityInfo::info() const
{
    return m_info;
}

void EntityInfo::setInfo(const QString &newInfo)
{
    if (m_info == newInfo)
        return;
    m_info = newInfo;
    emit infoChanged();
}
