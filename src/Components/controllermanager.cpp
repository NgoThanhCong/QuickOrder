#include "controllermanager.h"

ControllerManager::ControllerManager(QObject *parent) : QObject(parent)
{

}

void ControllerManager::init()
{
    qDebug() << __FUNCTION__;
    initWrapperServices();
    initController();
    initDb();
}

void ControllerManager::initController()
{
    qDebug() << __FUNCTION__;

    // Initialize Controllers
    m_controllers.insert(TAG_TITLEBAR       ,new TitleBarController(TAG_TITLEBAR,this));
    m_controllers.insert(TAG_NAVIGATION_BAR ,new NavigationBarController(TAG_NAVIGATION_BAR,this));
    m_controllers.insert(TAG_LOGINSCREEN    ,new LoginController(TAG_LOGINSCREEN, this));
    m_controllers.insert(TAG_USERSCREEN     ,new UserController(TAG_USERSCREEN, this));
    m_controllers.insert(TAG_MENUSCREEN     ,new MenuController(TAG_MENUSCREEN, this));
    m_controllers.insert(TAG_ORDERSCREEN    ,new OrderController(TAG_ORDERSCREEN, this));
    m_controllers.insert(TAG_REPORTSCREEN   ,new ReportController(TAG_REPORTSCREEN, this));
    m_controllers.insert(TAG_SETTINGSSCREEN ,new SettingsController(TAG_SETTINGSSCREEN, this));
    m_controllers.insert(TAG_VOUCHERSCREEN  ,new VoucherController(TAG_VOUCHERSCREEN, this));

    // Initialize Models
    m_controllers.value(TAG_TITLEBAR)->
            setModel(new TitleBarModel(QString("%1%2").arg(TAG_TITLEBAR,SUFFIX_MODEL)));
    m_controllers.value(TAG_NAVIGATION_BAR)->
            setModel(new NavigationBarModel(QString("%1%2").arg(TAG_NAVIGATION_BAR,SUFFIX_MODEL)));
    m_controllers.value(TAG_LOGINSCREEN)->
            setModel(new LoginModel(QString("%1%2").arg(TAG_LOGINSCREEN,SUFFIX_MODEL)));
    m_controllers.value(TAG_USERSCREEN)->
            setModel(new UserModel(QString("%1%2").arg(TAG_USERSCREEN,SUFFIX_MODEL)));
    m_controllers.value(TAG_MENUSCREEN)->
            setModel(new MenuModel(QString("%1%2").arg(TAG_MENUSCREEN,SUFFIX_MODEL)));
    m_controllers.value(TAG_ORDERSCREEN)->
        setModel(new OrderModel(QString("%1%2").arg(TAG_ORDERSCREEN,SUFFIX_MODEL)));
    m_controllers.value(TAG_REPORTSCREEN)->
        setModel(new ReportModel(QString("%1%2").arg(TAG_REPORTSCREEN,SUFFIX_MODEL)));
    m_controllers.value(TAG_SETTINGSSCREEN)->
        setModel(new SettingsModel(QString("%1%2").arg(TAG_SETTINGSSCREEN,SUFFIX_MODEL)));
    m_controllers.value(TAG_VOUCHERSCREEN)->
        setModel(new VoucherModel(QString("%1%2").arg(TAG_VOUCHERSCREEN,SUFFIX_MODEL)));
}

void ControllerManager::initWrapperServices()
{
    qDebug() << __FUNCTION__;
    PrinterService->init();
}

void ControllerManager::initDb()
{
    qDebug() << __FUNCTION__;
    connect(DatabaseManager::getInstance(), &DatabaseManager::isConnectedChanged, this,
            &ControllerManager::onDbConnected);
    DatabaseManager::getInstance()->connectToDb();
}

void ControllerManager::registerController(QQmlContext* root)
{
    qDebug() << __FUNCTION__;
    for(auto& item : m_controllers.toStdMap())
    {
        item.second->registerType(root);
    }
}

void ControllerManager::onDbConnected()
{
    qDebug() << __FUNCTION__;
    for(auto& item : m_controllers.toStdMap())
    {
        item.second->syncData();
    }
}
