#ifndef ENTITYORDER_H
#define ENTITYORDER_H

#include <QObject>
#include <QDateTime>
#include <QDebug>

class EntityOrder : public QObject
{
    Q_OBJECT
public:
    explicit EntityOrder(QObject *parent = nullptr);

    int orderId() const;
    void setOrderId(int newOrderId);

    const QString &orderDateTime() const;
    void setOrderDateTime(const QString &newOrderDateTime);

    float totalAmount() const;
    void setTotalAmount(float newTotalAmount);

    int voucherId() const;
    void setVoucherId(int newVoucherId);

    float cash() const;
    void setCash(float newCash);

    float change() const;
    void setChange(float newChange);

    int transactionId() const;
    void setTransactionId(int newTransactionId);

    int userId() const;
    void setUserId(int newUserId);

    void printDebug();

signals:
    void orderIdChanged();

    void orderDateTimeChanged();

    void totalAmountChanged();

    void voucherIdChanged();

    void cashChanged();

    void changeChanged();

    void transactionIdChanged();

    void userIdChanged();

private:
    int m_orderId;
    QString m_orderDateTime;
    float m_totalAmount;
    int m_voucherId;
    float m_cash;
    float m_change;
    int m_transactionId;
    int m_userId;

    Q_PROPERTY(int orderId READ orderId WRITE setOrderId NOTIFY orderIdChanged)
    Q_PROPERTY(QString orderDateTime READ orderDateTime WRITE setOrderDateTime NOTIFY orderDateTimeChanged)
    Q_PROPERTY(float totalAmount READ totalAmount WRITE setTotalAmount NOTIFY totalAmountChanged)
    Q_PROPERTY(int voucherId READ voucherId WRITE setVoucherId NOTIFY voucherIdChanged)
    Q_PROPERTY(float cash READ cash WRITE setCash NOTIFY cashChanged)
    Q_PROPERTY(float change READ change WRITE setChange NOTIFY changeChanged)
    Q_PROPERTY(int transactionId READ transactionId WRITE setTransactionId NOTIFY transactionIdChanged)
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)
};

#endif // ENTITYORDER_H
