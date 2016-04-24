#include "browserwindow.h"

#include <global>


BrowserWindow::BrowserWindow(QWidget *parent) : QMainWindow(parent)
{
    qDebug() << "Creating Browser window";
}

BrowserWindow::~BrowserWindow()
{
    qDebug() << "Deleting browser window";
}


void BrowserWindow::init(const QStringList& msg)
{
    qDebug() << "Init browser";

    // do stuff here

    qDebug() << "Init browser done";
}
