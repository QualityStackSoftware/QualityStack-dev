#include "singleapplication.h"

#include <QDebug>
#include <cstdio>

SingleApplication::SingleApplication(QObject* parent)
    : QObject(parent)
    , m_alreadyExist(false)
    , m_timer(new QTimer(this))
    , m_sharedMemory()
    , m_file("debug/in.txt")
    , cpt(0)
{

    if (!m_file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "failed to open file " << m_file.fileName();
    }

    qDebug() << "file:" << m_file.fileName();
    qDebug() << "file is opened:" << m_file.isOpen();

}

SingleApplication::~SingleApplication()
{
    qDebug() << "Deleting single application system";
    delete m_timer;
    qDebug() << "Deleting single application system done";

}



bool SingleApplication::init(const QString& key)
{
    qDebug() << "Creating shared memory with key=" << key;
    m_sharedMemory.setKey(key);

    // we can create it only if it doesn't exist
    if (m_sharedMemory.create(5000))
    {
        bool isLock = m_sharedMemory.lock();
        qDebug() << "Shared memoty is locked" << isLock;
        qDebug() << "Shared memory is created and locked";
        *(char*)m_sharedMemory.data() = '\0';
        isLock = m_sharedMemory.unlock();
        qDebug() << "Shared memory is assigned to zero and unlocked";
        m_alreadyExist = false;

        connect(m_timer, SIGNAL(timeout()), this, SLOT(checkForMessage()));
    }
    // it exits, so we can attach it ?!
    else if (m_sharedMemory.attach())
    {
        qDebug() << "shared memory already exist for this application";
        m_alreadyExist = true;
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
    return m_alreadyExist;
}

bool SingleApplication::isMasterApp() const
{
    return !alreadyExists();
}

void SingleApplication::checkForMessage()
{
    qDebug() << "Check for message ... / file is opened: " << m_file.isOpen();


    if (m_file.isOpen())
    {
        QTextStream out(&m_file);
        out << "The magic number is: " << cpt++ << "\n";
        qDebug() << "Writing into file";
    }

    QStringList arguments;
    bool isLocked = m_sharedMemory.lock();
    qDebug() << "file is temporary locked" << isLocked;
    char *from = (char*)m_sharedMemory.data();

    qDebug() << m_sharedMemory.data();

    qDebug() << from;

    if(*from != '\0')
    {
        qDebug() << "there is something to read";
    }
    else
    {
        qDebug() << "there is nothing to read";
    }



    while(*from != '\0')
    {
        int sizeToRead = int(*from);
        ++from;
        QByteArray byteArray = QByteArray(from, sizeToRead);
        byteArray[sizeToRead] = '\0';
        from += sizeToRead;
        arguments << QString::fromUtf8(byteArray.constData());
    }

    *(char*)m_sharedMemory.data() = '\0';

    m_sharedMemory.unlock();
    if (arguments.size() != 0)
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

    m_sharedMemory.lock();
    char *to = (char*)m_sharedMemory.data();
    while (*to != '\0')
    {
        int sizeToRead = int(*to);
        to += sizeToRead + 1;
    }

    const char *from = byteArray.data();
    memcpy(to, from, qMin(m_sharedMemory.size(), byteArray.size()));
    m_sharedMemory.unlock();
    return true;
}
