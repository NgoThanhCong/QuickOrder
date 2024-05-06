#include "orderdata.h"

OrderData::OrderData(QObject *parent) : QObject(parent)
{

}

OrderData::OrderData(QString id, QObject *parent) : QObject(parent)
{
    m_id = id;
    m_icePercent = 2;
    m_sugarPercent = 2;
    m_itemIdBelongs = "";
}

int OrderData::quantity() const
{
    return m_quantity;
}

void OrderData::setQuantity(int newQuantity)
{
    m_quantity = newQuantity;
    emit quantityChanged();
}

QVariant OrderData::orderItem()
{
    return QVariant::fromValue<EntityMenuItem*>(m_orderItem);
}

void OrderData::setOrderItem(EntityMenuItem *newOrderItem)
{
    m_orderItem = newOrderItem;
    emit orderItemChanged();
}

EntityMenuItem *OrderData::getOrderItem()
{
    return m_orderItem;
}

int OrderData::size() const
{
    return m_size;
}

QString OrderData::getSize()
{
    switch (m_size) {
    case 0:
        return "S";
    case 1:
        return "M";
    case 2:
        return "L";
    default:
        return "S";
    }
}

void OrderData::setSize(int newSize)
{
    if (m_size == newSize)
        return;
    m_size = newSize;
    emit sizeChanged();
}

QString OrderData::id() const
{
    return m_id;
}

QString OrderData::getName()
{
    if(m_orderItem != nullptr){
        return m_orderItem->name();
    }
    return "";
}

QString OrderData::getPrice()
{
    float price = 0.0;
    if(m_size == 0){
        price = m_orderItem->getPrice();
    }else if(m_size == 1){
        price = m_orderItem->getPriceM();
    }else if(m_size == 2){
        price = m_orderItem->getPriceL();
    }
    price = round(price * m_quantity * 100.0) / 100.0;
    return QString::number(price, 'f', 2);
}

float OrderData::getPriceF()
{
    float price = 0.0;
    if(m_size == 0){
        price = m_orderItem->getPrice();
    }else if(m_size == 1){
        price = m_orderItem->getPriceM();
    }else if(m_size == 2){
        price = m_orderItem->getPriceL();
    }
    return round(price * m_quantity * 100.0) / 100.0;
}

QString OrderData::getImage()
{
    return m_orderItem->image();
}

QString OrderData::getPriceUnit()
{
    float price = 0.0;
    if(m_size == 0){
        price = m_orderItem->getPrice();
    }else if(m_size == 1){
        price = m_orderItem->getPriceM();
    }else if(m_size == 2){
        price = m_orderItem->getPriceL();
    }
    price = round(price * 100.0) / 100.0;
    return QString::number(price, 'f', 2);
}

bool OrderData::isTopping()
{
    return m_orderItem->categoryId() == CAT_TOPPING_ID;
}

int OrderData::itemId() const
{
    return m_itemId;
}

void OrderData::setItemId(int newItemId)
{
    if (m_itemId == newItemId)
        return;
    m_itemId = newItemId;
    emit itemIdChanged();
}

int OrderData::icePercent() const
{
    return m_icePercent;
}

void OrderData::setIcePercent(int newIcePercent)
{
    qDebug() << __FUNCTION__ << newIcePercent;
    m_icePercent = newIcePercent;
    emit icePercentChanged();
}

int OrderData::sugarPercent() const
{
    return m_sugarPercent;
}

void OrderData::setSugarPercent(int newSugarPercent)
{
    qDebug() << __FUNCTION__ << newSugarPercent;
    m_sugarPercent = newSugarPercent;
    emit sugarPercentChanged();
}

QString OrderData::getNotes()
{
    QString note;
    switch (m_icePercent) {
    case 0:
        note.append("I0");
        break;
    case 1:
        note.append("I50");
        break;
    case 2:
        note.append("I100");
        break;
    default:
        note.append("I100");
        break;
    }

    switch (m_sugarPercent) {
    case 0:
        note.append("-S0");
        break;
    case 1:
        note.append("-S50");
        break;
    case 2:
        note.append("-S100");
        break;
    default:
        note.append("-S100");
        break;
    }
    return note;
}

void OrderData::incIcePercent()
{
    setIcePercent(m_icePercent == 2 ? 0 : (++m_icePercent));
}

void OrderData::incSugarPercent()
{
    setSugarPercent(m_sugarPercent == 2 ? 0 : (++m_sugarPercent));
}

QString OrderData::itemIdBelongs() const
{
    return m_itemIdBelongs;
}

void OrderData::setItemIdBelongs(const QString &newItemIdBelongs)
{
    m_itemIdBelongs = newItemIdBelongs;
}
