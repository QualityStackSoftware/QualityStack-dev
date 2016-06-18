#include "commandline.h"

/*static*/ CommandLine::Status CommandLine::analyse(QCommandLineParser& parser, QString& errorMessage)
{
    /*
     * We setup expected options for our application
     * 1. Register all expeced options
     * We analyse arguments of application.
     * 2. Read option and campare them with expected ones.
     * 3. If there is an error, we notice an error.
     * 4. If there no error, them, we check if we need to quit application now.
     * 5. Here, we do not quit application and we have valid options. So, we return ok.
     */

    qDebug() << "Analyzing command line";


    // 1.
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    parser.setApplicationDescription("QualityStack description");
    QCommandLineOption versionOption = parser.addVersionOption();
    QCommandLineOption helpOption = parser.addHelpOption();
    QCommandLineOption pathApplicationOption(QStringList() << "p" << "path", "path used in  all application");
    parser.addOption(pathApplicationOption);

    QCommandLineOption nameOption(QStringList() << "n" << "name" << "application name");
    parser.addOption(nameOption);

    QCommandLineOption displayNameOption(QStringList() << "d" << "displayName" << "application display name");
    parser.addOption(displayNameOption);

    QStringList arguments = QCoreApplication::arguments();
    qDebug() << "arguments:" << arguments;

    // 2.
    bool isParsedOk = parser.parse(arguments);
    isParsedOk &= (parser.unknownOptionNames().size() == 0);

    // 3.
    if (!isParsedOk)
    {
        errorMessage = parser.errorText();
        return Error;
    }

    // 4.
    bool hasVersion = parser.isSet(versionOption);
    if (hasVersion)
    {
        return VersionRequested;
    }

    bool hasHelp = parser.isSet(helpOption);
    if (hasHelp)
    {
        return HelpRequested;
    }

    // 5.
    return Ok;
}
