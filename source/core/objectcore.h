#ifndef OBJECTCORE
#define OBJECTCORE

#include <global>

class ObjectCore : public QObject
{
    Q_OBJECT
public:

    enum Type
    {
        ModelManager = 0,
        GitSystem,
        Synchronizer,
        WindowManager,
        Updater,
        AuthenticationManager
    };

    ObjectCore(QObject* parent, Type type)
        : QObject(parent)
        , m_type(type)
    {

    }

    ~ObjectCore()
    {

    }

signals:
    void sendMessage(Type from, Type to, QString message);

    void receiveMessage(Type from, Type to, QString message);
public slots:
    void receivingMessage(Type from, Type to, QString message)
    {
        if (to == m_type)
        {
            return do_receivingMessage(from, to, message);
        }
    }

private:
    virtual void do_receivingMessage(Type from, Type to, QString message)
    {

    }

private:
    Type m_type;
};

#endif // OBJECTCORE

