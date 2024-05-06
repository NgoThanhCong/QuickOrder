#include "icontroller.h"


IController::IController(QObject *parent) : QObject(parent)
{

}

IController::IController(const QString &tag, QObject *parent) : QObject(parent)
{
    setTag(tag);
}

IController::~IController()
{
    //Deallocate Model.
    if(m_model != nullptr)
    {
        delete m_model;
        m_model = nullptr;
    }
}

void IController::setModel(IModel *model)
{
    this->m_model = model;
}

void IController::registerType(QQmlContext *context)
{
    if(context == nullptr) return;
    context->setContextProperty(m_name,this);
    context->setContextProperty(QString("%1%2").arg(m_tag, SUFFIX_MODEL),m_model);
}

const QString &IController::tag() const
{
    return m_tag;
}

void IController::setTag(const QString &newTag)
{
    if (m_tag == newTag)
        return;
    m_tag = newTag;
    m_name = QString("%1%2").arg(m_tag, SUFFIX_CONTROLLER);

    emit nameChanged();
    emit tagChanged();
}

const QString &IController::name() const
{
    return m_name;
}

QObject *IController::model() const
{
    return m_model;
}

QString IController::storeImage(const QString &sourcePath)
{
    QString newFileName = Misc::Utilities::copyFile(sourcePath,getStoreImagePath());
    return newFileName;
}
