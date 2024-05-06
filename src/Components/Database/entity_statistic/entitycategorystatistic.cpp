#include "entitycategorystatistic.h"

EntityCategoryStatistic::EntityCategoryStatistic(QObject *parent)
    : QObject{parent}
{}

QString EntityCategoryStatistic::name() const
{
    return m_name;
}

void EntityCategoryStatistic::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

float EntityCategoryStatistic::totalAmount() const
{
    return m_totalAmount;
}

void EntityCategoryStatistic::setTotalAmount(float newTotalAmount)
{
    if (qFuzzyCompare(m_totalAmount, newTotalAmount))
        return;
    m_totalAmount = newTotalAmount;
    emit totalAmountChanged();
}
