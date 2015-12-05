#ifndef ONCERUNCHECKER_H
#define ONCERUNCHECKER_H

#include <qobject.h>
#include <QString>
#include <QList>
#include <iostream>


struct ProcessInfo
{
    quint32 id;
    QString name;
};


QList<ProcessInfo> getprocess();

std::ostream& operator<<(std::ostream& out, const ProcessInfo& info);

class RunOnceChecker
{
    Q_DISABLE_COPY(RunOnceChecker)

public:
    explicit RunOnceChecker();
    virtual ~RunOnceChecker();
    bool isRunning();
};

#endif // ONCERUNCHECKER_H
