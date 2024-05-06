#include "settingsmodel.h"

SettingsModel::SettingsModel(QObject *parent)
    : IModel{parent}
{}

SettingsModel::SettingsModel(const QString &name) : IModel(name)
{

}

QString SettingsModel::storeName() const
{
    return m_storeName;
}

void SettingsModel::setStoreName(const QString &newStoreName)
{
    if (m_storeName == newStoreName)
        return;
    m_storeName = newStoreName;
    emit storeNameChanged();
}

QString SettingsModel::hotline() const
{
    return m_hotline;
}

void SettingsModel::setHotline(const QString &newHotline)
{
    if (m_hotline == newHotline)
        return;
    m_hotline = newHotline;
    emit hotlineChanged();
}

QString SettingsModel::bankName() const
{
    return m_bankName;
}

void SettingsModel::setBankName(const QString &newBankName)
{
    if (m_bankName == newBankName)
        return;
    m_bankName = newBankName;
    emit bankNameChanged();
}

QString SettingsModel::bankId() const
{
    return m_bankId;
}

void SettingsModel::setBankId(const QString &newBankId)
{
    if (m_bankId == newBankId)
        return;
    m_bankId = newBankId;
    emit bankIdChanged();
}

QString SettingsModel::fanpage() const
{
    return m_fanpage;
}

void SettingsModel::setFanpage(const QString &newFanpage)
{
    if (m_fanpage == newFanpage)
        return;
    m_fanpage = newFanpage;
    emit fanpageChanged();
}

QString SettingsModel::address() const
{
    return m_address;
}

void SettingsModel::setAddress(const QString &newAddress)
{
    if (m_address == newAddress)
        return;
    m_address = newAddress;
    emit addressChanged();
}
