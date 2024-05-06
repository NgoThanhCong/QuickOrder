#ifndef ENTITYCATEGORYSTATISTIC_H
#define ENTITYCATEGORYSTATISTIC_H

#include <QObject>

class EntityCategoryStatistic : public QObject
{
    Q_OBJECT
public:
    explicit EntityCategoryStatistic(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &newName);

    float totalAmount() const;
    void setTotalAmount(float newTotalAmount);

signals:
    void nameChanged();

    void totalAmountChanged();

private:
    QString m_name;
    float m_totalAmount;
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(float totalAmount READ totalAmount WRITE setTotalAmount NOTIFY totalAmountChanged FINAL)
};

#endif // ENTITYCATEGORYSTATISTIC_H
