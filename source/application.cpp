#include "application.h"

Application::Application(int argc, char *argv[])
    : QApplication(argc, argv)
    , m_applicationPath()
    , m_objectCoreManager()
    , m_windowManager()
    , m_applicationCore()
{    
}

Application::~Application()
{
    qDebug() << "Deleting application";
    qDebug() << "Deleting application done";
}

void Application::setApplicationPath(const QString& applicationPath)
{
    m_applicationPath =  applicationPath;
}

const QString& Application::getApplicationPath() const
{
    return m_applicationPath;
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

