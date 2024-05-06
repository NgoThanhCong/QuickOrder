#ifndef TITLEBARCONTROLLER_H
#define TITLEBARCONTROLLER_H
#include "icontroller.h"

class TitleBarController : public IController
{
    Q_OBJECT
public:
    TitleBarController(QObject* parent = nullptr);
    TitleBarController(const QString &tag, QObject* parent = nullptr);

    void syncData();

public slots:
    void handle_On_TitleBar_Changed(QString title);

};

#endif // TITLEBARCONTROLLER_H
