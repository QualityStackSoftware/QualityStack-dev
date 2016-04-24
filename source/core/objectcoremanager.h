#ifndef OBJECTCOREMANAGER_H
#define OBJECTCOREMANAGER_H

#include <global>
#include "objecttype.h"
#include "objectcore.h"

class ObjectCoreManager : public QObject
{
    Q_OBJECT
public:
    explicit ObjectCoreManager(QObject *parent = 0);
    ~ObjectCoreManager();

    ObjectCore* get(ObjectType type) const;



    void init();

signals:

public slots:

private:
    QMap<ObjectType, ObjectCore*> m_objectCores;
};

#endif // OBJECTCOREMANAGER_H
