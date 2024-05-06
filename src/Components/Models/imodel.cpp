#include "imodel.h"

IModel::IModel(QObject *parent) : QObject(parent) , m_name("")
{

}

IModel::IModel(const QString &name, QObject *parent) : QObject(parent), m_name(name)
{

}

const QString &IModel::name() const
{
    return m_name;
}

void IModel::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}
