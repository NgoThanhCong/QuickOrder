#include "reportmodel.h"

ReportModel::ReportModel(QObject *parent)
    : IModel{parent}
{
    init();
}

ReportModel::ReportModel(const QString &name) : IModel(name)
{
    init();
}

QVariantList ReportModel::bestSellerItems() const
{
    QVariantList items;
    for(auto item : m_bestSellerItems){
        items.append(QVariant::fromValue<EntityBestSeller*>(item));
    }
    return items;
}

void ReportModel::setBestSellerItems(const QList<EntityBestSeller *> &newBestSellerItems)
{
    qDeleteAll(m_bestSellerItems);
    m_bestSellerItems.clear();

    m_bestSellerItems.append(newBestSellerItems);
    emit bestSellerItemsChanged();
}

QVariant ReportModel::totalOrder() const
{
    return QVariant::fromValue<EntityInfo*>(m_totalOrder);
}

void ReportModel::setTotalOrder(EntityInfo *newTotalOrder)
{
    if(m_totalOrder != nullptr){
    delete m_totalOrder;
    }
    m_totalOrder = newTotalOrder;
    emit totalOrderChanged();
}

QVariant ReportModel::totalIncomeCash() const
{
    return QVariant::fromValue<EntityInfo*>(m_totalIncomeCash);
}

void ReportModel::setTotalIncomeCash(EntityInfo *newTotalIncomeCash)
{
    if(m_totalIncomeCash != nullptr){
        delete m_totalIncomeCash;
    }
    m_totalIncomeCash = newTotalIncomeCash;
    emit totalIncomeCashChanged();
}

QVariant ReportModel::totalIncomeBanking() const
{
    return QVariant::fromValue<EntityInfo*>(m_totalIncomeBanking);
}

void ReportModel::setTotalIncomeBanking(EntityInfo *newTotalIncomeBanking)
{
    if(m_totalIncomeBanking != nullptr){
        delete m_totalIncomeBanking;
    }
    m_totalIncomeBanking = newTotalIncomeBanking;
    emit totalIncomeBankingChanged();
}

QVariant ReportModel::totalIncome() const
{
    return QVariant::fromValue<EntityInfo*>(m_totalIncome);
}

void ReportModel::setTotalIncome(EntityInfo *newTotalIncome)
{
    if(m_totalIncome != nullptr){
        delete m_totalIncome;
    }
    m_totalIncome = newTotalIncome;
    emit totalIncomeChanged();
}

QVariantList ReportModel::categoryStatistic() const
{
    QVariantList items;
    for(auto item : m_categoryStatistic){
        items.append(QVariant::fromValue<EntityCategoryStatistic*>(item));
    }
    return items;
}

void ReportModel::setCategoryStatistic(const QList<EntityCategoryStatistic *> &newCategoryStatistic)
{
    qDeleteAll(m_categoryStatistic);
    m_categoryStatistic.clear();

    if(newCategoryStatistic.length() <= 5){
        m_categoryStatistic.append(newCategoryStatistic);
    }else{
        EntityCategoryStatistic* others = new EntityCategoryStatistic();
        others->setName("Others");
        for(int i=0;i<newCategoryStatistic.length(); i++){
            if(i < 5) m_categoryStatistic.append(newCategoryStatistic[i]);
            else {
                others->setTotalAmount(others->totalAmount() + newCategoryStatistic[i]->totalAmount());
                delete newCategoryStatistic[i];
            }
        }
        m_categoryStatistic.append(others);
    }
    emit categoryStatisticChanged();
}

QVariantList ReportModel::dateStatistic() const
{
    QVariantList items;
    for(auto item : m_dateStatistic){
        items.append(QVariant::fromValue<EntityDateValue*>(item));
    }
    return items;
}

void ReportModel::setDateStatistic(const QList<EntityDateValue *> &newDateStatistic)
{
    qDeleteAll(m_dateStatistic);
    m_dateStatistic.clear();

    m_dateStatistic.append(newDateStatistic);
    emit dateStatisticChanged();
}

int ReportModel::getDateStatisticSize()
{
    m_dateStatistic.size();
}

void ReportModel::init()
{
    m_totalOrder = nullptr;
    m_totalIncome = nullptr;
    m_totalIncomeBanking = nullptr;
    m_totalIncomeCash = nullptr;
}
