#include "objectcore.h"

ObjectCore::ObjectCore(QObject* parent, ObjectType::ObjectType type)
    : QObject(parent)
    , m_type(type)
{
    connect(this, SIGNAL(receiveMessage(ObjectCore*,ObjectCore*,QJsonObject)),
            this, SLOT(receivingMessage(ObjectCore*,ObjectCore*,QJsonObject)));

    connect(this, SIGNAL(sendMe(QJsonObject)), this, SLOT(receiveMe(QJsonObject));
}


ObjectCore::~ObjectCore()
{
    // nothing to do
}

ObjectType::ObjectType ObjectCore::getType() const
{
    return m_type;
}


void ObjectCore::registerListener(ObjectCore* object)
{
    Q_ASSUME(object != 0);
    connect(this,
            SIGNAL(sendMessage(ObjectCore*,
                               ObjectCore*,
                               QJsonObject)),
            object,
            SIGNAL(receiveMessage(ObjectCore*,
                                  ObjectCore*,
                                  QJsonObject)));
}


void ObjectCore::unRegisterListener(ObjectCore* object)
{
    Q_ASSUME(object != 0);
    disconnect(this, SIGNAL(sendMessage(ObjectCore*,
                                     ObjectCore*,
                                     QJsonObject)),
               object,
               SIGNAL(receiveMessage(ObjectCore*,
                                     ObjectCore*,
                                     QJsonObject)));
}


void ObjectCore::emit_sendMessage(ObjectCore* from, ObjectCore* to, QJsonObject message)
{
    emit sendMessage(from, to, message);
}


void ObjectCore::emit_sendMe(QJsonObject message)
{
    emit sendMe(message);
}


void ObjectCore::receivingMessage(ObjectCore* from, ObjectCore* to, QJsonObject message) {

    Q_ASSUME(from != 0);
    Q_ASSUME(to != 0);

    // stupid
    if (*to != *m_type){
        return;
    }
    return do_receivingMessage(from, to, message);
}


void ObjectCore::receiveMe(QJsonObject message)
{
    return do_receiveMe(message);
}


//

bool operator!=(const ObjectCore& lhs, const ObjectCore& rhs)
{
    return !(lhs == rhs);
}


bool operator==(const ObjectCore& lhs, const ObjectCore& rhs)
{
     return (lhs.getType() == rhs.getType());
}
