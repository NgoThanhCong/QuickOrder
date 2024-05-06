#ifndef ORDERDATA_H
#define ORDERDATA_H

#include <QObject>
#include <math.h>
#include "../../Database/entity/entityorderitem.h"
#include "../../Database/entity/entitymenuitem.h"

class OrderData : public QObject
{
    Q_OBJECT
public:
    OrderData(QObject* parent = nullptr);
    OrderData(QString id,QObject *parent = nullptr);

    int quantity() const;
    void setQuantity(int newQuantity);

    QVariant orderItem();
    void setOrderItem(EntityMenuItem *newOrderItem);
    EntityMenuItem* getOrderItem();

    int size() const;
    QString getSize();
    void setSize(int newSize);

    QString id() const;

    QString getName();
    QString getPrice();
    float   getPriceF();
    QString getImage();
    QString getPriceUnit();
    bool isTopping();

    int itemId() const;
    void setItemId(int newItemId);

    int icePercent() const;
    void setIcePercent(int newIcePercent);

    int sugarPercent() const;
    void setSugarPercent(int newSugarPercent);

    QString getNotes();

    QString itemIdBelongs() const;
    void setItemIdBelongs(const QString &newItemIdBelongs);

signals:
    void quantityChanged();

    void sizeChanged();

    void orderItemChanged();

    void idChanged();

    void itemIdChanged();

    void icePercentChanged();

    void sugarPercentChanged();

    void toppingChanged();

public slots:
    void incIcePercent();
    void incSugarPercent();

private:
    EntityMenuItem* m_orderItem;
    int m_quantity;
    int m_size;
    QString m_id;
    int m_icePercent;
    int m_sugarPercent;
    int m_itemId;
    QString m_itemIdBelongs;

    Q_PROPERTY(int quantity READ quantity WRITE setQuantity NOTIFY quantityChanged)
    Q_PROPERTY(QVariant orderItem READ orderItem NOTIFY orderItemChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(int itemId READ itemId WRITE setItemId NOTIFY itemIdChanged)
    Q_PROPERTY(int icePercent READ icePercent WRITE setIcePercent NOTIFY icePercentChanged)
    Q_PROPERTY(int sugarPercent READ sugarPercent WRITE setSugarPercent NOTIFY sugarPercentChanged)
};

#endif // ORDERDATA_H
