#ifndef OBJECTCOREMANAGER_H
#define OBJECTCOREMANAGER_H

#include <global>
#include "objecttype.h"
#include "objectcore.h"

class ObjectCoreManager : public ObjectCore
{
//    Q_OBJECT
public:
    explicit ObjectCoreManager(QObject *parent = 0);
    ~ObjectCoreManager();

    ObjectCore* retreiveObjectCore(ObjectType::ObjectType type) const;

    void insert(ObjectType::ObjectType type, ObjectCore* objectToRegister);

private:
    virtual void do_receivingMessage(ObjectCore* from,
                                     ObjectCore* to,
                                     QJsonObject message);

    virtual void do_receiveMe(QJsonObject message);

//signals:

//public slots:

private:
    QMap<ObjectType::ObjectType, ObjectCore*> m_objectCores;
};

#endif // OBJECTCOREMANAGER_H
