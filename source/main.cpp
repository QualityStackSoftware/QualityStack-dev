#include "commandline.h"
#include "application.h"
#include <global>
#include <plugins/singleapplication>


int main(int argc, char *argv[])
{
    Application app(argc, argv);
    app.setApplicationName("QualityDock");
    app.setApplicationVersion("v1.0.0");

    /*
     * Manage application unicity: we want to launch only one application (with possible several windows).
     *
     */
    SingleApplication single;
    if (!single.init("QualityDock"))
    {
        return 1;
    }

    /*
     * Manage commandLine in order to display help or version if necesserary.
     */
    QCommandLineParser parser;
    QString errorMessage = "";
    CommandLine::Status status = CommandLine::analyse(app, parser, errorMessage);
    switch (status)
    {
        case CommandLine::Ok:
            /*
             * Arguments of application is ok.
             * So, we will continue to run this application.
             */
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
        case CommandLine::HelpRequested:
            /*
             * Display help text for this application.
             * Then, we quit application without any error.
             */
            fprintf(stdout, "%s", qPrintable(parser.helpText()));
    }

    //


    /*
     * Here, command line is ok. We have to launch application if application is not already running.
     * If not, we send to existing application the command line in order to
     * treat the request of current user.
     */
    if (single.alreadyExists())
    {
        for (int i=0; i < argc; ++i)
        {
            single.send(QString(argv[i]));
        }
        return 0;
    }

    QObject::connect(&single
              ,SIGNAL(messageAvailable(QStringList))
              ,&app
              ,SLOT(incomingMessage(QStringList)));


    // At this point, we have to initialise application

    // afficher la page de
    // - lancer authentification


    app.configure();


    QMainWindow w;
    w.show();
    return app.exec();
}
