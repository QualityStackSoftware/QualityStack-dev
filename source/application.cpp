#include "application.h"
#include "core/applicationobjectcore.h"

Application::Application(int argc, char *argv[])
    : QApplication(argc, argv)
    , m_objectCoreManager(new ObjectCoreManager)
    , m_windowManager(new WindowManager)
{
}

Application::~Application()
{
    qDebug() << "Deleting application";
    delete m_objectCoreManager;
    delete m_windowManager;
    qDebug() << "Deleting application done";
}

void Application::init(ObjectCoreManager* manager)
{
    qDebug() << "Configuring application";
    Q_ASSUME(manager != 0);

    m_windowManager->init(manager->get(ObjectType::WindowManager));

    qDebug() << "Configuring application done";
}

///*virtual*/ void Application::do_receivingMessage(ObjectCore* from,
//                                 ObjectCore* to,
//                                 QJsonObject message)
//{
//    Q_ASSUME(from != 0);
//    Q_ASSUME(to != 0);
//    qDebug() << "receiving message" << from << to << message;
//}


///*virtual*/ void do_receiveMe(QJsonObject message)
//{
//    qDebug() << "Receiving from me" << message;
//}
