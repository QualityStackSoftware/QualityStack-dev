#ifndef WINDOWMANAGERCORE_H
#define WINDOWMANAGERCORE_H

#include "windowmanager.h"

class WindowManagerCore : public ObjectCore
{
public:
    explicit WindowManagerCore();
    ~WindowManagerCore();
private:
    virtual void do_receivingMessage(ObjectCore* from,
                                     ObjectCore* to,
                                     QJsonObject message);

    virtual void do_receiveMe(QJsonObject message);

};

#endif // WINDOWMANAGERCORE_H
