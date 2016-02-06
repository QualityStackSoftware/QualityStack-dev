#ifndef APPLICATION_H
#define APPLICATION_H

#include <global>

#include "windowmanager.h"

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int &argc, char** argv);
    ~Application();
    void configure();

public slots:
    void incomingMessage(QStringList msg);

private:
    WindowManager* m_windowManager;
};

#endif // APPLICATION_H
