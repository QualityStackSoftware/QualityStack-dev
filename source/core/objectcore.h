#ifndef OBJECTCORE
#define OBJECTCORE

#include <global>
#include "objecttype.h"


class ObjectCore : public QObject
{
    Q_OBJECT
public:

    ObjectCore(QObject* parent, ObjectType::ObjectType type);
    ~ObjectCore();

    ObjectType::ObjectType getType() const;

    /*!
     * Allows to register other ObjectCore listening this
     * When this will emit something, then other ObjectCore will
     * be notified
     */
    void registerListener(ObjectCore* object);
    void unRegisterListener(ObjectCore* object);

    /**
     * @brief emit_sendMessage allows to send signal from "from" OBjectCore to "to" ObjectCore with message "message"
     * @param from emitter
     * @param to
     * @param message
     */
    void emit_sendMessage(ObjectCore* from,
                          ObjectCore* to,
                          QJsonObject message);

    void emit_sendMe(QJsonObject message);

signals:
    void sendMe(QJsonObject message);
    void sendMessage(ObjectCore* from,
                     ObjectCore* to,
                     QJsonObject message);

    void receiveMessage(ObjectCore* from,
                        ObjectCore* to,
                        QJsonObject message);
public slots:
    void receivingMessage(ObjectCore* from,
                          ObjectCore* to,
                          QJsonObject message);

    void receiveMe(QJsonObject message);

private:
    virtual void do_receivingMessage(ObjectCore* from,
                                     ObjectCore* to,
                                     QJsonObject message) = 0;

    virtual void do_receiveMe(QJsonObject message) = 0;


private:
    ObjectType::ObjectType m_type;
};


bool operator!=(const ObjectCore& lhs, const ObjectCore& rhs);
bool operator==(const ObjectCore& lhs, const ObjectCore& rhs);


#endif // OBJECTCORE

