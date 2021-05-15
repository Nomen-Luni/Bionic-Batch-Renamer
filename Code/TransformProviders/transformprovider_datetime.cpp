#include "transformprovider_datetime.h"
#include "ui_transformprovider_datetime.h"
#include "MainWindow/mainwindow.h" //For signal connection
#include <QDateTime>
#include <QFileInfo>
#include "KF5/KExiv2/kexiv2/kexiv2.h"

TransformProvider_dateTime::TransformProvider_dateTime(QWidget *parent)
    : TransformProvider(parent) //QWidget constructor called via TransformProvider constructor
    , ui(new Ui::TransformProvider_dateTime)
{
    ui->setupUi(this);
    displayName="Date Time";

    //Connect change events of all contained control to Main Window's 'transformChanged' slot to trigger an update
    connect(ui->atPositionSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->dateSelectComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->formatLineEdit,&QLineEdit::textEdited,(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->fromComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::transformChanged);

    if (KExiv2Iface::KExiv2::initializeExiv2()==false) displayName="Problem";
}

TransformProvider_dateTime::~TransformProvider_dateTime()
{
    KExiv2Iface::KExiv2::cleanupExiv2();
    delete ui;
}

void TransformProvider_dateTime::UpdateGUIvars()
{
    atPosition=ui->atPositionSpinBox->value();
    dateSelect=(dateSelections)ui->dateSelectComboBox->currentIndex();
    format=ui->formatLineEdit->text();
    from=(fromLocations)ui->fromComboBox->currentIndex();
}

QString TransformProvider_dateTime::transform(const QString& inFullUrl, const QString& in, int index, bool& success)
{
    QString transformed;
    (void)index;
    QDateTime date;
    int atIndex;
    KExiv2Iface::KExiv2 exiv2fileInfo(inFullUrl);

    //QDateTime::currentDateTime()
    //static QFileInfo InfoAboutCurrentFile (files.at (i));

    QFileInfo fileInfo(inFullUrl);

    switch (dateSelect)
    {
        case current:
            date=QDateTime::currentDateTime();
            break;
        case date_created:
            date=fileInfo.fileTime(QFileDevice::FileBirthTime);
            break;
        case date_accessed:
            date=fileInfo.fileTime(QFileDevice::FileAccessTime);
            break;
        case date_modified:
            date=fileInfo.fileTime(QFileDevice::FileModificationTime);
            break;
        case date_picture_taken:
            date=exiv2fileInfo.getImageDateTime();
            break;
    }

    switch (from)
    {
        case from_front:
            atIndex=atPosition;
            break;
        case from_back:
            atIndex=in.length()-atPosition;
            break;
    }

    QStringView formatStringView(format);
    QString dateString=date.toString(formatStringView);

    transformed=in;
    transformed.insert(atIndex,dateString);

    success=true;
    return transformed;
}
