#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <global>

class CommandLine
{
public:
    enum Status
    {
        Ok,
        Error,
        VersionRequested,
        HelpRequested
    };

    static Status analyse(QCommandLineParser& parser, QString& errorMessage);

private:
    QCommandLineParser m_parser;
};

#endif // COMMANDLINE_H

