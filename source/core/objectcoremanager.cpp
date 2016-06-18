#include "objectcoremanager.h"

#include "applicationobjectcore.h"


ObjectCoreManager::ObjectCoreManager(QObject *parent)
    : ObjectCore(ObjectType::ObjectCoreManager, parent)
    , m_objectCores()
{
}

ObjectCoreManager::~ObjectCoreManager()
{

}


void ObjectCoreManager::insert(ObjectType::ObjectType type, ObjectCore* objectToRegister)
{
    qDebug() << "Inserting type" << type << objectToRegister->getType();
    m_objectCores.insert(type,  objectToRegister);
}


ObjectCore* ObjectCoreManager::retreiveObjectCore(ObjectType::ObjectType type) const
{
    QMap<ObjectType::ObjectType, ObjectCore*>::const_iterator i = m_objectCores.find(type);
    Q_ASSUME(i != m_objectCores.end());
    return i.value();
}



void ObjectCoreManager::do_receivingMessage(ObjectCore* from,
                                 ObjectCore* to,
                                 QJsonObject message)
{
    Q_UNUSED(from)
    Q_UNUSED(to)
    Q_UNUSED(message)
}

void ObjectCoreManager::do_receiveMe(QJsonObject message)
{
    Q_UNUSED(message)
}
