#include "navigationbarmodel.h"

NavigationBarModel::NavigationBarModel()
{
   init(true);
}

NavigationBarModel::NavigationBarModel(const QString &name) : IModel(name)
{
init(true);
}

const QList<QObject *> &NavigationBarModel::items() const
{
    return m_items;
}

void NavigationBarModel::setItems(const QList<QObject *> &newItems)
{
    if (m_items == newItems)
        return;
    m_items = newItems;
    emit itemsChanged();
}

void NavigationBarModel::init(bool isAdmin)
{
    qDebug() << __FUNCTION__ << "NavigationBarModel";

    m_items.append(new NaviItem("Users", "qrc:/icons/ic_user.png"));
    m_items.append(new NaviItem("Menu", "qrc:/icons/ic_report.png"));
    m_items.append(new NaviItem("Reports", "qrc:/icons/ic_home.png"));
    m_items.append(new NaviItem("Voucher", "qrc:/icons/ic_voucher.png"));
    m_items.append(new NaviItem("Settings", "qrc:/icons/ic_settings.png"));

}
