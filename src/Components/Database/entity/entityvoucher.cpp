#include "entityvoucher.h"

EntityVoucher::EntityVoucher(QObject *parent) : QObject(parent)
{

}

QString EntityVoucher::validDate() const
{
    return m_validDate;
}

void EntityVoucher::setValidDate(QString date)
{
    if (m_validDate == date)
        return;
    m_validDate = date;
    if(!TimeManager::getIntance()->isGreaterThanCurrentDate(m_validDate)){
        setStatus(2); // Expired
    }
    emit validDateChanged();
}

int EntityVoucher::discountValue() const
{
    return m_discountValue;
}

void EntityVoucher::setDiscountValue(int newDiscountValue)
{
    if (m_discountValue ==  newDiscountValue)
        return;
    m_discountValue = newDiscountValue;
    emit discountValueChanged();
}

int EntityVoucher::status() const
{
    return m_status;
}

void EntityVoucher::setStatus(int newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}

void EntityVoucher::printDebug()
{
    qDebug() << m_voucherId;
    qDebug() << m_voucherCode;
    qDebug() << m_validDate;
    qDebug() << m_discountValue;
    qDebug() << m_status;
}

int EntityVoucher::voucherId() const
{
    return m_voucherId;
}

void EntityVoucher::setVoucherId(int newVoucherId)
{
    if (m_voucherId == newVoucherId)
        return;
    m_voucherId = newVoucherId;
    emit voucherIdChanged();
}

const QString &EntityVoucher::voucherCode() const
{
    return m_voucherCode;
}

void EntityVoucher::setVoucherCode(const QString &newVoucherCode)
{
    if (m_voucherCode == newVoucherCode)
        return;
    m_voucherCode = newVoucherCode;
    emit voucherCodeChanged();
}

QString EntityVoucher::getStatusText()
{
    switch (m_status) {
    case 0:
        return "Active";
    case 1:
        return "Used";
    case 2:
        return "Expired";
    default:
        return "";
    }
}
