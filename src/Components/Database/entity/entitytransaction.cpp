#include "entitytransaction.h"

EntityTransaction::EntityTransaction(QObject *parent) : QObject(parent)
{

}

int EntityTransaction::transactionId() const
{
    return m_transactionId;
}

void EntityTransaction::setTransactionId(int newTransactionId)
{
    if (m_transactionId == newTransactionId)
        return;
    m_transactionId = newTransactionId;
    emit transactionIdChanged();
}

int EntityTransaction::order_id() const
{
    return m_order_id;
}

void EntityTransaction::setOrder_id(int newOrder_id)
{
    if (m_order_id == newOrder_id)
        return;
    m_order_id = newOrder_id;
    emit order_idChanged();
}

int EntityTransaction::payment_method() const
{
    return m_payment_method;
}

void EntityTransaction::setPayment_method(int newPayment_method)
{
    if (m_payment_method == newPayment_method)
        return;
    m_payment_method = newPayment_method;
    emit payment_methodChanged();
}

float EntityTransaction::amount() const
{
    return m_amount;
}

void EntityTransaction::setAmount(float newAmount)
{
    if (qFuzzyCompare(m_amount, newAmount))
        return;
    m_amount = newAmount;
    emit amountChanged();
}

void EntityTransaction::printDebug()
{
    qDebug() << m_transactionId;
    qDebug() << m_order_id;
    qDebug() << m_payment_method;
    qDebug() << m_amount;
}
