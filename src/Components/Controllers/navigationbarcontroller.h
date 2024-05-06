#ifndef NAVIGATIONBARCONTROLLER_H
#define NAVIGATIONBARCONTROLLER_H
#include "icontroller.h"

class NavigationBarController : public IController
{
    Q_OBJECT
public:
    NavigationBarController(QObject *parent = nullptr);
    NavigationBarController(const QString &tag, QObject* parent = nullptr);
    bool inspectionState() const;
    void setInspectionState(bool newInspectionState);

    void syncData();

public slots:
    void changeInspectionStartStatus();

signals:
    void inspectionStartStatus_Changed(bool value);
    void inspectionStateChanged();

private:
    bool m_inspectionState;

    Q_PROPERTY(bool inspectionState READ inspectionState WRITE setInspectionState NOTIFY inspectionStateChanged)
};

#endif // NAVIGATIONBARCONTROLLER_H
