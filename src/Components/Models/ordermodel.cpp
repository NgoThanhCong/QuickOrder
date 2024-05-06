#include "ordermodel.h"

OrderModel::OrderModel(QObject *parent)
    : IModel{parent}
{
    init();
}

OrderModel::OrderModel(const QString &name)
    : IModel(name)
{
    init();
}

void OrderModel::init()
{
    m_voucher = nullptr;
    m_orderDataView = new OrderModelView();
    connect(m_orderDataView,&OrderModelView::orderDataChanged,
            this, &OrderModel::handleOrderDataChanged);

    m_discount = "0.0";
    m_subTotal = "0.0";
    m_total = "0.0";
    m_printerStatusSrc = "qrc:/icons/ic_print_error.png";
    m_paymentMethod = 0;
}

QString OrderModel::printerStatusSrc() const
{
    return m_printerStatusSrc;
}

void OrderModel::setPrinterStatusSrc(const QString &newPrinterStatusSrc)
{
    if (m_printerStatusSrc == newPrinterStatusSrc)
        return;
    m_printerStatusSrc = newPrinterStatusSrc;
    emit printerStatusSrcChanged();
}

QString OrderModel::discountPercent() const
{
    return m_discountPercent;
}

void OrderModel::setDiscountPercent(const QString &newDiscountPercent)
{
    if (m_discountPercent == newDiscountPercent)
        return;
    m_discountPercent = newDiscountPercent;
    emit discountPercentChanged();
}

EntityVoucher *OrderModel::voucher() const
{
    return m_voucher;
}

void OrderModel::setVoucher(EntityVoucher *newVoucher)
{
    m_voucher = newVoucher;
    setDiscountPercent(QString::number(m_voucher->discountValue()));
    handleOrderDataChanged();
}

int OrderModel::paymentMethod() const
{
    return m_paymentMethod;
}

void OrderModel::setPaymentMethod(int newPaymentMethod)
{
    if (m_paymentMethod == newPaymentMethod)
        return;
    m_paymentMethod = newPaymentMethod;
    emit paymentMethodChanged();
}

QString OrderModel::cash() const
{
    return m_cash;
}

void OrderModel::setCash(const QString &newCash)
{
    qDebug() << __FUNCTION__ << newCash;
    m_cash = newCash;
    emit cashChanged();
}

QList<OrderData *> OrderModel::getOrderData()
{
    return m_orderDataView->getData();
}

QString OrderModel::change() const
{
    qDebug() << __FUNCTION__ << m_change;
    return m_change;
}

void OrderModel::setChange(const QString &newChange)
{
    if (m_change == newChange)
        return;
    m_change = newChange;
    emit changeChanged();
}

void OrderModel::addOrderData(EntityMenuItem *item, int size)
{
    qDebug() << __FUNCTION__ << item->itemId() << " - " << size;
    m_orderDataView->addOrderData(item, size);
}

QObject *OrderModel::orderDataView() const
{
    return static_cast<QObject*>(m_orderDataView);
}

OrderModelView *OrderModel::getOrderDataView()
{
    return m_orderDataView;
}

void OrderModel::updateOrderItem(QString orderDataId, int size)
{
    m_orderDataView->updateOrderItem(orderDataId, size);
}

void OrderModel::removeOrderItem(QString orderDataId)
{
    m_orderDataView->removeOrderItem(orderDataId);
}

void OrderModel::addToppingData(int idx, EntityMenuItem *item, int size)
{
    m_orderDataView->addToppingData(idx, item, size);
}

void OrderModel::removeToppingItem(QString orderDataId)
{
    m_orderDataView->removeToppingItem(orderDataId);
}

void OrderModel::handleOrderDataChanged()
{
    qDebug() << __FUNCTION__;
    float subtotalF = m_orderDataView->getTotal();
    float discountF = 0.0;
    if(m_voucher != nullptr){
        discountF = subtotalF * ((float)m_voucher->discountValue() / 100.0);
        qDebug() << "[ORDER] Voucher is applied " << m_voucher->discountValue() << " - " << discountF;
    }
    float totalF = subtotalF - discountF;

    setSubTotal(Misc::Utilities::formatFloat(subtotalF));
    setDiscount(Misc::Utilities::formatFloat(discountF));
    setTotal(Misc::Utilities::formatFloat(totalF));
}

QString OrderModel::total() const
{
    qDebug() << __FUNCTION__ << m_total;
    return m_total;
}

void OrderModel::setTotal(const QString &newTotal)
{
    if (m_total == newTotal)
        return;
    m_total = newTotal;
    emit totalChanged();
}

void OrderModel::clearOrder()
{
    m_orderDataView->clearOrder();
    setTotal(0);
    setSubTotal(0);
    setDiscount(0);
    if(m_voucher != nullptr){
        setDiscountPercent("");
        delete m_voucher;
        m_voucher = nullptr;
    }
}

QString OrderModel::discount() const
{
    return m_discount;
}

void OrderModel::setDiscount(const QString &newDisCount)
{
    m_discount = newDisCount;
    emit disCountChanged();
}

QString OrderModel::subTotal() const
{
    return m_subTotal;
}

void OrderModel::setSubTotal(const QString &newSubTotal)
{
    m_subTotal = newSubTotal;
    emit subTotalChanged();
}
