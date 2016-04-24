#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <global>

#include "core/messagetype.h"
#include "core/objectcoremanager.h"
#include "browserwindow.h"


class WindowManager : public QObject
{
    Q_OBJECT
public:
    explicit WindowManager(QObject* parent);
    virtual ~WindowManager();

    void init(ObjectCoreManager* manager);

private:
    QWidget* createWindow(const QStringList& msg);

private:
    ObjectCore* m_core;
    QMap<QString, BrowserWindow* > m_browsers;

};

#endif // WINDOWMANAGER_H
