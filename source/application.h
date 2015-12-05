#ifndef APPLICATION_H
#define APPLICATION_H

#include <global>

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

};

#endif // APPLICATION_H
