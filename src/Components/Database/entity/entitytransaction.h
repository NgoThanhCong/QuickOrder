#ifndef ENTITYTRANSACTION_H
#define ENTITYTRANSACTION_H

#include <QObject>
#include <QDebug>

class EntityTransaction : public QObject
{
    Q_OBJECT
public:
    explicit EntityTransaction(QObject *parent = nullptr);

    int transactionId() const;
    void setTransactionId(int newTransactionId);

    int order_id() const;
    void setOrder_id(int newOrder_id);

    int payment_method() const;
    void setPayment_method(int newPayment_method);

    float amount() const;
    void setAmount(float newAmount);

    void printDebug();

signals:
    void transactionIdChanged();

    void order_idChanged();

    void payment_methodChanged();

    void amountChanged();

private:
    int m_transactionId;
    int m_order_id;
    int m_payment_method;
    float m_amount;
    Q_PROPERTY(int transactionId READ transactionId WRITE setTransactionId NOTIFY transactionIdChanged)
    Q_PROPERTY(int order_id READ order_id WRITE setOrder_id NOTIFY order_idChanged)
    Q_PROPERTY(int payment_method READ payment_method WRITE setPayment_method NOTIFY payment_methodChanged)
    Q_PROPERTY(float amount READ amount WRITE setAmount NOTIFY amountChanged)
};

#endif // ENTITYTRANSACTION_H
