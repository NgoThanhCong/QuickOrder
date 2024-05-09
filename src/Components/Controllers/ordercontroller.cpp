#include "ordercontroller.h"

OrderController::OrderController(QObject *parent)
    : IController{parent}
{}

OrderController::OrderController(const QString &tag, QObject *parent)
    : IController(tag, parent)
{

}

OrderController::~OrderController()
{
    PrinterService->closePrinter();
}

void OrderController::syncData()
{
    connect(PrinterService, &PrinterWrapperService::onPrinterStatusChanged, this, &OrderController::handlePrinterStatusChanged);
    handlePrinterStatusChanged(PrinterService->printerStatus());
}

void OrderController::addOrderItem(int itemId, int size)
{    
    OrderModel* model = getModel<OrderModel>();
    qDebug() << __FUNCTION__ << itemId << " - " << size;
    model->addOrderData(m_menuitemTable.getMenuItemById(itemId), size);
}

void OrderController::removeOrderItem(QString orderDataId)
{
    OrderModel* model = getModel<OrderModel>();
    model->removeOrderItem(orderDataId);
}

void OrderController::updateOrderItem(QString orderDataId, int quantity)
{
    OrderModel* model = getModel<OrderModel>();
    model->updateOrderItem(orderDataId, quantity);
}

void OrderController::addToppingItem(int idx, int itemId, int size)
{
    OrderModel* model = getModel<OrderModel>();
    qDebug() << __FUNCTION__ << itemId << " - " << size;
    model->addToppingData(idx, m_menuitemTable.getMenuItemById(itemId), size);
}

void OrderController::removeToppingItem(QString orderDataId)
{
    OrderModel* model = getModel<OrderModel>();
    model->removeToppingItem(orderDataId);
}

bool OrderController::applyVoucher(QString code)
{
    OrderModel* model = getModel<OrderModel>();
    EntityVoucher* voucher = m_voucherTable.getVoucherByCode(code);
    if(voucher == nullptr
        || !TimeManager::getIntance()->isGreaterThanCurrentDate(voucher->validDate())
        || (voucher->status() == 1)
        ){
        return false;
    }

    model->setVoucher(voucher);
    return true;
}

void OrderController::checkout(QVariant userId)
{
    qDebug() << __FUNCTION__;
    OrderModel* model = getModel<OrderModel>();
    handleCheckingout(userId);
    if(model->voucher() != nullptr){
        m_voucherTable.updateStatus(model->voucher());
    }
    model->clearOrder();
}

void OrderController::handlePrinterStatusChanged(int status)
{
    qDebug() << __FUNCTION__ << " - " << status;
    OrderModel* model = getModel<OrderModel>();
    if(status == PRINTER_STATUS::PRINTER_READY){
        model->setPrinterStatusSrc("qrc:/icons/ic_print.png");
    }else if(status  == PRINTER_IS_OUT_OF_PAPER){
        model->setPrinterStatusSrc("qrc:/icons/ic_out_of_paper.png");
    }else{
        model->setPrinterStatusSrc("qrc:/icons/ic_print_error.png");
    }
}

void OrderController::clearOrder()
{
    OrderModel* model = getModel<OrderModel>();
    model->clearOrder();
}

QString OrderController::alignText(QString title, QString content)
{
    QString res = "";
    if(title.length() + content.length() > LINE_SIZE){
        res += (title.leftJustified(LINE_SIZE) + "\n");
        res += content.rightJustified(LINE_SIZE);

        // res = title................
        //       ..............content
    }else{
        int padSpaces = LINE_SIZE - content.length();
        res = title;
        res = res.leftJustified(padSpaces);
        res += content;
        res += "\n";
    }

    qDebug() << "Align Res: " << res;
    return res;
}

QString OrderController::alignCenter(const QString &text, int length)
{
    int totalSpaces = length - text.length();
    int leftSpaces = totalSpaces / 2;
    int rightSpaces = totalSpaces - leftSpaces;

    // Add spaces to both left and right of the text
    QString centeredText = QString(" ").repeated(leftSpaces) + text + QString(" ").repeated(rightSpaces);

    return centeredText;
}

void OrderController::handleCheckingout(QVariant user)
{
    qDebug() << __FUNCTION__;
    OrderModel* model = getModel<OrderModel>();
    EntityOrder eo;
    EntityTransaction eTrans;
    QList<OrderData *> orderDatas = model->getOrderData();
    EntityUser* eu = user.value<EntityUser*>();
    eu->printDebug();

    eo.setUserId(eu->userId());
    eo.setOrderId(m_orderTable.getNextId());
    eo.setTotalAmount(model->total().toFloat());
    eo.setChange(model->change().toFloat());
    eo.setCash(model->cash().toFloat());
    eo.setOrderDateTime(TimeManager::getIntance()->currentTimeDb());
    int voucherId = -1;
    if(model->voucher() != nullptr){
        voucherId = model->voucher()->voucherId();
        model->voucher()->setStatus(1); // USED
    }
    eo.setVoucherId(voucherId);

    m_orderTable.insert(eo);

    foreach(OrderData* od, orderDatas){
        EntityOrderItem eoi;
        eoi.setItemId(od->itemId());
        eoi.setQuantity(od->quantity());
        eoi.setItemSize(od->size());
        eoi.setOrderId(eo.orderId());

        m_orderItemTable.insert(eoi);
    }

    eTrans.setAmount(model->cash().toFloat());
    eTrans.setOrder_id(eo.orderId());
    eTrans.setPayment_method(model->paymentMethod());

    m_transTable.insert(eTrans);

    //Bill to Print
    QString storeName = m_settings.value(KEY_STORE_NAME).toString();
    QString hotline = m_settings.value(KEY_HOTLINE).toString();
    QString bankName = m_settings.value(KEY_BANKNAME).toString();
    QString bankId = m_settings.value(KEY_BANK_ID).toString();
    QString address = m_settings.value(KEY_ADDRESS).toString();

    QStringList data;
    data << "\n********************************\n";
    data << alignCenter(Misc::Utilities::convertVietnameseToEnglish(storeName), LINE_SIZE);
    data << "\n";
    data << "\n";
    data << QString("Ticket #%1").arg(eo.orderId()).leftJustified(LINE_SIZE);
    data << QString("Time %1").arg(TimeManager::getIntance()->currentDateTime()).leftJustified(LINE_SIZE);
    data << Misc::Utilities::convertVietnameseToEnglish("Staff: " + eu->name()).leftJustified(31) + "\n";
    data << "\n";
    data << Misc::Utilities::convertVietnameseToEnglish(address).leftJustified(LINE_SIZE);
    data << "\n";
    data << "\n";
    data << QString("________________________________");
    data << "\n";
    data << QString("Item     Qty     Price     Total");
    foreach(OrderData* od, orderDatas){
        QString name = QString("%1 (%2)").arg(od->getName()).arg(od->getSize());
        if(name.length() > LINE_SIZE) name = name.left(32) + "\n" + name.right(32);
        data << name.leftJustified(32) + "\n";
        QString line;
        if(!od->isTopping()){
            line = od->getNotes().leftJustified(9,' ');
        }else{
            line = QString("").leftJustified(9,' ');
        }
        QString formattedQuantity =  QString("x%1").arg(QString::number(od->quantity())).leftJustified(5, ' ');
        QString formattedPrice = od->getPriceUnit().rightJustified(8, ' ');
        QString formattedTotal = od->getPrice().rightJustified(10, ' ');
        line = line + formattedQuantity + formattedPrice + formattedTotal + "\n";
        data << line;
        data << "\n";
    }
    data << QString("________________________________");
    data << alignText("Subtotal", model->subTotal());
    data << "\n";
    data << alignText("Discount",model->discount());
    if(model->isCash()){
        data << alignText("Cash",QString::number(model->cash().toFloat(), 'f', 2));
        data << alignText("Change",model->change());
    }else{
        data << alignText("Banking","");
    }
    data << QString("________________________________");
    data << alignText("Total",QString::number(eo.totalAmount(), 'f', 2));
    data << "\n";
    data << "\n";
    data << QString("Give us Feedback: %1").arg(hotline).leftJustified(32,' ');
    data << QString("**** Thank you for visiting ****");
    data << "\n";
    data << "\n";
    data << "\n";

    PrinterService->printText(data);
}
