#ifndef IMODEL_H
#define IMODEL_H

#include <QObject>
#include <QVariantList>
#include <QVariant>
#include <QDebug>
#include "Misc/Utilities.h"

class IModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit IModel(QObject *parent = nullptr);
    explicit IModel(const QString& name, QObject* parent = nullptr);
    virtual ~IModel(){};

    const QString &name() const;
    void setName(const QString &newName);

signals:
    void nameChanged();

private:
    QString m_name;
};

#endif // IMODEL_H
