#ifndef ENTITYSTATISTICELEMENT_H
#define ENTITYSTATISTICELEMENT_H

#include <QObject>

class EntityStatisticElement : public QObject
{
    Q_OBJECT
public:
    explicit EntityStatisticElement(QObject *parent = nullptr);

    QString label() const;
    void setLabel(const QString &newLabel);

    float value() const;
    void setValue(float newValue);

signals:
    void labelChanged();

    void valueChanged();

private:
    float m_value;
    QString m_label;
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged FINAL)
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged FINAL)
};

#endif // ENTITYSTATISTICELEMENT_H
