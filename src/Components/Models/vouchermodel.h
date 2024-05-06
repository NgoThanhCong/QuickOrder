#ifndef VOUCHERMODEL_H
#define VOUCHERMODEL_H

#include "imodel.h"
#include "../Database/entity/entityvoucher.h"

class VoucherModel : public IModel
{
    Q_OBJECT
public:
    explicit VoucherModel(QObject *parent = nullptr);
    VoucherModel(const QString& name);

    QVariantList vouchers() const;
    void setVouchers(const QList<EntityVoucher *> &newVouchers);
    Q_INVOKABLE bool isCodeExisted(const QString& code);

signals:
    void vouchersChanged();

private:
    QList<EntityVoucher*> m_vouchers;
    Q_PROPERTY(QVariantList vouchers READ vouchers NOTIFY vouchersChanged FINAL)
};

#endif // VOUCHERMODEL_H
