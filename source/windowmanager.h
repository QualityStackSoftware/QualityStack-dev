#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <global>

#include "browserwindow.h"




class WindowManager : public QObject
{
    Q_OBJECT

public:

    enum MessageType {
        BrowserCount = 0,
        CreateBrowser = 1,
        DeleteBrowser = 2
    };

    explicit WindowManager(QObject *parent = 0);
    ~WindowManager();



signals:


public slots:
    void incomingMessage(MessageType type, QString option);

private:
    QMap<QString, BrowserWindow* > m_browsers;

    // add model here

};

#endif // WINDOWMANAGER_H
