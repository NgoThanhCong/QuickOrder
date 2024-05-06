#include "timemanager.h"

TimeManager* TimeManager::m_instance = nullptr;

TimeManager::TimeManager(QObject *parent)
    : QObject{parent}
{
    updateDateTime();
    m_beat = new QTimer(this);
    connect(m_beat,&QTimer::timeout,this, &TimeManager::updateDateTime);
    m_beat->start(1000);
}

QString TimeManager::currentDateTime() const
{
    return m_currentDateTime;
}

QString TimeManager::currentTimeDb()
{
    return QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss");
}

void TimeManager::setCurrentDateTime(const QString &newCurrentDateTime)
{
    if (m_currentDateTime == newCurrentDateTime)
        return;
    m_currentDateTime = newCurrentDateTime;
    emit currentDateTimeChanged();
}

bool TimeManager::isGreaterThanCurrentDate(QString date)
{
    QDate currentDate = QDate::currentDate();
    QDate inputDate = QDate::fromString(date, "dd/MM/yyyy");

    return inputDate >= currentDate;
}

void TimeManager::updateDateTime()
{
    setCurrentDateTime(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
}
