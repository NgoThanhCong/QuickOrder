#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include "imodel.h"

class SettingsModel : public IModel
{
    Q_OBJECT
public:
    explicit SettingsModel(QObject *parent = nullptr);
    SettingsModel(const QString& name);

    QString storeName() const;
    void setStoreName(const QString &newStoreName);

    QString hotline() const;
    void setHotline(const QString &newHotline);

    QString bankName() const;
    void setBankName(const QString &newBankName);

    QString bankId() const;
    void setBankId(const QString &newBankId);

    QString fanpage() const;
    void setFanpage(const QString &newFanpage);

    QString address() const;
    void setAddress(const QString &newAddress);

signals:
    void storeNameChanged();
    void hotlineChanged();
    void bankNameChanged();

    void bankIdChanged();

    void fanpageChanged();

    void addressChanged();

private:
    QString m_storeName;
    QString m_hotline;
    QString m_bankName;
    QString m_bankId;
    QString m_fanpage;
    QString m_address;

    Q_PROPERTY(QString storeName READ storeName WRITE setStoreName NOTIFY storeNameChanged FINAL)
    Q_PROPERTY(QString hotline READ hotline WRITE setHotline NOTIFY hotlineChanged FINAL)
    Q_PROPERTY(QString bankName READ bankName WRITE setBankName NOTIFY bankNameChanged FINAL)
    Q_PROPERTY(QString bankId READ bankId WRITE setBankId NOTIFY bankIdChanged FINAL)
    Q_PROPERTY(QString fanpage READ fanpage WRITE setFanpage NOTIFY fanpageChanged FINAL)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged FINAL)
};

#endif // SETTINGSMODEL_H
