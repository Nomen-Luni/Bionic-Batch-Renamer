#include "MainWindow/MainWindow.h"
#include <QApplication>
#include <QLocale>
#include <QMessageBox>
#include <QTranslator>
#include "TransformEngine/TransformEngine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    QLocale locale=QLocale::system();
    QString translationFileName=":/Translations/Batch_Renamer_"+locale.name()+".qm";
    if (translator.load(translationFileName))
    {
        app.installTranslator(&translator);
    }

    QStringList commandLineUrls=app.arguments();
    commandLineUrls.removeFirst();    //First argument is executable name, discard it

    QString error=TransformEngine::addSourceUrls(commandLineUrls);
    if (error!="")
    {
        QMessageBox msg;
        msg.setText(error);
        msg.exec();
        return 1;
    }
    MainWindow window (nullptr, &app);
    window.show();
    return app.exec();
}
