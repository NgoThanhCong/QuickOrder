#ifndef MENUMODEL_H
#define MENUMODEL_H

#include "imodel.h"
#include "../Database/entity/entitycategory.h"
#include "../Database/entity/entitymenuitem.h"
#define NON_FILTER -1

class MenuModel : public IModel
{
    Q_OBJECT
public:
    explicit MenuModel(QObject *parent = nullptr);
    MenuModel(const QString& name);

    QVariantList cats() const;
    void setCats(const QList<EntityCategory *> &newCats);

    QVariantList menuItems() const;
    void setMenuItems(const QList<EntityMenuItem *> &newMenuItems);

    int getCatIdByIdx(int idx);
    EntityMenuItem* getMenuItemById(int id);

    int filterKey() const;
    void setFilterKey(const int &newFilterKey);

    QVariantList filtedItems() const;
    void setFiltedItems(const QList<EntityMenuItem *> &newFiltedItems);

public slots:
    QString getCatById(int catId);
    QStringList getCats();
    int getIdxByCatId(int catID);
    void clearFilter();

signals:
    void catsChanged();
    void menuItemsChanged();
    void filterKeyChanged();
    void filtedItemsChanged();

private slots:
    void handleFilterKeyChanged();
    void refreshFilterItems();

private:
    QList<EntityCategory*> m_cats;
    QList<EntityMenuItem*> m_menuItems;

    QList<EntityMenuItem*> m_filtedItems;
    int m_filterKey;

    Q_PROPERTY(QVariantList cats READ cats NOTIFY catsChanged)
    Q_PROPERTY(QVariantList menuItems READ menuItems NOTIFY menuItemsChanged FINAL)
    Q_PROPERTY(QVariantList filtedItems READ filtedItems NOTIFY filtedItemsChanged FINAL)
    Q_PROPERTY(int filterKey READ filterKey WRITE setFilterKey NOTIFY filterKeyChanged FINAL)
};

#endif // MENUMODEL_H
