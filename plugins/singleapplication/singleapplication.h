#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QSharedMemory>
#include <QStringList>
#include <QTimer>
#include <QFile>


class SingleApplication : public QObject
{
    Q_OBJECT
public:
    SingleApplication(QObject* parent=0);

    ~SingleApplication();

    bool init(const QString& key);
    bool startListening();
    bool stoplistening();

    bool alreadyExists() const;
    bool isMasterApp() const;
    bool sendMessage(const QString &message);

public slots:
    void checkForMessage();

signals:
    void messageAvailable(const QStringList& messages);

private:
    QFile file;
    int cpt;

    bool bAlreadyExists;
    QTimer* m_timer;
    QSharedMemory sharedMemory;
};
#endif // SINGLEAPPLICATION_H
