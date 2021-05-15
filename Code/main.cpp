#include "MainWindow/mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QMessageBox>
#include <QTranslator>
#include "TransformEngine/transformengine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //QApplication::applicationDirPath()+"/"+"Batch_Renamer_en_GB.ts";
    QTranslator translator;
    QLocale locale=QLocale::system();
    if (translator.load(":/"+locale.name()+".qm"))
    {
        app.installTranslator(&translator);
    }

    QStringList FileNames=app.arguments();
    FileNames.removeFirst();

    bool filesOkay=TransformEngine::AddSourceUrls(FileNames);
    if (filesOkay==false)
    {
        QMessageBox msg;
        msg.setText("Problem with selected files.\nCheck you have write permission for all files.");
        msg.exec();
        return 1;
    }
    MainWindow window (nullptr, &app);
    window.show();
    return app.exec();
}
