#include "menumodel.h"

MenuModel::MenuModel(QObject *parent)
    : IModel{parent}
{}

MenuModel::MenuModel(const QString &name) : IModel(name)
{
    connect(this, &MenuModel::filterKeyChanged, this, &MenuModel::handleFilterKeyChanged);
    clearFilter();
}

QVariantList MenuModel::cats() const
{
    QVariantList res;
    for(auto cat : m_cats){
        res.append(QVariant::fromValue<EntityCategory*>(cat));
    }
    return res;
}

void MenuModel::setCats(const QList<EntityCategory *> &newCats)
{
    qDebug() << __FUNCTION__ << newCats.length();
    qDeleteAll(m_cats);
    m_cats.clear();

    m_cats.append(newCats);
    emit catsChanged();
}

QVariantList MenuModel::menuItems() const
{
    QVariantList res;
    for(auto item : m_menuItems){
        res.append(QVariant::fromValue<EntityMenuItem*>(item));
    }
    return res;
}

void MenuModel::setMenuItems(const QList<EntityMenuItem *> &newMenuItems)
{
    qDeleteAll(m_menuItems);
    m_menuItems.clear();
    m_filtedItems.clear();
    qDeleteAll(m_menuItems);

    m_menuItems.append(newMenuItems);
    refreshFilterItems();
    emit menuItemsChanged();
}

int MenuModel::getCatIdByIdx(int idx)
{
    if(idx < m_cats.length()){
        return m_cats.at(idx)->categoryId();
    }
    return 0;
}

EntityMenuItem *MenuModel::getMenuItemById(int id)
{
    for(int i=0;i<m_menuItems.length();i++){
        if(m_menuItems[i]->itemId() == id){
            return m_menuItems[i];
        }
    }
    return nullptr;
}

int MenuModel::getIdxByCatId(int catID)
{
    for(int i=0;i<m_cats.length();i++){
        if(m_cats[i]->categoryId() == catID){
            return i;
        }
    }
    return 0;
}

void MenuModel::clearFilter()
{
    setFilterKey(NON_FILTER);
}

void MenuModel::handleFilterKeyChanged()
{
    qDebug() << __FUNCTION__;
    refreshFilterItems();
    emit filtedItemsChanged();
}

void MenuModel::refreshFilterItems()
{
    m_filtedItems.clear();
    for(auto menu_item : qAsConst(m_menuItems)){
        if(m_filterKey == NON_FILTER){
            m_filtedItems.append(menu_item);
        }else{
            if(menu_item->categoryId() == m_filterKey){
                m_filtedItems.append(menu_item);
            }
        }
    }
}

QVariantList MenuModel::filtedItems() const
{
    QVariantList res;
    for(auto item : m_filtedItems){
        res.append(QVariant::fromValue<EntityMenuItem*>(item));
    }
    return res;
}

void MenuModel::setFiltedItems(const QList<EntityMenuItem *> &newFiltedItems)
{
    if (m_filtedItems == newFiltedItems)
        return;
    m_filtedItems = newFiltedItems;
    emit filtedItemsChanged();
}

int MenuModel::filterKey() const
{
    return m_filterKey;
}

void MenuModel::setFilterKey(const int &newFilterKey)
{
    if(newFilterKey == m_filterKey){
        clearFilter();
        return;
    }
    m_filterKey = newFilterKey;
    emit filterKeyChanged();
}

QString MenuModel::getCatById(int catId)
{
    for(auto cat : qAsConst(m_cats)){
        if(cat->categoryId() == catId){
            return cat->name();
        }
    }
    return "";
}

QStringList MenuModel::getCats()
{
    QStringList res;
    for(auto cat : qAsConst(m_cats)){
        res.append(cat->name());
    }
    return res;
}
