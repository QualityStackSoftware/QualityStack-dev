#ifndef APPLICATION_H
#define APPLICATION_H

#include <global>

#include "core/messagetype.h"
#include "core/objectcore.h"
#include "core/objectcoremanager.h"

class WindowManager;
class ObjectCoreManager;

class Application : public QApplication
{
    Q_OBJECT
public:
    explicit Application(int argc, char *argv[]);
    ~Application();

    void init(ObjectCoreManager* manager);

public slots:
    void do_slots() {}

private:

    ObjectCoreManager* m_objectCoreManager;

    WindowManager* m_windowManager;
};

#endif // APPLICATION_H
