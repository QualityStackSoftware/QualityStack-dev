#include "oncerunchecker.h"
#include <qt_windows.h>
#include <QString>
#include <QLibrary>
#include <QStringList>
#include <QDebug>
#include <iostream>
#include <tlhelp32.h>
#include <psapi.h>

const int KDSYSINFO_PROCESS_QUERY_LIMITED_INFORMATION = 0x1000;

typedef BOOL (WINAPI *QueryFullProcessImageNamePtr)(HANDLE, DWORD, char *, PDWORD);
typedef DWORD (WINAPI *GetProcessImageFileNamePtr)(HANDLE, char *, DWORD);

QList<ProcessInfo> runningProcesses()
{
    QList<ProcessInfo> processes;
    return processes;
}

std::ostream& operator<<(std::ostream& out, const ProcessInfo& info)
{
    out << info.id;
    out << ", ";
    out << info.name.toStdString();
    return out;
}

QList<ProcessInfo> getprocess()
{
    QList<ProcessInfo> process;

    ProcessInfo proc1;
    proc1.id = 14;
    proc1.name = "process one";
    process.append(proc1);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (!snapshot)
    {
        return process;
    }

    QStringList deviceList;
    const DWORD bufferSize = 1024;
    char buffer[bufferSize + 1] = { 0 };
    if (QSysInfo::windowsVersion() <= QSysInfo::WV_5_2)
    {
        const DWORD size = GetLogicalDriveStringsA(bufferSize, buffer);
        deviceList = QString::fromLatin1(buffer, size).split(QLatin1Char(char(0)), QString::SkipEmptyParts);
    }

    QLibrary kernel32(QLatin1String("Kernel32.dll"));
    kernel32.load();
    QueryFullProcessImageNamePtr pQueryFullProcessImageNamePtr = (QueryFullProcessImageNamePtr) kernel32
        .resolve("QueryFullProcessImageNameA");

    QLibrary psapi(QLatin1String("Psapi.dll"));
    psapi.load();
    GetProcessImageFileNamePtr pGetProcessImageFileNamePtr = (GetProcessImageFileNamePtr) psapi
        .resolve("GetProcessImageFileNameA");

    PROCESSENTRY32 processStruct;
    processStruct.dwSize = sizeof(PROCESSENTRY32);
    bool foundProcess = Process32First(snapshot, &processStruct);
    while (foundProcess)
    {
        HANDLE procHandle = OpenProcess(QSysInfo::windowsVersion() > QSysInfo::WV_5_2
            ? KDSYSINFO_PROCESS_QUERY_LIMITED_INFORMATION : PROCESS_QUERY_INFORMATION, false, processStruct
                .th32ProcessID);

        bool succ = false;
        QString executablePath;
        DWORD bufferSize = 1024;

        if (QSysInfo::windowsVersion() > QSysInfo::WV_5_2)
        {
            succ = pQueryFullProcessImageNamePtr(procHandle, 0, buffer, &bufferSize);
            executablePath = QString::fromLatin1(buffer);
        }
        else if (pGetProcessImageFileNamePtr)
        {
            succ = pGetProcessImageFileNamePtr(procHandle, buffer, bufferSize);
            executablePath = QString::fromLatin1(buffer);
            for (int i = 0; i < deviceList.count(); ++i)
            {
                executablePath.replace(QString::fromLatin1( "\\Device\\HarddiskVolume%1\\" ).arg(i + 1),
                    deviceList.at(i));
            }
        }

        if (succ)
        {
            const quint32 pid = processStruct.th32ProcessID;
            // param.seenIDs.append(pid);
            ProcessInfo info;
            info.id = pid;
            QStringList execs = executablePath.split("\\");
            int size = execs.size();
            std::cout << size << std::endl;
            qDebug() << execs;
            info.name = execs[size-1];
            process.append(info);
        }

        CloseHandle(procHandle);
        foundProcess = Process32Next(snapshot, &processStruct);

    }

    if (snapshot)
    {
        CloseHandle(snapshot);
    }

    kernel32.unload();
    return process;
}

RunOnceChecker::RunOnceChecker()
{
}

RunOnceChecker::~RunOnceChecker()
{
}

bool RunOnceChecker::isRunning()
{
    bool result = true;
    QList<ProcessInfo> process = getprocess();
     Q_FOREACH (const ProcessInfo &info, process)
     {
        std::cout << info << std::endl;
     }

    return result;
}
