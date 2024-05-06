#ifndef ENTITYBESTSELLER_H
#define ENTITYBESTSELLER_H

#include <QObject>

class EntityBestSeller : public QObject
{
    Q_OBJECT
public:
    explicit EntityBestSeller(QObject *parent = nullptr);

    QString itemName() const;
    void setItemName(const QString &newItemName);

    int quantity() const;
    void setQuantity(int newQuantity);

signals:
    void itemNameChanged();
    void quantityChanged();

private:
    QString m_itemName;
    int m_quantity;
    Q_PROPERTY(QString itemName READ itemName WRITE setItemName NOTIFY itemNameChanged FINAL)
    Q_PROPERTY(int quantity READ quantity WRITE setQuantity NOTIFY quantityChanged FINAL)
};

#endif // ENTITYBESTSELLER_H
