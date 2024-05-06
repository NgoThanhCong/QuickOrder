#include "entitybestseller.h"

EntityBestSeller::EntityBestSeller(QObject *parent)
    : QObject{parent} , m_itemName(""), m_quantity(0)
{}

QString EntityBestSeller::itemName() const
{
    return m_itemName;
}

void EntityBestSeller::setItemName(const QString &newItemName)
{
    if (m_itemName == newItemName)
        return;
    m_itemName = newItemName;
    emit itemNameChanged();
}

int EntityBestSeller::quantity() const
{
    return m_quantity;
}

void EntityBestSeller::setQuantity(int newQuantity)
{
    if (m_quantity == newQuantity)
        return;
    m_quantity = newQuantity;
    emit quantityChanged();
}
