#include "MainWindow/mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QMessageBox>
#include <QTranslator>
#include "TransformEngine/transformengine.h"

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

    QStringList FileNames=app.arguments();
    FileNames.removeFirst();

    bool filesOkay=TransformEngine::AddSourceUrls(FileNames);
    if (filesOkay==false)
    {
        QMessageBox msg;
        msg.setText(QMessageBox::tr("Problem with selected files.\nCheck you have write permission for all files."));
        msg.exec();
        return 1;
    }
    MainWindow window (nullptr, &app);
    window.show();
    return app.exec();
}
