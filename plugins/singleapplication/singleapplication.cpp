#include "singleapplication.h"

#include <QDebug>
#include <cstdio>

SingleApplication::SingleApplication(QObject* parent)
    : QObject(parent)
    , bAlreadyExists(false)
    , m_timer(new QTimer(this))
    , sharedMemory()
    , file("debug/in.txt")
    , cpt(0)
{

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "failed to open file " << file.fileName();
    }

    qDebug() << "file is opened:" << file.isOpen();

}

SingleApplication::~SingleApplication()
{
    qDebug() << "Deleting single application system";
    delete m_timer;
    qDebug() << "Deleting single application system done";

}



bool SingleApplication::init(const QString& key)
{
    sharedMemory.setKey(key);

    // we can create it only if it doesn't exist
    if (sharedMemory.create(5000))
    {
        bool isLock = sharedMemory.lock();
        qDebug() << "Shared memory is created and locked";
        *(char*)sharedMemory.data() = '\0';
        isLock = sharedMemory.unlock();
        qDebug() << "Shared memory is assigned to zero ans unlocked";
        bAlreadyExists = false;

        connect(m_timer, SIGNAL(timeout()), this, SLOT(checkForMessage()));

    }
    // it exits, so we can attach it ?!
    else if (sharedMemory.attach())
    {
        qDebug() << "shared memory alredy exist for this application";
        bAlreadyExists = true;
    }
    else
    {
        qDebug() << "Internal error during creation of sharedmemory";
        return false;
    }
    return true;
}


bool SingleApplication::startListening()
{
    // start checking for messages of other instances.
    m_timer->start(1000);
    return true;
}


bool SingleApplication::stoplistening()
{
    m_timer->stop();
    return true;
}



bool SingleApplication::alreadyExists() const
{
    return bAlreadyExists;
}

bool SingleApplication::isMasterApp() const
{
    return !alreadyExists();
}

void SingleApplication::checkForMessage()
{
    qDebug() << "Check for message ... / file is opened: " << file.isOpen();


    if (file.isOpen())
    {
        QTextStream out(&file);
        out << "The magic number is: " << cpt++ << "\n";
        qDebug() << "Writing into file";
    }

    QStringList arguments;
    sharedMemory.lock();
    char *from = (char*)sharedMemory.data();

    while(*from != '\0')
    {
        int sizeToRead = int(*from);
        ++from;
        QByteArray byteArray = QByteArray(from, sizeToRead);
        byteArray[sizeToRead] = '\0';
        from += sizeToRead;
        arguments << QString::fromUtf8(byteArray.constData());
    }

    *(char*)sharedMemory.data() = '\0';
    sharedMemory.unlock();
    if (arguments.size())
    {
        qDebug() << "Message available:" << arguments;
        emit messageAvailable( arguments );
    }
}

bool SingleApplication::sendMessage(const QString &message)
{
    if (isMasterApp())
    {
        // We can not send message if we are the master process!
        return false;
    }

    QByteArray byteArray;
    byteArray.append(char(message.size()));
    byteArray.append(message.toUtf8());
    byteArray.append('\0');

    sharedMemory.lock();
    char *to = (char*)sharedMemory.data();
    while (*to != '\0')
    {
        int sizeToRead = int(*to);
        to += sizeToRead + 1;
    }

    const char *from = byteArray.data();
    memcpy(to, from, qMin(sharedMemory.size(), byteArray.size()));
    sharedMemory.unlock();
    return true;
}
