#ifndef ENTITYCATEGORY_H
#define ENTITYCATEGORY_H

#include <QObject>
#include <QDebug>

class EntityCategory : public QObject
{
    Q_OBJECT
public:
    explicit EntityCategory(QObject *parent = nullptr);

    int categoryId() const;
    void setCategoryId(int newCategoryId);

    const QString &name() const;
    void setName(const QString &newName);

    void printDebug();

signals:
    void categoryIdChanged();

    void nameChanged();

private:
    int m_categoryId;
    QString m_name;
    Q_PROPERTY(int categoryId READ categoryId WRITE setCategoryId NOTIFY categoryIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
};

#endif // ENTITYCATEGORY_H
