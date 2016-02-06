#include "browserwindow.h"



BrowserWindow::BrowserWindow(QWidget *parent) : QMainWindow(parent)
{
    qDebug() << "Creating Browser window";
}

BrowserWindow::~BrowserWindow()
{
    qDebug() << "Deleting browser window";
}

