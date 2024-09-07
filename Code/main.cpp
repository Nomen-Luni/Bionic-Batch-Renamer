#include "MainWindow/MainWindow.h"
#include <QApplication>
#include <QLocale>
#include <QMessageBox>
#include <QTranslator>
#include "TransformEngine/TransformEngine.h"
#include "Styling/SingleClickWorkaroundProxyStyle.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // TODO: Does line below need associated cleanup (from new)
    app.setStyle(new SingleClickWorkaroundProxyStyle()); // Workaround to stop file selector closing after single file click on Plasma 6.

    QTranslator translator;
    QLocale locale=QLocale::system();
    QString translationFileName=":/Translations/Batch_Renamer_"+locale.name()+".qm";
    if (translator.load(translationFileName))
    {
        app.installTranslator(&translator);
    }

    // Currently this is the way to set window icon on Wayland
    QGuiApplication::setDesktopFileName("Bionic_Batch_Renamer");

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
    MainWindow mainWindow(nullptr, &app);
    mainWindow.show();
    return app.exec();
}
