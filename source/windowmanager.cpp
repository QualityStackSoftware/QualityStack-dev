#include "windowmanager.h"


WindowManager::WindowManager(QObject* parent)
    : QObject(parent)
    , m_core(0)
{
}

WindowManager::~WindowManager()
{
    qDebug() << "Deleting WindowManager";
    // nothing to do with m_core
    // TODO delete all window
    qDebug() << "Deleting WindowManager done";
}

void WindowManager::init(const ObjectCoreManager& manager)
{
    qDebug() << "Initializing window manager";
    m_core =  manager.retreiveObjectCore(ObjectType::WindowManager);



}



//void WindowManager::incomingMessage(MessageType type, QStringList option)
//{
//    switch (type)
//    {
//    case BrowserCount: {
//        qDebug() << "emiting browserCount";
//        createWindow(options);
//        break;
//    }
//    case CreateBrowser:
//    {
//        qDebug() << "Creating new browser with option="
//                 << option;

//        break;
//    }
//    case DeleteBrowser:
//    {
//        qDebug() << "Deleting browser with option="
//                 << option;
//        break;
//    }
//    default:
//        qDebug() << "Internal error: Unmanaged request for windowManager";
//        break;

//    }
//}

QWidget* WindowManager::createWindow(const QString& id, const QStringList& msg, Qt::WindowStates state)
{
    Q_UNUSED(state)

    BrowserWindow* browser = new BrowserWindow;
    connect(browser, SIGNAL(destroyed(QObject*)), this, SLOT(windowDestroyed(QObject*)));
    connect(browser, SIGNAL(startingCompleted()), this, SLOT(restoreOverrideCursor()));

    m_browsers.insert(id, browser);
    qDebug() << "Create browser. # of browser is now" << m_browsers.size();


    browser->init(id, msg);

//    if (actWin != 0) {
//        browser->setWindowState(state & ~Qt::WindowMinimized);
//        browser->raise();
//        browser->activateWindow();
//        browser->setFocus();
//    }

    return browser;

}


