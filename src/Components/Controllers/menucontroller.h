#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include "icontroller.h"
#include "../Database/qocategorytable.h"
#include "../Database/qomenuitemtable.h"

class MenuController : public IController
{
    Q_OBJECT
public:
    explicit MenuController(QObject *parent = nullptr);
    MenuController(const QString &tag, QObject* parent = nullptr);

public slots:
    void syncData();
    bool addCat(QString cateName);
    bool removeCat(int catId);
    bool updateCat(int catID, QString newName);

    bool removeMenuItem(int menuItemId);
    bool addMenuItem(QString name,QString avt, int catIdx, QString price, QString priceM, QString priceL);
    bool updateMenuItem(int itemId, QString avt, QString name, int catIdx, QString price, QString priceM, QString priceL);

private:
    QOCategoryTable m_catTable;
    QOMenuItemTable m_menuTable;
};

#endif // MENUCONTROLLER_H
