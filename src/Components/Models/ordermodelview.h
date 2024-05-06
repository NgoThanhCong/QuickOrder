#ifndef ORDERMODELVIEW_H
#define ORDERMODELVIEW_H

#include <QAbstractListModel>
#include <QList>
#include "data/orderdata.h"
#include "../Database/entity/entitymenuitem.h"

#define SEPERATOR_CHAR "_"

class OrderModelView : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit OrderModelView(QObject *parent = nullptr);    

    enum AnimalRoles {
        NameRole = Qt::UserRole + 1,
        SizeRole,
        QuantityRole,
        PriceRole,
        IdRole,
        ImageRole,
        IceRole,
        SugarRole,
        ToppingRole,
    };

    ~OrderModelView();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void addOrderData(EntityMenuItem* item,int size);
    void updateOrderItem(QString orderDataId, int size );
    void removeOrderItem(QString orderDataId);

    void addToppingData(int idx, EntityMenuItem* item,int size);
    void removeToppingItem(QString orderDataId);

    float getTotal();
    void clearOrder();

    QList<OrderData*> getData();

public slots:
    void incIce(int idx);
    void incSugar(int idx);

signals:
    void orderDataChanged();

private:
    QList<OrderData*> m_data;
    OrderData* getOrderDataByID(QString& id);

    inline QString generateId(int itemId, int size)
    {
        return QString::number(itemId).append(QString::number(size));
    }

    inline QString generateToppingId(int itemId, int size, int toppingId, int toppingSize)
    {
        return QString::number(itemId).append(QString::number(size)).append(SEPERATOR_CHAR).
            append(QString::number(toppingId)).append(QString::number(toppingSize));
    }

    Q_PROPERTY(int rowCount READ rowCount NOTIFY orderDataChanged)

};

#endif // ORDERMODELVIEW_H
