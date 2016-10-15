#include "application.h"

Application::Application(int argc, char *argv[])
    : QApplication(argc, argv)
    , m_applicationCore()
    , m_applicationPath()
    , m_objectCoreManager()
    , m_windowManager()
{    
}


void Application::init(const ObjectCoreManager& manager)
{
    m_applicationCore = manager.retreiveObjectCore(ObjectType::Application);
    Q_ASSUME(m_applicationCore!=0);

    qDebug() << "Configuring application";
    m_windowManager.init(manager);
    qDebug() << "Configuring application done";
}

void Application::sendMe(const QJsonObject& json)
{
    qDebug() << "executing send me with json=" << json;
}


void Application::incomingMessage(QStringList msg)
{
    qDebug() << "receiving data from single application system:" << msg;
}

