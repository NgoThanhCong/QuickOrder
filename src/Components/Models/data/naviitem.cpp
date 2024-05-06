#include "naviitem.h"

NaviItem::NaviItem(QObject *parent) : QObject(parent)
{

}

NaviItem::NaviItem(const QString &name, const QString &src, bool isEnable) : m_name(name), m_src(src), m_isEnable(isEnable)
{

}

const QString &NaviItem::name() const
{
    return m_name;
}

void NaviItem::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

const QString &NaviItem::src() const
{
    return m_src;
}

void NaviItem::setSrc(const QString &newSrc)
{
    if (m_src == newSrc)
        return;
    m_src = newSrc;
    emit srcChanged();
}

bool NaviItem::isEnable() const
{
    return m_isEnable;
}

void NaviItem::setIsEnable(bool newIsEnable)
{
    if (m_isEnable == newIsEnable)
        return;
    m_isEnable = newIsEnable;
    emit isEnableChanged();
}
