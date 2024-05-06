#ifndef NAVIITEM_H
#define NAVIITEM_H

#include <QObject>

class NaviItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString src READ src WRITE setSrc NOTIFY srcChanged)
    Q_PROPERTY(bool isEnable READ isEnable WRITE setIsEnable NOTIFY isEnableChanged)
public:
    explicit NaviItem(QObject *parent = nullptr);
    NaviItem(const QString& name, const QString& src,bool isEnable = true);

    const QString &name() const;
    void setName(const QString &newName);

    const QString &src() const;
    void setSrc(const QString &newSrc);

    bool isEnable() const;
    void setIsEnable(bool newIsEnable);

signals:

    void nameChanged();

    void srcChanged();

    void isEnableChanged();

private:
    QString m_name;
    QString m_src;
    bool m_isEnable;
};

#endif // NAVIITEM_H
