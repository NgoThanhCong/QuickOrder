#include "entityorderitem.h"

EntityOrderItem::EntityOrderItem(QObject *parent) : QObject(parent)
{

}

int EntityOrderItem::orderItemId() const
{
    return m_orderItemId;
}

void EntityOrderItem::setOrderItemId(int newOrderItemId)
{
    if (m_orderItemId == newOrderItemId)
        return;
    m_orderItemId = newOrderItemId;
    emit orderItemIdChanged();
}

int EntityOrderItem::orderId() const
{
    return m_orderId;
}

void EntityOrderItem::setOrderId(int newOrderId)
{
    if (m_orderId == newOrderId)
        return;
    m_orderId = newOrderId;
    emit orderIdChanged();
}

int EntityOrderItem::itemId() const
{
    return m_itemId;
}

void EntityOrderItem::setItemId(int newItemId)
{
    if (m_itemId == newItemId)
        return;
    m_itemId = newItemId;
    emit itemIdChanged();
}

int EntityOrderItem::quantity() const
{
    return m_quantity;
}

void EntityOrderItem::setQuantity(int newQuantity)
{
    if (m_quantity == newQuantity)
        return;
    m_quantity = newQuantity;
    emit quantityChanged();
}

void EntityOrderItem::printDebug()
{
    qDebug() << m_itemId;
    qDebug() << m_orderId;
    qDebug() << m_orderItemId;
    qDebug() << m_quantity;
}

int EntityOrderItem::itemSize() const
{
    return m_itemSize;
}

void EntityOrderItem::setItemSize(int newItemSize)
{
    if (m_itemSize == newItemSize)
        return;
    m_itemSize = newItemSize;
    emit itemSizeChanged();
}
