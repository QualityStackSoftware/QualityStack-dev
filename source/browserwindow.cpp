#include "browserwindow.h"

#include <global>


BrowserWindow::BrowserWindow()
    : QMainWindow()
{
    qDebug() << "Creating Browser window";
}

BrowserWindow::~BrowserWindow()
{
    qDebug() << "Deleting browser window";
}


void BrowserWindow::init(const QString& id, const QStringList& msg)
{
    qDebug() << "Init browser" << id;

    m_id = id;
    m_msg = msg;


    // do stuff here

    qDebug() << "Init browser done";
}
