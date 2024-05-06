#include "vouchercontroller.h"

VoucherController::VoucherController(QObject *parent)
    : IController{parent}
{}

VoucherController::VoucherController(const QString &tag, QObject *parent) : IController(tag, parent)
{

}

void VoucherController::syncData()
{
    VoucherModel* model = getModel<VoucherModel>();
    model->setVouchers(m_voucherTable.getAll());
}

bool VoucherController::removeVoucher(int id)
{
    return m_voucherTable.remove(id);
}

bool VoucherController::generateVoucher(int value, int quantity, QString date)
{
    qDebug() << __FUNCTION__ << value << " - " << quantity << " - " << date;
    for(int i=0;i<quantity;i++){
        EntityVoucher ev;
        ev.setVoucherCode(generateDiscountCode());
        ev.setDiscountValue(value);
        ev.setValidDate(date);
        ev.setStatus(0); // Active

        m_voucherTable.insert(ev);
    }

    return true;
}

QString VoucherController::generateDiscountCode()
{
    VoucherModel* model = getModel<VoucherModel>();
    QString discountCode;
    do{
        for (int i = 0; i < 6; ++i) {
            discountCode.append(QChar('A' + qrand() % 26)); // Generates a random uppercase letter
        }
    }while (model->isCodeExisted(discountCode));

    return discountCode;
}
