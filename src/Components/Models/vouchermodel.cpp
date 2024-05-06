#include "vouchermodel.h"

VoucherModel::VoucherModel(QObject *parent)
    : IModel{parent}
{}

VoucherModel::VoucherModel(const QString &name) : IModel(name)
{

}

QVariantList VoucherModel::vouchers() const
{
    QVariantList items;
    for(auto item : m_vouchers){
        items.append(QVariant::fromValue<EntityVoucher*>(item));
    }
    return items;
}

void VoucherModel::setVouchers(const QList<EntityVoucher *> &newVouchers)
{
    qDeleteAll(m_vouchers);
    m_vouchers.clear();

    m_vouchers.append(newVouchers);
    emit vouchersChanged();
}

bool VoucherModel::isCodeExisted(const QString &code)
{
    for(auto item : m_vouchers){
        if(item->voucherCode() == code){
            return true;
        }
    }
    return false;
}
