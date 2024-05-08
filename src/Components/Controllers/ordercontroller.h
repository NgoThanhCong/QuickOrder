#ifndef ORDERCONTROLLER_H
#define ORDERCONTROLLER_H

#include "icontroller.h"
#include "../Database/qoordertable.h"
#include "../Database/qoorderitemtable.h"
#include "../Database/qotransactiontable.h"
#include "../Database/qovouchertable.h"
#include "../timemanager.h"
#include "../WrapperServices/printerwrapperservice.h"
#include "settingscontroller.h"

class OrderController : public IController
{
    Q_OBJECT
public:
    explicit OrderController(QObject *parent = nullptr);
    OrderController(const QString &tag, QObject* parent = nullptr);
    ~OrderController();

public slots:
    void syncData();
    void addOrderItem(int itemId, int size);
    void removeOrderItem(QString orderDataId);
    void updateOrderItem(QString orderDataId,int quantity);

    void addToppingItem(int idx, int itemId, int size);
    void removeToppingItem(QString orderDataId);
    bool applyVoucher(QString code);
    void checkout(QVariant userId);
    void handlePrinterStatusChanged(int);
    void clearOrder();

private:
    QOMenuItemTable m_menuitemTable;
    QOOrderTable m_orderTable;
    QOOrderItemTable m_orderItemTable;
    QOTransactionTable m_transTable;
    QOVoucherTable m_voucherTable;
    QString alignText(QString,QString);
    QString alignCenter(const QString &text, int length);

    void handleCheckingout(QVariant userId);
    QSettings m_settings;
};

#endif // ORDERCONTROLLER_H
