#include "objectcoremanager.h"

#include "applicationobjectcore.h"


ObjectCoreManager::ObjectCoreManager(QObject *parent)
    : QObject(parent)
    , m_objectCores()
{
}

ObjectCoreManager::~ObjectCoreManager()
{

}


ObjectCoreManager::init()
{
    m_objectCores.insert(ObjectType::Application,
                         new ApplicationObjectCore);



}


ObjectCore* ObjectCoreManager::get(ObjectType type) const
{
    QMap<QString, ObjectCore*>::const_iterator i = m_objectCores.find(type);
    Q_ASSUME(i != m_objectCores.end());
    return i.value();
}
