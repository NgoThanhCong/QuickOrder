#include "entitystatisticelement.h"

EntityStatisticElement::EntityStatisticElement(QObject *parent)
    : QObject{parent}
{}

QString EntityStatisticElement::label() const
{
    return m_label;
}

void EntityStatisticElement::setLabel(const QString &newLabel)
{
    m_label = newLabel;
    emit labelChanged();
}

float EntityStatisticElement::value() const
{
    return m_value;
}

void EntityStatisticElement::setValue(float newValue)
{
    m_value = newValue;
    emit valueChanged();
}
