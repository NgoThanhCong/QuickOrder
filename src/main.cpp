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
    //Qsettings
    app.setOrganizationName("QuickOrder");
    app.setOrganizationDomain("QuickOrderCor");

    app.setApplicationName("QuickOrder");
    qDebug() << QCoreApplication::applicationDirPath();  // dc
    app.setWindowIcon(QIcon(":/icons/ic_app.svg"));
    Misc::Utilities::getInstance().loadFont(app);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    engine.rootContext()->setContextProperty("TimeManager", TimeManager::getIntance());

    ControllerManager cm;
    cm.init();
    cm.registerController(engine.rootContext());


    // QML error, exit
    if (engine.rootObjects().isEmpty())
    {
        qDebug() << "QML engine error";
        return EXIT_FAILURE;
    }
    app.exec();
    return 0;
}
