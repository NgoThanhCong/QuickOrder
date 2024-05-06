#include "navigationbarcontroller.h"

NavigationBarController::NavigationBarController(QObject *parent) : IController(parent)
{

}

NavigationBarController::NavigationBarController(const QString &tag, QObject *parent) : IController(tag, parent), m_inspectionState(true)
{

}

bool NavigationBarController::inspectionState() const
{
    return m_inspectionState;
}

void NavigationBarController::setInspectionState(bool newInspectionState)
{
    m_inspectionState = newInspectionState;
    emit inspectionStateChanged();
}

void NavigationBarController::syncData()
{
    qDebug() << "NavigationBarController " << __FUNCTION__;
}

void NavigationBarController::changeInspectionStartStatus()
{
    setInspectionState(!m_inspectionState);
    emit inspectionStartStatus_Changed(m_inspectionState);
}
