#include "settingscontroller.h"

SettingsController::SettingsController(QObject *parent)
    : IController{parent}
{}

SettingsController::SettingsController(const QString &tag, QObject *parent) : IController(tag,parent)
{

}

void SettingsController::updateStoreName(QString data)
{
    SettingsModel* model = getModel<SettingsModel>();
    if(model->storeName() == data ) return;
    m_settings.setValue(KEY_STORE_NAME, data);
    syncData();
}

void SettingsController::updateHotline(QString data)
{
    SettingsModel* model = getModel<SettingsModel>();
    if(model->hotline() == data ) return;
    m_settings.setValue(KEY_HOTLINE, data);
    syncData();
}

void SettingsController::updateFanpageLink(QString data)
{
    SettingsModel* model = getModel<SettingsModel>();
    if(model->hotline() == data ) return;
    m_settings.setValue(KEY_FANPAGE_LINK, data);
    syncData();
}

void SettingsController::updateBankId(QString data)
{
    SettingsModel* model = getModel<SettingsModel>();
    if(model->bankId() == data ) return;
    QString imgStoredName = storeImage(data);
    m_settings.setValue(KEY_BANK_ID, imgStoredName);
    syncData();
}

void SettingsController::updateAddress(QString data)
{
    SettingsModel* model = getModel<SettingsModel>();
    if(model->bankId() == data ) return;
    m_settings.setValue(KEY_ADDRESS, data);
    syncData();
}

void SettingsController::syncData()
{
    QString storeName = m_settings.value(KEY_STORE_NAME).toString();
    QString hotline = m_settings.value(KEY_HOTLINE).toString();
    QString address = m_settings.value(KEY_ADDRESS).toString();
    QString fanpage = m_settings.value(KEY_FANPAGE_LINK).toString();
    QString bankId = Utils.formatPathImage(m_settings.value(KEY_BANK_ID).toString());
    // bankId = QFile::exists(bankId) ? bankId : "qrc:/images/select_avt.png";

    SettingsModel* model = getModel<SettingsModel>();
    model->setStoreName(storeName);
    model->setHotline(hotline);
    model->setBankId(bankId);
    model->setFanpage(fanpage);
    model->setAddress(address);
}
