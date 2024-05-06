#ifndef ENTITYMENUITEM_H
#define ENTITYMENUITEM_H

#include <QObject>
#include <QDebug>
#include <math.h>

#define CAT_TOPPING_ID 7

class EntityMenuItem : public QObject
{
    Q_OBJECT
public:
    explicit EntityMenuItem(QObject *parent = nullptr);

    int itemId() const;
    void setItemId(int newItemId);

    const QString &name() const;
    void setName(const QString &newName);

    const QString &description() const;
    void setDescription(const QString &newDescription);

    int categoryId() const;
    void setCategoryId(int newCategoryId);

    QString image() const;
    void setImage(const QString &newImage);

    QString price() const;
    void setPrice(float newPrice);

    QString priceM() const;
    void setPriceM(float newPriceM);

    QString priceL() const;
    void setPriceL(float newPriceL);

    void printDebug();

    float getPrice() const;
    float getPriceM() const;
    float getPriceL() const;

    Q_INVOKABLE bool isTopping();

signals:
    void itemIdChanged();

    void nameChanged();

    void descriptionChanged();

    void categoryIdChanged();

    void imageChanged();

    void priceChanged();

    void priceMChanged();

    void priceLChanged();

private:
    int m_itemId;
    QString m_name;
    QString m_description;
    int m_categoryId;
    QString m_image;
    float m_price;
    float m_priceM;
    float m_priceL;
    Q_PROPERTY(int itemId READ itemId WRITE setItemId NOTIFY itemIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(int categoryId READ categoryId WRITE setCategoryId NOTIFY categoryIdChanged)
    Q_PROPERTY(QString image READ image NOTIFY imageChanged)
    Q_PROPERTY(QString price READ price NOTIFY priceChanged)
    Q_PROPERTY(QString priceM READ priceM NOTIFY priceMChanged)
    Q_PROPERTY(QString priceL READ priceL NOTIFY priceLChanged)
};

#endif // ENTITYMENUITEM_H
