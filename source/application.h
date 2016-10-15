#ifndef APPLICATION_H
#define APPLICATION_H

#include <global>

#include "core/messagetype.h"
#include "core/objectcoremanager.h"

#include "windowmanager.h"


class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int argc, char *argv[]);
    ~Application()
    {
    }

    void setApplicationPath(const QString& path) { m_applicationPath = path; }
    const QString& getApplicationPath() const { return m_applicationPath; }

    void init(const ObjectCoreManager& manager);
    void sendMe(const QJsonObject& json);

public slots:
    void incomingMessage(QStringList msg);
    void do_slots() {}

private:
    ObjectCore* m_applicationCore;

    QString m_applicationPath;
    ObjectCoreManager m_objectCoreManager;
    WindowManager m_windowManager;
};

#endif // APPLICATION_H
