#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include "TransformEngine/TransformEngine.h"
#include "AboutDialog/AboutDialog.h"

//Transform providers
#include "TransformProviders/TransformProvider_Case.h"
#include "TransformProviders/TransformProvider_RemoveChars.h"
#include "TransformProviders/TransformProvider_Numbering.h"
#include "TransformProviders/TransformProvider_InsertOverwrite.h"
#include "TransformProviders/TransformProvider_SearchReplace.h"
#include "TransformProviders/TransformProvider_DateTime.h"

MainWindow::MainWindow(QWidget *parent, QApplication* app)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // This doesn't work on Wayland - see call to QGuiApplication::setDesktopFileName() in main.cpp.
    setWindowIcon(QIcon::fromTheme(QStringLiteral("edit-rename")));

    connect(ui->closePushButton, &QPushButton::clicked, app, &QCoreApplication::quit, Qt::QueuedConnection);

    ui->fileNamesTableView->setModel(&fileNameTableModel);

    //auto tableNameHeader=ui->fileNamesTableView->horizontalHeader();
    //connect(tableNameHeader, &QHeaderView::sectionClicked, this, &MainWindow::on_TableNameHeaderClicked);

    //TODO: delete providers
    addProvider(new TransformProvider_Case(this));
    addProvider(new TransformProvider_RemoveChars(this));
    addProvider(new TransformProvider_Numbering(this));
    addProvider(new TransformProvider_InsertOverwrite(this));
    addProvider(new TransformProvider_SearchReplace(this));
    addProvider(new TransformProvider_DateTime(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addProvider(TransformProvider* provider)
{
    TransformEngine::addProvider(provider);
    ui->TransformPagesStackedWidget->addWidget(provider);
    ui->operationComboBox->addItem(provider->displayName);
}

void MainWindow::on_operationComboBox_currentIndexChanged(int index)
{
    TransformEngine::selectProvider(index);
    ui->TransformPagesStackedWidget->setCurrentIndex(index);
    doTransforms();
}

void MainWindow::updateFileNamesTable()
{
    QStringList sourceFileNames=TransformEngine::getSourceFileNamesList();
    QStringList targetFileNames=TransformEngine::getTargetFileNamesList();

    fileNameTableModel.setFileNames(sourceFileNames, targetFileNames);

    //ui->fileNamesTableView->clearContents();
    //ui->fileNamesTableView->setRowCount(sourcefiles.count());

    /*
    int row=0;
    foreach (QString string, sourcefiles)
    {
        //ui->fileNamesTableView->setItem(row,0,new QTableWidgetItem(string));
        row++;
    }
    row=0;
    foreach (QString string, targetfiles)
    {
        //ui->fileNamesTableView->setItem(row,1,new QTableWidgetItem(string));
        row++;
    }
    */
}

void MainWindow::doTransforms()
{
    TransformEngine::doTransform();
    updateFileNamesTable();
}

void MainWindow::on_AddPushButton_clicked()
{
    // auto fileNames = QFileDialog::getOpenFileNames(this, QFileDialog::tr("Select files to add"),"~","All Files (*.*)");
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setNameFilter(tr("Any file (*.*)"));
    fileDialog.setDirectory("/home/lee/Code/Bionic-Batch-Renamer/Temp - Test/");

    //fileDialog.setOption(QFileDialog::DontUseNativeDialog, true); // Makes no difference

    if (!fileDialog.exec()) return;

    auto fileNames=fileDialog.selectedFiles();
    if (fileNames.size() == 0 ) return;

    TransformEngine::addSourceUrls(fileNames);
    doTransforms();
}

void MainWindow::on_RemovePushButton_clicked()
{
    auto indexList = ui->fileNamesTableView->selectionModel()->selectedRows();
    int row;
    //As we're deleting, need to iterate backwards or indices will be wrong
    for (auto index = indexList.crbegin(); index != indexList.crend(); index++)
    {
        row = (*index).row();
        TransformEngine::removeSourceUrl(row);
    }
    doTransforms();
}

void MainWindow::on_clearPushButton_clicked()
{
    TransformEngine::clearSourceUrls();
    //ui->fileNamesTableView->clearContents();
}

void MainWindow::on_renamePushButton_clicked()
{
    TransformEngine::renameFiles();
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
    TransformEngine::selectScope((transformScope)index);
    doTransforms();
}

void MainWindow::on_TableNameHeaderClicked(int index)
{
    if (index==0)   //Name column header
    {
        auto val=ui->fileNamesTableView->horizontalHeader()->sortIndicatorOrder();
        if (val==Qt::SortOrder::AscendingOrder)
        {
            TransformEngine::sortSourceUrls(false);
        }
        else
        {
            TransformEngine::sortSourceUrls(true);
        }
        //Quick but slightly dirty way of reordering target filename list and updating table...
        doTransforms();
    }
}

