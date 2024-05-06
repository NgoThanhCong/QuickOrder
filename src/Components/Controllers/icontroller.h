#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QQmlContext>
#include "../databasemanager.h"
#include "../Models/titlebarmodel.h"
#include "../Models/navigationbarmodel.h"
#include "../Models/loginmodel.h"
#include "../Models/usermodel.h"
#include "../Models/menumodel.h"
#include "../Models/ordermodel.h"
#include "../Models/reportmodel.h"
#include "../Models/settingsmodel.h"
#include "../Models/vouchermodel.h"
#include "../const.h"
#include "../../Misc/Utilities.h"

class ControllerManager;

class IController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString tag READ tag WRITE setTag NOTIFY tagChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)

public:
    explicit IController(QObject *parent = nullptr);
    explicit IController(const QString& tag,QObject *parent = nullptr);
    virtual ~IController();

    void setModel(IModel* model);
    void registerType(QQmlContext* context);

    const QString &tag() const;
    void setTag(const QString &newTag);

    const QString &name() const;    
    QObject *model() const;

    QString storeImage(const QString& sourcePath);

    virtual void syncData() = 0;

    static QString getStoreImagePath(){
        QString imgPath =QCoreApplication::applicationDirPath().append("/").append("images");
        qDebug() << __FUNCTION__ << ": " << imgPath;
        return imgPath;
    }

    ControllerManager* getManager(){
        if(parent() != nullptr){
            return (ControllerManager*)parent();
        }
        return nullptr;
    }

signals:
    void nameChanged();
    void tagChanged();

protected:

    QString m_tag;
    QString m_name;

    template<class T>
    T* getModel(){
        return dynamic_cast<T*>(m_model);
    }

private:
    QObject* m_model;

};

#endif // ICONTROLLER_H
