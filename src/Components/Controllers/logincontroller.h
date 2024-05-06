#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H
#include "icontroller.h"
#include <QCryptographicHash>
#include "Misc/Utilities.h"
#include "../Database/qousertable.h"

class LoginController : public IController
{
    Q_OBJECT
public:
    explicit LoginController(QObject *parent = nullptr);
    LoginController(const QString &tag, QObject* parent = nullptr);

public slots:
    void handle_On_TitleBar_Changed(QString title);
    void login(const QString& id, const QString& pw);
    void logout();
    void recoverPassword();
    void syncData();

private:
    bool comparePw(QString input, QString hash);
    QOUserTable* m_userTable;
};

#endif // LOGINCONTROLLER_H
