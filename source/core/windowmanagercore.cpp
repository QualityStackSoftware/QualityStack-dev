#include "windowmanagercore.h"

WindowManagerCore::WindowManagerCore()
    : ObjectCore(ObjectType::WindowManager)
{
}


WindowManagerCore::~WindowManagerCore()
{

}

/*virtual*/ void WindowManagerCore::do_receivingMessage(ObjectCore* from,
                                                        ObjectCore* to,
                                                        QJsonObject message)
{
    Q_UNUSED(from)
    Q_UNUSED(to)
    Q_UNUSED(message)
}

/*virtual*/ void WindowManagerCore::do_receiveMe(QJsonObject message)
{
    Q_UNUSED(message)
}
