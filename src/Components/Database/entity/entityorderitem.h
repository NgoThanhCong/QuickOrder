#ifndef ENTITYORDERITEM_H
#define ENTITYORDERITEM_H

#include <QObject>
#include <QDebug>

class EntityOrderItem : public QObject
{
    Q_OBJECT
public:
    explicit EntityOrderItem(QObject *parent = nullptr);

    int orderItemId() const;
    void setOrderItemId(int newOrderItemId);

    int orderId() const;
    void setOrderId(int newOrderId);

    int itemId() const;
    void setItemId(int newItemId);

    int quantity() const;
    void setQuantity(int newQuantity);

    void printDebug();

    int itemSize() const;
    void setItemSize(int newItemSize);

signals:
    void orderItemIdChanged();

    void orderIdChanged();

    void itemIdChanged();

    void quantityChanged();

    void itemSizeChanged();

private:
    int m_orderItemId;
    int m_orderId;
    int m_itemId;
    int m_quantity;
    int m_itemSize;

    Q_PROPERTY(int orderItemId READ orderItemId WRITE setOrderItemId NOTIFY orderItemIdChanged)
    Q_PROPERTY(int orderId READ orderId WRITE setOrderId NOTIFY orderIdChanged)
    Q_PROPERTY(int itemId READ itemId WRITE setItemId NOTIFY itemIdChanged)
    Q_PROPERTY(int quantity READ quantity WRITE setQuantity NOTIFY quantityChanged)
    Q_PROPERTY(int itemSize READ itemSize WRITE setItemSize NOTIFY itemSizeChanged FINAL)
};

#endif // ENTITYORDERITEM_H
