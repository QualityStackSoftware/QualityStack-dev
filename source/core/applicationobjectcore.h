#ifndef APPLICATIONOBJECTCORE_H
#define APPLICATIONOBJECTCORE_H

#include "objectcore.h"
#include <global>

class ApplicationObjectCore : public ObjectCore
{
public:
    // TODO replace QObject by explicit Application ? NON
    ApplicationObjectCore(QObject* parent = 0);
    ~ApplicationObjectCore();

    void init(ObjectCore* objectCore);

private:
    virtual void do_receivingMessage(ObjectCore* from,
                                     ObjectCore* to,
                                     QJsonObject message);

    virtual void do_receiveMe(QJsonObject message);

private:

};

#endif // APPLICATIONOBJECTCORE_H
