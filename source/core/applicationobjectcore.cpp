#include "applicationobjectcore.h"
#include "application.h"

ApplicationObjectCore::ApplicationObjectCore(QObject* parent)
    : ObjectCore(ObjectType::Application, parent)
{

}

ApplicationObjectCore::~ApplicationObjectCore()
{

}


void ApplicationObjectCore::init(ObjectCore* objectCore)
{
    Q_ASSUME(objectCore != 0);
    QObject* parent  = objectCore->parent();
    Q_ASSUME(parent != 0);

    Application* app = qobject_cast<Application*>(parent);
    if (!app) {
        qDebug() << "null object for ApplicationObjectName";
        return;
    }

}


/*virtual*/ void ApplicationObjectCore::do_receivingMessage(ObjectCore* from, ObjectCore* to, QJsonObject message)
{
    Q_ASSUME(from != 0);
    Q_ASSUME(to != 0);
    qDebug() << "Receiving message \"" << message << "\" from" << from << "to" << to;

}

/*virtual*/ void ApplicationObjectCore::do_receiveMe(QJsonObject message)
{
    Q_UNUSED(message);
}
