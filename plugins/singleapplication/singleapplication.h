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
    QFile m_file;
    int cpt;

    bool m_alreadyExist;
    QTimer* m_timer;
    QSharedMemory m_sharedMemory;
};
#endif // SINGLEAPPLICATION_H
