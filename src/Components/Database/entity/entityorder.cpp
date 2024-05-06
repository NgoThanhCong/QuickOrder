#include "entityorder.h"

EntityOrder::EntityOrder(QObject *parent) : QObject(parent)
{

}

int EntityOrder::orderId() const
{
    return m_orderId;
}

void EntityOrder::setOrderId(int newOrderId)
{
    if (m_orderId == newOrderId)
        return;
    m_orderId = newOrderId;
    emit orderIdChanged();
}

const QString &EntityOrder::orderDateTime() const
{
    return m_orderDateTime;
}

void EntityOrder::setOrderDateTime(const QString &newOrderDateTime)
{
    if (m_orderDateTime == newOrderDateTime)
        return;
    m_orderDateTime = newOrderDateTime;
    emit orderDateTimeChanged();
}

float EntityOrder::totalAmount() const
{
    return m_totalAmount;
}

void EntityOrder::setTotalAmount(float newTotalAmount)
{
    if (qFuzzyCompare(m_totalAmount, newTotalAmount))
        return;
    m_totalAmount = newTotalAmount;
    emit totalAmountChanged();
}

int EntityOrder::voucherId() const
{
    return m_voucherId;
}

void EntityOrder::setVoucherId(int newVoucherId)
{
    if (m_voucherId == newVoucherId)
        return;
    m_voucherId = newVoucherId;
    emit voucherIdChanged();
}

float EntityOrder::cash() const
{
    return m_cash;
}

void EntityOrder::setCash(float newCash)
{
    if (qFuzzyCompare(m_cash, newCash))
        return;
    m_cash = newCash;
    emit cashChanged();
}

float EntityOrder::change() const
{
    return m_change;
}

void EntityOrder::setChange(float newChange)
{
    if (qFuzzyCompare(m_change, newChange))
        return;
    m_change = newChange;
    emit changeChanged();
}

int EntityOrder::transactionId() const
{
    return m_transactionId;
}

void EntityOrder::setTransactionId(int newTransactionId)
{
    if (m_transactionId == newTransactionId)
        return;
    m_transactionId = newTransactionId;
    emit transactionIdChanged();
}

int EntityOrder::userId() const
{
    return m_userId;
}

void EntityOrder::setUserId(int newUserId)
{
    if (m_userId == newUserId)
        return;
    m_userId = newUserId;
    emit userIdChanged();
}

void EntityOrder::printDebug()
{
    qDebug() << m_orderId;
    qDebug() << m_orderDateTime;
    qDebug() << m_totalAmount;
    qDebug() << m_transactionId;
    qDebug() << m_cash;
    qDebug() << m_change;
    qDebug() << m_userId;

}
