#include "windowmanager.h"


WindowManager::WindowManager(QObject* parent)
    : QObject(parent)
    , m_core(0)
{
}

WindowManager::~WindowManager()
{
    qDebug() << "Deleting WindowManager";
    qDebug() << "Deleting WindowManager done";

}

void WindowManager::init(const ObjectCoreManager* manager)
{
    qDebug() << "Initializing window manager";

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

QWidget* WindowManager::createWindow(const QStringList& msg)
{
    QWidget* actWin = getCurrentWindow();

    BrowserWindow* window = new BrowserWindow(this);
    connect(window, SIGNAL(destroyed(QObject*)),
            this, SLOT(windowDestroyed(QObject*)));
    connect(window, SIGNAL(startingCompleted()),
            this, SLOT(restoreOverrideCursor()));

    m_browsers.insert(window->Identifier(), window);
    qDebug() << "Create browser. # of browser is now" << m_browsers.size();


    window->init(msg);


    if (actWin != 0) {
        window->setWindowState(actWin->windowState() & ~Qt::WindowMinimized);
        window->raise();
        window->activateWindow();
        window->setFocus();
    }

}


