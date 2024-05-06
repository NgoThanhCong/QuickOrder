#ifndef REPORTMODEL_H
#define REPORTMODEL_H

#include "imodel.h"
#include "../Database/entity_statistic/entitybestseller.h"
#include "../Database/entity_statistic/entityinfo.h"
#include "../Database/entity_statistic/entitycategorystatistic.h"
#include "../Database/entity_statistic/entitydatevalue.h"

class ReportModel : public IModel
{
    Q_OBJECT
public:
    explicit ReportModel(QObject *parent = nullptr);
    ReportModel(const QString& name);

    QVariantList bestSellerItems() const;
    void setBestSellerItems(const QList<EntityBestSeller *> &newBestSellerItems);

    QVariant totalOrder() const;
    void setTotalOrder(EntityInfo *newTotalOrder);

    QVariant totalIncomeCash() const;
    void setTotalIncomeCash(EntityInfo *newTotalIncomeCash);

    QVariant totalIncomeBanking() const;
    void setTotalIncomeBanking(EntityInfo *newTotalIncomeBanking);

    QVariant totalIncome() const;
    void setTotalIncome(EntityInfo *newTotalIncome);

    QVariantList categoryStatistic() const;
    void setCategoryStatistic(const QList<EntityCategoryStatistic *> &newCategoryStatistic);

    QVariantList dateStatistic() const;
    void setDateStatistic(const QList<EntityDateValue *> &newDateStatistic);

signals:
    void bestSellerItemsChanged();

    void totalOrderChanged();

    void totalIncomeCashChanged();

    void totalIncomeBankingChanged();

    void totalIncomeChanged();

    void categoryStatisticChanged();

    void dateStatisticChanged();

public slots:
    int getDateStatisticSize();

private:
    void init();

    QList<EntityBestSeller*> m_bestSellerItems;
    QList<EntityCategoryStatistic*> m_categoryStatistic;
    QList<EntityDateValue*> m_dateStatistic;
    EntityInfo* m_totalOrder;
    EntityInfo* m_totalIncome;
    EntityInfo* m_totalIncomeCash;
    EntityInfo* m_totalIncomeBanking;

    Q_PROPERTY(QVariantList bestSellerItems READ bestSellerItems NOTIFY bestSellerItemsChanged FINAL)
    Q_PROPERTY(QVariant totalOrder READ totalOrder NOTIFY totalOrderChanged FINAL)
    Q_PROPERTY(QVariant totalIncomeCash READ totalIncomeCash NOTIFY totalIncomeCashChanged FINAL)
    Q_PROPERTY(QVariant totalIncomeBanking READ totalIncomeBanking  NOTIFY totalIncomeBankingChanged FINAL)
    Q_PROPERTY(QVariant totalIncome READ totalIncome  NOTIFY totalIncomeChanged FINAL)
    Q_PROPERTY(QVariantList categoryStatistic READ categoryStatistic NOTIFY categoryStatisticChanged FINAL)
    Q_PROPERTY(QVariantList dateStatistic READ dateStatistic NOTIFY dateStatisticChanged FINAL)
};

#endif // REPORTMODEL_H
