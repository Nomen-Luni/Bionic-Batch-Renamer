#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include "TransformProviders/TransformProvider.h"
#include "FileNameTableModel/FileNameTableModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QApplication* app = nullptr);
    ~MainWindow();
    //static void transformChangedCallbackUsingInstancePtr(void * instance, int arg);

private:
    void addProvider(TransformProvider* provider);
    void updateFileNamesTable();
    FileNameTableModel fileNameTableModel;
    Ui::MainWindow *ui;

public slots:
    void doTransforms();

private slots:
    void on_operationComboBox_currentIndexChanged(int index);
    void on_AddPushButton_clicked();
    void on_RemovePushButton_clicked();
    void on_clearPushButton_clicked();
    void on_renamePushButton_clicked();
    void on_aboutButton_clicked();
    void on_targetComboBox_currentIndexChanged(int index);
    void on_TableNameHeaderClicked(int column);
};
#endif // MAINWINDOW_H
