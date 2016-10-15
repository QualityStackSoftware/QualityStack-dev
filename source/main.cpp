#include "commandline.h"
#include "application.h"
#include "core/objectcoremanager.h"
#include "core/windowmanagercore.h"
#include "core/applicationobjectcore.h"

#include <plugins/singleapplication>

#include <global>


int main(int argc, char *argv[])
{
    Application app(argc, argv);

    /*
     * Parse command line in order to display help or version if needed.
     */
    QCommandLineParser parser;
    QString errorMessage = "";
    CommandLine::Status status = CommandLine::analyse(parser, errorMessage);
    switch (status)
    {
        case CommandLine::Ok:
            /*
             * Arguments of application is ok.
             * So, we will continue to run this application.
             */
            qDebug() << "Command line ok";
            break;
        case CommandLine::Error:
            /*
             * There is an error with argument of this application.
             * So, we quit application after displaying error message.
             */
            fputs(qPrintable(errorMessage), stderr);
            fputs("\n\n", stderr);
            fputs(qPrintable(parser.helpText()), stderr);
            return 1;
        case CommandLine::VersionRequested:
            /*
             * Display version of this application
             * Then, we quit application without any error.
             */
            printf("%s %s\n", qPrintable(QCoreApplication::applicationName())
                   , qPrintable(QCoreApplication::applicationVersion()));
            return 0;
        case CommandLine::HelpRequested:
            /*
             * Display help text for this application.
             * Then, we quit application without any error.
             */
            fprintf(stdout, "%s", qPrintable(parser.helpText()));
            return 0;
    }

    app.setApplicationPath(parser.value("path"));
    app.setApplicationName(parser.value("name"));
    app.setApplicationDisplayName(parser.value("displayName"));
    app.setApplicationVersion("v1.0.0");

    /*
     * Manage application unicity: we want to launch only one application
     * (with possible several windows).
     */
    SingleApplication single;
    if (!single.init(app.applicationName()))
    {
        qDebug() << "failed to init unicity system for application";
        return 1;
    }

    /*
     * Here, command line is ok. We have to launch application if application is not already running.
     * If not, we send to existing application the command line in order to
     * treat the request of current user.
     */
    if (single.alreadyExists())
    {
        qDebug() << "Application is already running. So, sending arguments and quit";

        QStringList args;
        for (int i = 0; i < argc; ++i)
        {
            args.push_back(QString(argv[i]));
        }
        single.sendMessage(args.join(';'));
        return 0;
    }

    // At this point, there is no other application running.
    // So, we have to to initialise application for the first time.
    //    qDebug() << QSysInfo::windowsVersion();
    //    qDebug() << QProcessEnvironment::systemEnvironment().toStringList();

    // system for window management (creation / removing / update / show/hide )

    // git system for save change

    // shared model for each abstract item managed in this application ( requirement, test, ... )

    // synchorisation system

    // system + GUI specific for specific activity




    ObjectCoreManager objectCoreManager;
    objectCoreManager.insert(ObjectType::WindowManager, new WindowManagerCore);
    objectCoreManager.insert(ObjectType::Application, new ApplicationObjectCore);



    app.init(objectCoreManager);


    single.startListening();
    QObject::connect(&single, SIGNAL(messageAvailable(QStringList)),
                     &app, SLOT(incomingMessage(QStringList)));



    QJsonObject activity;
    activity.insert("Action", "NewWindow");
    app.sendMe(activity);

    return app.exec();
}
