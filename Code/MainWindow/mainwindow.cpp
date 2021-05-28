#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "TransformEngine/transformengine.h"
#include "AboutDialog/aboutdialog.h"

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

    auto tableNameHeader=ui->fileNamesTableWidget->horizontalHeader();
    connect(tableNameHeader, &QHeaderView::sectionClicked, this, &MainWindow::on_TableNameHeaderClicked);

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
    ui->operationComboBox->addItem(provider->displayName);
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
    ui->fileNamesTableWidget->setRowCount(sourcefiles->count());

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
    auto fileNames = QFileDialog::getOpenFileNames(this, QFileDialog::tr("Select files to add"),"~","All Files (*.*)");
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

void MainWindow::on_TableNameHeaderClicked(int index)
{
    if (index==0)   //Name column header
    {
        auto val=ui->fileNamesTableWidget->horizontalHeader()->sortIndicatorOrder();
        if (val==Qt::SortOrder::AscendingOrder)
        {
            TransformEngine::SortSourceUrls(false);
        }
        else
        {
            TransformEngine::SortSourceUrls(true);
        }
        //Quick but slightly dirty way of reordering target filename list and updating table...
        transformChanged();
    }
}

