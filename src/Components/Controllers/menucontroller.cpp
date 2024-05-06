#include "menucontroller.h"

MenuController::MenuController(QObject *parent)
    : IController{parent}
{

}

MenuController::MenuController(const QString &tag, QObject *parent) : IController(tag, parent)
{

}

void MenuController::syncData()
{
    qDebug() << "[Category Syncing]";
    MenuModel* model = getModel<MenuModel>();
    model->setCats(m_catTable.getAll());
    model->setMenuItems(m_menuTable.getAll());
}

bool MenuController::addCat(QString cateName)
{
    EntityCategory eCat;
    eCat.setName(cateName);

    return m_catTable.insert(eCat);
}

bool MenuController::removeCat(int catId)
{
    qDebug() << "[Remove CAT]"  << catId;
    if(m_menuTable.removeByCatId(catId)){
        m_catTable.remove(catId);
        return true;
    }
    return false;
}

bool MenuController::updateCat(int catID, QString newName)
{
    EntityCategory eCat;
    eCat.setCategoryId(catID);
    eCat.setName(newName);
    return m_catTable.update(eCat);
}

bool MenuController::removeMenuItem(int menuItemId)
{
    return m_menuTable.remove(menuItemId);
}

bool MenuController::addMenuItem(QString name, QString avt,int catIdx, QString price, QString priceM, QString priceL)
{
    MenuModel* model = getModel<MenuModel>();
    EntityMenuItem mItem;
    mItem.setName(name);
    if(avt != "qrc:/images/default_item_img.jpg"){
        avt = storeImage(avt);
        qDebug() << "Image is stored:" << avt;
    }
    mItem.setImage(avt);
    mItem.setCategoryId(model->getCatIdByIdx(catIdx));
    mItem.setPrice(price.toFloat());
    mItem.setPriceM(priceM.toFloat());
    mItem.setPriceL(priceL.toFloat());
    mItem.printDebug();

    return m_menuTable.insert(mItem);
}

bool MenuController::updateMenuItem(int itemId, QString name,QString avt , int catIdx, QString price, QString priceM, QString priceL)
{
    MenuModel* model = getModel<MenuModel>();
    EntityMenuItem mItem;
    mItem.setItemId(itemId);
    mItem.setName(name);
    if(avt != "qrc:/images/default_item_img.jpg"){
        avt = storeImage(avt);
        qDebug() << "Image is stored:" << avt;
    }
    mItem.setImage(avt);
    mItem.setCategoryId(model->getCatIdByIdx(catIdx));
    mItem.setPrice(price.toFloat());
    mItem.setPriceM(priceM.toFloat());
    mItem.setPriceL(priceL.toFloat());
    mItem.printDebug();

    return m_menuTable.update(mItem);
}
