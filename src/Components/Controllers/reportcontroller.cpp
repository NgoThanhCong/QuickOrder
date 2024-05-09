#include "reportcontroller.h"

ReportController::ReportController(QObject *parent)
    : IController{parent}
{}

ReportController::ReportController(const QString &tag, QObject *parent)
    : IController(tag, parent)
{

}

void ReportController::exportData(int days)
{
    qDebug() << __FUNCTION__;
    QString queryStr = "SELECT "
                       "o.order_id, "
                       "o.order_date_time, "
                       "oi.item_id, "
                       "o.total_amount AS total_amount,"
                       "m.name AS item_name, "
                       "oi.quantity, "
                       "oi.item_size, "
                       "oi.quantity * (CASE oi.item_size "
                       "WHEN 1 THEN m.price "
                       "WHEN 2 THEN m.price_medium "
                       "WHEN 3 THEN m.price_large "
                       "ELSE 0 END) AS subtotal, "
                       "t.payment_method, "
                       "t.amount, "
                       "u.name AS user_name "
                       "FROM "
                       "ORDER_TABLE o "
                       "JOIN "
                       "ORDER_ITEMS_TABLE oi ON o.order_id = oi.order_id "
                       "JOIN "
                       "MENU_TABLE m ON oi.item_id = m.item_id "
                       "JOIN "
                       "TRANSACTION_TABLE t ON o.order_id = t.order_id "
                       "JOIN "
                       "USER_TABLE u ON o.user_id = u.user_id "
                       "WHERE "
                       "substr(order_date_time, 7, 4) || '-' || substr(order_date_time, 4, 2) || '-' || substr(order_date_time, 1, 2) >= date('now', '-%1 days') "
                       "ORDER BY "
                       "o.order_id;";
    QSqlQuery query(queryStr.arg(days));

    QStringList dataToWrite;
    QSet<QString> orderIdSet;
    dataToWrite << "Order ID,Order Date Time,Payment Method,Item ID,Item Name,Quantity,Item Size,Subtotal,Amount,User Name";
    if (query.exec()) {
        while (query.next()) {
            QString line;
            QString orderId = query.value("order_id").toString();
            QString orderTime = query.value("order_date_time").toString();
            int paymentMethod = query.value("payment_method").toInt();
            QString pmMethod = paymentMethod == 0 ? "Cash" : "Banking";
            QString total = query.value("total_amount").toString();
            QString user = Misc::Utilities::convertVietnameseToEnglish(query.value("user_name").toString());
            if(orderIdSet.contains(orderId)){
                orderId = "";
                orderTime = "";
                pmMethod = "";
                total = "";
                user = "";
            }else{
                orderIdSet.insert(orderId);
            }
            line.append(orderId + ",");
            line.append(orderTime + ",");
            line.append(pmMethod + ",");
            line.append(query.value("item_id").toString() + ",");
            line.append(query.value("item_name").toString() + ",");
            line.append(query.value("quantity").toString() + ",");
            line.append(SizeToText(query.value("item_size").toInt()) + ",");
            line.append(query.value("subtotal").toString() + ",");
            line.append(total + ",");
            line.append(user);
            dataToWrite << line;
        }
    }
    Misc::Utilities::writeCsv(dataToWrite, QString::number(days).append("days"));
}

void ReportController::syncData()
{
    getDataBestSeller();
    getTotalOrder();
    getTotalIncome();
    getTotalCashIncome();
    getTotalBankingIncome();
    analyzeByCategory();
    analyzeRevenueByDate();
}

void ReportController::getDataBestSeller()
{
    qDebug() << __FUNCTION__;
    QSqlQuery query;
    QString queryString = "SELECT "
                          "m.name AS menu_item, "
                          "COUNT(oi.item_id) AS total_ordered "
                          "FROM "
                          "ORDER_ITEMS_TABLE oi "
                          "JOIN MENU_TABLE m ON oi.item_id = m.item_id "
                          "JOIN CATEGORY_TABLE c ON m.category_id = c.category_id "
                          "JOIN ORDER_TABLE o ON oi.order_id = o.order_id "
                          "WHERE "
                          "c.name != 'Topping' "
                          "AND o.order_date_time >= DATE('now', '-7 days') "
                          "GROUP BY "
                          "oi.item_id "
                          "ORDER BY "
                          "total_ordered DESC;";

    if (query.exec(queryString)) {
        qDebug() << "Query executed successfully:";
        QList<EntityBestSeller*> m_bs;
        while (query.next()) {
            QString menu_item = query.value("menu_item").toString();
            int total_ordered = query.value("total_ordered").toInt();
            EntityBestSeller* ebs = new EntityBestSeller();
            ebs->setItemName(menu_item);
            ebs->setQuantity(total_ordered);
            m_bs.append(ebs);
        }
        ReportModel* model = getModel<ReportModel>();
        model->setBestSellerItems(m_bs);
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}

void ReportController::getTotalIncome()
{
    QSqlQuery query;

    QString queryString = "SELECT SUM(total_amount) AS total_money "
                          "FROM ORDER_TABLE "
                          "WHERE order_date_time >= DATE('now', '-7 days');";

    if (query.exec(queryString)) {
        if (query.next()) {
            int totalOrders = query.value("total_money").toFloat();
            EntityInfo* info = new EntityInfo();
            info->setName("Total Income");
            info->setInfo(QString::number(totalOrders));
            ReportModel* model = getModel<ReportModel>();
            model->setTotalIncome(info);
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}

void ReportController::getTotalOrder()
{
    qDebug() << __FUNCTION__;
    QSqlQuery query;

    QString queryString = "SELECT COUNT(order_id) AS total_orders "
                          "FROM ORDER_TABLE "
                          "WHERE order_date_time >= DATE('now', '-7 days');";

    if (query.exec(queryString)) {
        if (query.next()) {
            int totalOrders = query.value("total_orders").toInt();
            EntityInfo* info = new EntityInfo();
            info->setName("Total Order");
            info->setInfo(QString::number(totalOrders));
            ReportModel* model = getModel<ReportModel>();
            model->setTotalOrder(info);
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}

void ReportController::getTotalCashIncome()
{
    qDebug() << __FUNCTION__;
    EntityInfo* info = new EntityInfo();
    info->setName("Cash");
    info->setInfo(getTotalAmountMoneyByPaymentMethod(0));
    ReportModel* model = getModel<ReportModel>();
    model->setTotalIncomeCash(info);

}

void ReportController::getTotalBankingIncome()
{
    qDebug() << __FUNCTION__;
    EntityInfo* info = new EntityInfo();
    info->setName("Banking");
    info->setInfo(getTotalAmountMoneyByPaymentMethod(1));
    ReportModel* model = getModel<ReportModel>();
    model->setTotalIncomeBanking(info);
}

void ReportController::analyzeByCategory()
{
    qDebug() << __FUNCTION__;
    QSqlQuery query;
    QString sqlQuery = "SELECT "
                       "    c.name AS category_name, "
                       "    SUM(oi.quantity * m.price) AS total_amount "
                       "FROM "
                       "    ORDER_TABLE o "
                       "INNER JOIN "
                       "    ORDER_ITEMS_TABLE oi ON o.order_id = oi.order_id "
                       "INNER JOIN "
                       "    MENU_TABLE m ON oi.item_id = m.item_id "
                       "INNER JOIN "
                       "    CATEGORY_TABLE c ON m.category_id = c.category_id "
                       "WHERE "
                       "    o.order_date_time >= DATE('now', '-7 days') "
                       "GROUP BY "
                       "    c.category_id "
                       "ORDER BY "
                       "    total_amount DESC";

    if (query.exec(sqlQuery)) {
        QList<EntityCategoryStatistic*> ecsList;
        while (query.next()) {
            EntityCategoryStatistic* ecs = new EntityCategoryStatistic();
            ecs->setTotalAmount(query.value("total_amount").toFloat());
            ecs->setName(query.value("category_name").toString());
            qDebug() << __FUNCTION__ << " - " << ecs->name() << " - " << ecs->totalAmount();
            ecsList.append(ecs);
        }
        ReportModel* model = getModel<ReportModel>();
        model->setCategoryStatistic(ecsList);
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}

void ReportController::analyzeRevenueByDate()
{
    qDebug() << __FUNCTION__;
    QSqlQuery query;
    QString sql = R"(
        SELECT
          SUBSTR(o.order_date_time, 1, 10) as order_date,
          SUM(o.total_amount) as daily_sales
        FROM
          ORDER_TABLE o
        WHERE
          SUBSTR(o.order_date_time, 1, 10) >= DATE('now', '-6 days')
        GROUP BY
          order_date
        ORDER BY
          order_date DESC
    )";

    if (query.exec(sql)) {
        QList<EntityDateValue*> items;
        while (query.next()) {
            QString order_date = query.value(0).toString();
            float daily_sales = query.value(1).toFloat();
            EntityDateValue* edv = new EntityDateValue();
            edv->setDate(QDateTime::fromString(order_date, "dd.MM.yyyy"));
            edv->setValue(daily_sales);
            items.append(edv);
            qDebug() << "Date:" << order_date << ", Daily Sales:" << daily_sales;
        }
        ReportModel* model = getModel<ReportModel>();
        model->setDateStatistic(items);
    }
}

QString ReportController::getTotalAmountMoneyByPaymentMethod(int method)
{
    qDebug() << __FUNCTION__;
    QSqlQuery query;
    QString queryString = "SELECT SUM(ot.total_amount) AS total_money "
                          "FROM ORDER_TABLE ot "
                          "JOIN TRANSACTION_TABLE tt ON ot.order_id = tt.order_id "
                          "WHERE ot.order_date_time >= DATE('now', '-7 days') "
                          "AND tt.payment_method = :paymentMethod;";

    query.prepare(queryString);
    query.bindValue(":paymentMethod", method);

    if (query.exec()) {
        if (query.next()) {
            return QString::number(query.value("total_money").toFloat());
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
    return 0;
}

QString ReportController::SizeToText(int size)
{
    switch (size) {
    case 0:
        return "S";
    case 1:
        return "M";
    case 2:
        return "L";
    default:
        return "";
    }
}
