#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#include <QIcon>

#include <Misc/Utilities.h>
#include "Misc/Utilities.h"
#include "Components/controllermanager.h"
#include "Components/timemanager.h"

int main(int argc, char **argv)
{

    // Init. application
    QApplication app(argc, argv);
    app.setOrganizationName("QuickOrder");
    app.setOrganizationDomain("QuickOrderCor");
    app.setApplicationName("QuickOrder");
    qDebug() << QCoreApplication::applicationDirPath();
    app.setWindowIcon(QIcon(":/icons/ic_app.svg"));
    Misc::Utilities::getInstance().loadFont(app);
    QQmlApplicationEngine engine;

    ControllerManager cm;

    // Init QML interface
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    engine.rootContext()->setContextProperty("Utils", &Misc::Utilities::getInstance());
    engine.rootContext()->setContextProperty("TimeManager", TimeManager::getIntance());

    cm.init();
    cm.registerController(engine.rootContext());


    // QML error, exit
    if (engine.rootObjects().isEmpty())
    {
        qDebug() << "QML engine error";
        return EXIT_FAILURE;
    }

    // Enter application event loop
    auto code = app.exec();
    qDebug() << "Application exit code" << code;
    return code;
}
