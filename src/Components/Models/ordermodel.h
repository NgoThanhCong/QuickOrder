#ifndef ORDERMODEL_H
#define ORDERMODEL_H

#include "imodel.h"
#include "ordermodelview.h"
#include "../Database/entity/entityvoucher.h"

class OrderModel : public IModel
{
    Q_OBJECT
public:
    explicit OrderModel(QObject *parent = nullptr);
    OrderModel(const QString& name);

    void addOrderData(EntityMenuItem* item, int size);
    void updateOrderItem(QString, int);
    void removeOrderItem(QString);

    void addToppingData(int idx, EntityMenuItem* item, int size);
    void removeToppingItem(QString);

    QObject *orderDataView() const;
    OrderModelView* getOrderDataView();

    QString subTotal() const;
    void setSubTotal(const QString &newSubTotal);

    QString discount() const;
    void setDiscount(const QString &newDisCount);

    QString total() const;
    void setTotal(const QString &newTotal);
    void clearOrder();

    QString change() const;
    void setChange(const QString &newChange);

    QString cash() const;
    void setCash(const QString &newCash);

    QList<OrderData*> getOrderData();

    int paymentMethod() const;
    void setPaymentMethod(int newPaymentMethod);

    void setVoucher(EntityVoucher *newVoucher);

    EntityVoucher *voucher() const;

    QString discountPercent() const;
    void setDiscountPercent(const QString &newDiscountPercent);

    QString printerStatusSrc() const;
    void setPrinterStatusSrc(const QString &newPrinterStatusSrc);

    bool isCash();

signals:
    void orderDataViewChanged();
    void subTotalChanged();

    void disCountChanged();

    void totalChanged();

    void changeChanged();

    void cashChanged();

    void paymentMethodChanged();

    void discountPercentChanged();

    void isPrinterReadyChanged();

    void printerStatusSrcChanged();

private slots:
    void handleOrderDataChanged();

private:
    void init();
    OrderModelView* m_orderDataView;
    QString m_subTotal;
    QString m_discount;
    QString m_total;
    QString m_cash;
    QString m_change;
    QString m_discountPercent;
    int m_paymentMethod; //0 Cash. 1 Banking
    EntityVoucher* m_voucher;
    QString m_printerStatusSrc;


    Q_PROPERTY(QObject *orderDataView READ orderDataView NOTIFY orderDataViewChanged )
    Q_PROPERTY(QString subTotal READ subTotal WRITE setSubTotal NOTIFY subTotalChanged )
    Q_PROPERTY(QString discount READ discount WRITE setDiscount NOTIFY disCountChanged )
    Q_PROPERTY(QString total READ total WRITE setTotal NOTIFY totalChanged )
    Q_PROPERTY(QString change READ change WRITE setChange NOTIFY changeChanged )
    Q_PROPERTY(QString cash READ cash WRITE setCash NOTIFY cashChanged )
    Q_PROPERTY(int paymentMethod READ paymentMethod WRITE setPaymentMethod NOTIFY paymentMethodChanged )
    Q_PROPERTY(QString discountPercent READ discountPercent NOTIFY discountPercentChanged)
    Q_PROPERTY(QString printerStatusSrc READ printerStatusSrc WRITE setPrinterStatusSrc NOTIFY printerStatusSrcChanged FINAL)
};

#endif // ORDERMODEL_H
