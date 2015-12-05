﻿#include "singleapplication.h"

#include <QTimer>
#include <QDebug>

SingleApplication::SingleApplication(QObject* parent)
    : QObject(parent)
    , bAlreadyExists(false)
    , sharedMemory()
{}


bool SingleApplication::init(const QString& key)
{
    sharedMemory.setKey(key);

    // we can create it only if it doesn't exist
    if (sharedMemory.create(5000))
    {
        sharedMemory.lock();
        *(char*)sharedMemory.data() = '\0';
        sharedMemory.unlock();
        bAlreadyExists = false;

        // start checking for messages of other instances.
        QTimer* timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(checkForMessage()));
        timer->start(200);
    }
    // it exits, so we can attach it ?!
    else if (sharedMemory.attach())
    {
        bAlreadyExists = true;
    }
    else
    {
        qDebug() << "Internal error";
        return false;
    }
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
        emit messageAvailable( arguments );
    }
}

bool SingleApplication::send(const QString &message)
{
    //we cannot send mess if we are master process!
    if (isMasterApp())
    {
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
