#ifndef ENTITYINFO_H
#define ENTITYINFO_H

#include <QObject>

class EntityInfo : public QObject
{
    Q_OBJECT
public:
    explicit EntityInfo(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &newName);

    QString info() const;
    void setInfo(const QString &newInfo);

signals:
    void nameChanged();

    void infoChanged();

private:
    QString m_name;
    QString m_info;
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged FINAL)
};

#endif // ENTITYINFO_H
