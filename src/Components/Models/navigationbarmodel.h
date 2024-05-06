#ifndef NAVIGATIONBARMODEL_H
#define NAVIGATIONBARMODEL_H
#include <QList>
#include <QDebug>
#include "imodel.h"
#include "data/naviitem.h"

class NavigationBarModel : public IModel
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject *> items READ items NOTIFY itemsChanged)
public:
    NavigationBarModel();
    NavigationBarModel(const QString& name);
    const QList<QObject *> &items() const;
    void setItems(const QList<QObject *> &newItems);

    void init(bool isAdmin);
signals:
    void itemsChanged();

private:
    QList<QObject*> m_items;
};

#endif // NAVIGATIONBARMODEL_H
