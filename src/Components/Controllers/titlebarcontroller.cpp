#include "titlebarcontroller.h"

TitleBarController::TitleBarController(QObject *parent) : IController(parent)
{

}

TitleBarController::TitleBarController(const QString &tag, QObject *parent) : IController(tag,parent)
{

}

void TitleBarController::syncData()
{
    qDebug() << "TitleBarController " << __FUNCTION__;
}

void TitleBarController::handle_On_TitleBar_Changed(QString title)
{
    getModel<TitleBarModel>()->setAppName(title);
}
