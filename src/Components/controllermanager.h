#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <QObject>
#include <QDebug>
#include <QMap>
#include <QQmlContext>

#include "databasemanager.h"
#include "Controllers/titlebarcontroller.h"
#include "Controllers/navigationbarcontroller.h"
#include "Controllers/logincontroller.h"
#include "Controllers/usercontroller.h"
#include "Controllers/menucontroller.h"
#include "Controllers/ordercontroller.h"
#include "Controllers/reportcontroller.h"
#include "Controllers/settingscontroller.h"
#include "Controllers/vouchercontroller.h"
#include "const.h"
#include "WrapperServices/iwrapperservice.h"
#include "WrapperServices/printerwrapperservice.h"

class ControllerManager : public QObject
{
    Q_OBJECT
public:
    explicit ControllerManager(QObject *parent = nullptr);
    void init();
    void registerController(QQmlContext* root);
public slots:
    void onDbConnected();

private:
    void initController();
    void initWrapperServices();
    void initDb();
    QMap<QString, IController*> m_controllers;

    template<class T>
    inline T* getControllerByTag(QString tag)
    {
        if(!m_controllers.contains(tag)) return nullptr;
        return dynamic_cast<T*>(m_controllers.value(tag));
    }
    template<class T>
    inline T* getModelByTag(QString tag)
    {
        if(!m_controllers.contains(tag)) return nullptr;
        return dynamic_cast<T*>(m_controllers.value(tag)->model());
    }
};

#endif // CONTROLLERMANAGER_H
