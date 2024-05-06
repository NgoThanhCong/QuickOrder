#ifndef IWRAPPERSERVICE_H
#define IWRAPPERSERVICE_H

#include <QObject>

class IWrapperService : public QObject
{
    Q_OBJECT
public:
    explicit IWrapperService(QObject *parent = nullptr);
    virtual ~IWrapperService(){}
    virtual void init() = 0;
signals:

};

#endif // IWRAPPERSERVICE_H
