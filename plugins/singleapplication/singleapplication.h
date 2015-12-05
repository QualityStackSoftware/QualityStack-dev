#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QSharedMemory>
#include <QStringList>

class SingleApplication : public QObject
{
    Q_OBJECT
public:
    SingleApplication(QObject* parent=0);

    bool init(const QString& key);

    bool alreadyExists() const;
    bool isMasterApp() const;
    bool send(const QString &message);

public slots:
    void checkForMessage();

signals:
    void messageAvailable(const QStringList& messages);

private:
    bool bAlreadyExists;
    QSharedMemory sharedMemory;
};
#endif // SINGLEAPPLICATION_H
