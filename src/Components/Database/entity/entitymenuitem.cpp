#include "entitymenuitem.h"

EntityMenuItem::EntityMenuItem(QObject *parent) : QObject(parent)
{

}

int EntityMenuItem::itemId() const
{
    return m_itemId;
}

void EntityMenuItem::setItemId(int newItemId)
{
    if (m_itemId == newItemId)
        return;
    m_itemId = newItemId;
    emit itemIdChanged();
}

const QString &EntityMenuItem::name() const
{
    return m_name;
}

void EntityMenuItem::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

const QString &EntityMenuItem::description() const
{
    return m_description;
}

void EntityMenuItem::setDescription(const QString &newDescription)
{
    if (m_description == newDescription)
        return;
    m_description = newDescription;
    emit descriptionChanged();
}

int EntityMenuItem::categoryId() const
{
    return m_categoryId;
}

void EntityMenuItem::setCategoryId(int newCategoryId)
{
    if (m_categoryId == newCategoryId)
        return;
    m_categoryId = newCategoryId;
    emit categoryIdChanged();
}

QString EntityMenuItem::image() const
{
    return m_image;
}

void EntityMenuItem::setImage(const QString &newImage)
{
    if(newImage.isEmpty()){
        m_image = "qrc:/images/default_item_img.jpg";
    }else{
        m_image = newImage;
    }
    emit imageChanged();
}

QString EntityMenuItem::price() const
{
    return QString::number(m_price, 'f', 2);
}

void EntityMenuItem::setPrice(float newPrice)
{
    m_price = round(newPrice * 100.0) / 100.0;
    emit priceChanged();
}

QString EntityMenuItem::priceM() const
{
    return QString::number(m_priceM, 'f', 2);
}

void EntityMenuItem::setPriceM(float newPriceM)
{
    m_priceM = round(newPriceM * 100.0) / 100.0;
    emit priceMChanged();
}

QString EntityMenuItem::priceL() const
{
    return QString::number(m_priceL, 'f', 2);
}

void EntityMenuItem::setPriceL(float newPriceL)
{
    m_priceL = round(newPriceL * 100.0) / 100.0;
    emit priceLChanged();
}

void EntityMenuItem::printDebug()
{
    qDebug() << m_itemId << " - " <<m_name << " - " <<
        m_categoryId << " - " << m_price << " - " << m_priceM << " - " << m_priceL;
    qDebug() << m_image;
}

float EntityMenuItem::getPrice() const
{
    return m_price;
}

float EntityMenuItem::getPriceM() const
{
    return m_priceM;
}

float EntityMenuItem::getPriceL() const
{
    return m_priceL;
}

bool EntityMenuItem::isTopping()
{
    return m_categoryId == CAT_TOPPING_ID;
}
