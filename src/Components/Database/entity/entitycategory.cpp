#include "entitycategory.h"

EntityCategory::EntityCategory(QObject *parent) : QObject(parent)
{

}

int EntityCategory::categoryId() const
{
    return m_categoryId;
}

void EntityCategory::setCategoryId(int newCategoryId)
{
    if (m_categoryId == newCategoryId)
        return;
    m_categoryId = newCategoryId;
    emit categoryIdChanged();
}

const QString &EntityCategory::name() const
{
    return m_name;
}

void EntityCategory::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

void EntityCategory::printDebug()
{
    qDebug() << m_categoryId;
    qDebug() << m_name;
}
