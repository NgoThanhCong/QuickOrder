#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include "icontroller.h"
#include <QSettings>

#define KEY_STORE_NAME "Settings/KS_StoreName"
#define KEY_ADDRESS "Settings/KS_Address"
#define KEY_HOTLINE "Settings/KS_Hotline"
#define KEY_FANPAGE_LINK "BankAccount/KS_FANPAGE_LINK"
#define KEY_BANKNAME "BankAccount/KS_BANK_NAME"
#define KEY_BANK_ID "BankAccount/KS_BANK_ID"

class SettingsController : public IController
{
    Q_OBJECT
public:
    explicit SettingsController(QObject *parent = nullptr);
    SettingsController(const QString &tag, QObject* parent = nullptr);

public slots:
    void updateStoreName(QString);
    void updateHotline(QString);
    void updateFanpageLink(QString);
    void updateBankId(QString);
    void updateAddress(QString);
    void syncData();

private:
    QSettings m_settings;
};

#endif // SETTINGSCONTROLLER_H
