#include "application.h"

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
    , m_windowManager(new WindowManager(this))
{
    qDebug() << "Creating application";
}

Application::~Application()
{
    qDebug() << "Deleting application";
    delete m_windowManager;
    qDebug() << "Deleting application done";
}


void Application::incomingMessage(QStringList msg)
{
    qDebug() << "Incoming message into application:" << msg;


}


void Application::configure()
{

}

