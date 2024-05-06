#include "entitydatevalue.h"

EntityDateValue::EntityDateValue(QObject *parent) : QObject(parent)
{

}

QString EntityDateValue::date() const
{
    return m_date.toString("dd.MM.yyyy");
}

void EntityDateValue::setDate(const QDateTime &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

float EntityDateValue::value() const
{
    return m_value;
}

void EntityDateValue::setValue(float newValue)
{
    if (qFuzzyCompare(m_value, newValue))
        return;
    m_value = newValue;
    emit valueChanged();
}
