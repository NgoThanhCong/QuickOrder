#ifndef ENTITYVOUCHER_H
#define ENTITYVOUCHER_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include "../../timemanager.h"

class EntityVoucher : public QObject
{
    Q_OBJECT
public:
    explicit EntityVoucher(QObject *parent = nullptr);


    QString validDate() const;
    void setValidDate(QString date);

    int discountValue() const;
    void setDiscountValue(int newDiscountValue);

    int status() const;
    void setStatus(int newStatus);

    void printDebug();

    int voucherId() const;
    void setVoucherId(int newVoucherId);

    const QString &voucherCode() const;
    void setVoucherCode(const QString &newVoucherCode);

    Q_INVOKABLE QString getStatusText();

signals:
    void validDateChanged();

    void discountValueChanged();

    void statusChanged();

    void voucherIdChanged();

    void voucherCodeChanged();

private:
    int m_voucherId;
    QString m_voucherCode;
    QString m_validDate;
    int m_discountValue;
    int m_status;


    Q_PROPERTY(QString validDate READ validDate WRITE setValidDate NOTIFY validDateChanged)
    Q_PROPERTY(int discountValue READ discountValue WRITE setDiscountValue NOTIFY discountValueChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(int voucherId READ voucherId WRITE setVoucherId NOTIFY voucherIdChanged)
    Q_PROPERTY(QString voucherCode READ voucherCode WRITE setVoucherCode NOTIFY voucherCodeChanged)
};

#endif // ENTITYVOUCHER_H
