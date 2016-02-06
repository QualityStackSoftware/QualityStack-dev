#include "windowmanager.h"



WindowManager::WindowManager(QObject *parent)
    : QObject(parent)
    , m_browsers()
{
    qDebug() << "Creating WindowManager";
    qDebug() << "Creating WindowManager done";

}

WindowManager::~WindowManager()
{
    qDebug() << "Deleting WindowManager";
    qDebug() << "Deleting WindowManager done";

}


void WindowManager::incomingMessage(MessageType type, QString option)
{
    switch (type)
    {
    case BrowserCount: {
        qDebug() << "emiting browserCount";

        break;
    }
    case CreateBrowser:
    {
        qDebug() << "Creating new browser with option=" << option;
        break;
    }
    case DeleteBrowser:
    {
        qDebug() << "Deleting browser with option=" << option;
        break;
    }
    default:
        qDebug() << "Internal error: Unmanaged request for windowManager";
        break;

    }
}

