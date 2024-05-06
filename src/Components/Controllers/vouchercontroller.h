#ifndef VOUCHERCONTROLLER_H
#define VOUCHERCONTROLLER_H

#include "icontroller.h"
#include "../Database/qovouchertable.h"

class VoucherController : public IController
{
    Q_OBJECT
public:
    explicit VoucherController(QObject *parent = nullptr);
    VoucherController(const QString &tag, QObject* parent = nullptr);

public slots:
    void syncData();
    bool removeVoucher(int id);
    bool generateVoucher(int value, int quantity, QString date);

private:
    QOVoucherTable m_voucherTable;

    QString generateDiscountCode();
};

#endif // VOUCHERCONTROLLER_H
