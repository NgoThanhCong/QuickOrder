#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QDebug>

class TimeManager : public QObject
{
    Q_OBJECT
    explicit TimeManager(QObject *parent = nullptr);
    static TimeManager* m_instance;


public:
    static TimeManager* getIntance(){
        if(m_instance == nullptr){
            m_instance = new TimeManager();
        }
        return m_instance;
    }

    QString currentDateTime() const;
    QString currentTimeDb();
    void setCurrentDateTime(const QString &newCurrentDateTime);
    bool isGreaterThanCurrentDate(QString date);

private slots:
    void updateDateTime();

signals:
    void currentDateTimeChanged();

private:
    QString m_currentDateTime;
    QTimer* m_beat;

    Q_PROPERTY(QString currentDateTime READ currentDateTime WRITE setCurrentDateTime NOTIFY currentDateTimeChanged FINAL)
};

#endif // TIMEMANAGER_H
