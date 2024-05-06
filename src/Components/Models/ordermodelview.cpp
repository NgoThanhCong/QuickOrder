#include "ordermodelview.h"

OrderModelView::OrderModelView(QObject *parent)
    : QAbstractListModel{parent}
{}

OrderModelView::~OrderModelView()
{

}

void OrderModelView::addOrderData(EntityMenuItem *item, int size)
{
    qDebug() << __FUNCTION__ << item->itemId() << " - " << size;
    if(item == nullptr){
        qCritical() << "MenuItem null";
        return;
    }

    QString id = generateId(item->itemId(), size);
    OrderData* od = getOrderDataByID(id);

    if(od == nullptr){
        od = new OrderData(id);
        od->setOrderItem(item);
        od->setQuantity(1);
        od->setSize(size);
        od->setItemId(item->itemId());

        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_data.append(od);
        endInsertRows();
    }else{
        beginResetModel();
        od->setQuantity(od->quantity() + 1);
        endResetModel();
    }
    emit orderDataChanged();
}

void OrderModelView::updateOrderItem(QString orderDataId, int quantity)
{
    qDebug() << __FUNCTION__ << orderDataId;
    if(quantity == 0){
        qDebug() << __FUNCTION__ << quantity;
        removeOrderItem(orderDataId);
        return;
    }
    OrderData* od = getOrderDataByID(orderDataId);
    beginResetModel();
    od->setQuantity(quantity);
    endResetModel();
    emit orderDataChanged();
}

void OrderModelView::removeOrderItem(QString orderDataId)
{
    qDebug() << __FUNCTION__ << orderDataId;
    QMutableListIterator<OrderData*> it(m_data);
    while(it.hasNext()){
        OrderData* item  = it.next();
        if(item->id() == orderDataId ||    // Remove item
            (item->isTopping() && item->itemIdBelongs() == orderDataId)){ // Remove all topping of the item
            delete item;
            it.remove();
        }
    }

    beginResetModel();
    endResetModel();
    emit orderDataChanged();
}

void OrderModelView::addToppingData(int idx, EntityMenuItem *topping, int size)
{
    if(idx  == - 1) return;
    OrderData* item = m_data[idx];
    if(!item->isTopping()){
        QString toppingId = generateToppingId(item->getOrderItem()->itemId(),item->size(),topping->itemId(),size);
        qDebug() << __FUNCTION__ << " - " << toppingId;
        OrderData* toppingOd = getOrderDataByID(toppingId);
        if(toppingOd == nullptr){
            toppingOd = new OrderData(toppingId);
            toppingOd->setOrderItem(topping);
            toppingOd->setSize(size);
            toppingOd->setItemId(topping->itemId());
            toppingOd->setQuantity(1);
            toppingOd->setItemIdBelongs(item->id());
            beginResetModel();
            m_data.insert(idx+1,toppingOd);
            endResetModel();
        }else{
            beginResetModel();
            toppingOd->setQuantity(toppingOd->quantity() + 1);
            endResetModel();
        }
    }
    emit orderDataChanged();
}

void OrderModelView::removeToppingItem(QString orderDataId)
{
    qDebug() << __FUNCTION__ << orderDataId;
    for(int i=0;i<m_data.size();i++){
        if(m_data[i]->id() == orderDataId){
            delete m_data[i];
            beginResetModel();
            m_data.removeAt(i);
            endResetModel();
            emit orderDataChanged();
            return;
        }
    }
}

float OrderModelView::getTotal()
{
    float total =0.0;
    foreach (OrderData* od, m_data) {
        total += od->getPriceF();
    }
    return total;
}

void OrderModelView::clearOrder()
{
    beginResetModel();
    qDeleteAll(m_data);
    m_data.clear();
    endResetModel();
}

QList<OrderData *> OrderModelView::getData()
{
    return m_data;
}

void OrderModelView::incIce(int idx)
{
    if(idx < m_data.length()){
        qDebug() << __FUNCTION__ << idx;
        beginResetModel();
        m_data[idx]->incIcePercent();
        endResetModel();
    }
}

void OrderModelView::incSugar(int idx)
{
    if(idx < m_data.length()){
        qDebug() << __FUNCTION__ << idx;
        beginResetModel();
        m_data[idx]->incSugarPercent();
        endResetModel();
    }
}

OrderData* OrderModelView::getOrderDataByID(QString& id)
{
    foreach (OrderData* od, m_data) {
        if(od->id() == id){
            return od;
        }
    }
    return nullptr;
}

int OrderModelView::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant OrderModelView::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_data.count())
        return QVariant();

    OrderData* od = m_data[index.row()];
    if (role == NameRole)
        return od->getName();
    else if (role == SizeRole)
        return od->getSize();
    else if (role == QuantityRole)
        return od->quantity();
    else if (role == PriceRole)
        return od->getPrice();
    else if (role == IdRole)
        return od->id();
    else if (role == ImageRole)
        return od->getImage();
    else if (role == IceRole)
        return od->icePercent();
    else if (role == SugarRole)
        return od->sugarPercent();
    else if (role == ToppingRole)
        return od->isTopping();
    return QVariant();
}

QHash<int, QByteArray> OrderModelView::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[SizeRole] = "size";
    roles[QuantityRole] = "quantity";
    roles[PriceRole] = "price";
    roles[IdRole] = "id";
    roles[ImageRole] = "image";
    roles[IceRole] = "iceLevel";
    roles[SugarRole] = "sugarLevel";
    roles[ToppingRole] = "isTopping";
    return roles;
}
