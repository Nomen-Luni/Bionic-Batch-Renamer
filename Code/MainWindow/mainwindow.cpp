#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "transformengine.h"
#include "aboutdialog.h"

//Transform providers
#include "TransformProviders/transformprovider_case.h"
#include "TransformProviders/transformprovider_removechars.h"
#include "TransformProviders/transformprovider_numbering.h"
#include "TransformProviders/transformprovider_insertoverwrite.h"
#include "TransformProviders/transformprovider_searchreplace.h"
#include "TransformProviders/transformprovider_datetime.h"

MainWindow::MainWindow(QWidget *parent, QApplication* app)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon::fromTheme(QStringLiteral("system-file-manager")));

    connect(ui->closePushButton, &QPushButton::clicked, app, &QCoreApplication::quit, Qt::QueuedConnection);

    AddProvider(new TransformProvider_case(this));
    AddProvider(new TransformProvider_removeChars(this));
    AddProvider(new TransformProvider_numbering(this));
    AddProvider(new TransformProvider_insertOverwrite(this));
    AddProvider(new TransformProvider_searchReplace(this));
    AddProvider(new TransformProvider_dateTime(this));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddProvider(TransformProvider* provider)
{
    TransformEngine::AddProvider(provider);
    ui->TransformPagesStackedWidget->addWidget(provider);
    ui->operationComboBox->addItem(QString::fromStdString(provider->displayName));
}

void MainWindow::on_operationComboBox_currentIndexChanged(int index)
{
    TransformEngine::SelectProvider(index);
    ui->TransformPagesStackedWidget->setCurrentIndex(index);
    transformChanged();
}

void MainWindow::updateFileNamesTable()
{
    QStringList* sourcefiles=TransformEngine::GetSourceFileNamesListPtr();
    QStringList* targetfiles=TransformEngine::GetTargetFileNamesListPtr();

    ui->fileNamesTableWidget->clearContents();

    int row=0;
    foreach (QString string, *sourcefiles)
    {
        ui->fileNamesTableWidget->setItem(row,0,new QTableWidgetItem(string));
        row++;
    }
    row=0;
    foreach (QString string, *targetfiles)
    {
        ui->fileNamesTableWidget->setItem(row,1,new QTableWidgetItem(string));
        row++;
    }
}

void MainWindow::transformChanged()
{
    TransformEngine::DoTransform();
    updateFileNamesTable();
}

void MainWindow::on_AddPushButton_clicked()
{
    auto fileNames = QFileDialog::getOpenFileNames(this, "Select files to add","/path/to/file/","All Files (*.*)");
    TransformEngine::AddSourceUrls(fileNames);
    transformChanged();
}

void MainWindow::on_RemovePushButton_clicked()
{
    auto indexList = ui->fileNamesTableWidget->selectionModel()->selectedRows();
    int row;
    //As we're deleting, need to iterate backwards or indices will be wrong
    for (auto index = indexList.crbegin(); index != indexList.crend(); index++)
    {
        row = (*index).row();
        TransformEngine::RemoveSourceUrl(row);
    }
    transformChanged();
}

void MainWindow::on_clearPushButton_clicked()
{
    TransformEngine::ClearSourceUrls();
    ui->fileNamesTableWidget->clearContents();
}

void MainWindow::on_renamePushButton_clicked()
{
    TransformEngine::RenameFiles();
    updateFileNamesTable();
}

void MainWindow::on_aboutButton_clicked()
{
    AboutDialog aboutDialog(this);
    aboutDialog.exec();
}

void MainWindow::on_targetComboBox_currentIndexChanged(int index)
{
    (void)index;
    TransformEngine::SelectScope((transformScope)index);
    transformChanged();
}
