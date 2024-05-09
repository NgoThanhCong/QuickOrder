#ifndef REPORTCONTROLLER_H
#define REPORTCONTROLLER_H

#include "icontroller.h"
#include <QSql>

class ReportController : public IController
{
    Q_OBJECT
public:
    explicit ReportController(QObject *parent = nullptr);
    ReportController(const QString &tag, QObject* parent = nullptr);

public slots:
    void exportData(int days = 0); // 0 is today.

public:
    void syncData();
private:
    void getDataBestSeller();
    void getTotalIncome();
    void getTotalOrder();
    void getTotalCashIncome();
    void getTotalBankingIncome();
    void analyzeByCategory();
    void analyzeRevenueByDate();

    QString getTotalAmountMoneyByPaymentMethod(int method);// 0 Cash . 1. Banking

    QString SizeToText(int);
};

#endif // REPORTCONTROLLER_H
