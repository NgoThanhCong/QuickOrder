#ifndef ENTITYDATEVALUE_H
#define ENTITYDATEVALUE_H

#include <QObject>
#include <QDateTime>

class EntityDateValue : public QObject
{
    Q_OBJECT
public:
    explicit EntityDateValue(QObject *parent = nullptr);

    QString date() const;
    void setDate(const QDateTime &newDate);

    float value() const;
    void setValue(float newValue);

signals:

    void dateChanged();
    void valueChanged();

private:
    QDateTime m_date;
    float m_value;
    Q_PROPERTY(QString date READ date NOTIFY dateChanged FINAL)
    Q_PROPERTY(float value READ value NOTIFY valueChanged FINAL)
};

#endif // ENTITYDATEVALUE_H
