#include "transformprovider_numbering.h"
#include "ui_transformprovider_numbering.h"
#include "mainwindow.h" //For signal connection

TransformProvider_numbering::TransformProvider_numbering(QWidget *parent)
    : TransformProvider(parent) //QWidget constructor called via TransformProvider constructor
    , ui(new Ui::TransformProvider_numbering)
{
    ui->setupUi(this);
    displayName="Numbering";

    //Connect change events of all contained control to Main Window's 'transformChanged' slot to trigger an update
    connect(ui->startNumberSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->spacerComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->padCharacterComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->padWidthSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->locationComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::transformChanged);
}

TransformProvider_numbering::~TransformProvider_numbering()
{
    delete ui;
}

void TransformProvider_numbering::UpdateGUIvars()
{
    spacerType=(spacerTypes)ui->spacerComboBox->currentIndex();
    padCharacterType=(padCharacterTypes)ui->padCharacterComboBox->currentIndex();
    padWidth=ui->padWidthSpinBox->value();
    startNumber=ui->startNumberSpinBox->value();
    location=(locationTypes)ui->locationComboBox->currentIndex();
}

QString TransformProvider_numbering::transform(const QString& inFullUrl, const QString& in, int index, bool& success)
{
    QString transformed;
    QString numberString;
    QString spaceChar;
    int number=startNumber+index;
    (void)inFullUrl;

    numberString=QString::number(number);
    switch (padCharacterType)
    {
        case nopad:
            break;
        case zeros:
            numberString=numberString.rightJustified(padWidth,'0');
            break;
        case spaces:
            numberString=numberString.rightJustified(padWidth,' ');
            break;
    }

    switch (spacerType)
    {
        case none:
            spaceChar="";
        break;
        case space:
            spaceChar=" ";
        break;
        case period:
            spaceChar=".";
        break;
        case hyphen:
            spaceChar="-";
        break;
        case underscore:
            spaceChar="_";
        break;
    }

    switch (location)
    {
        case at_start:
            transformed=numberString+spaceChar+in;
            break;
        case at_end:
            transformed=in+spaceChar+numberString;
            break;
    }

    success=true;
    return transformed;
}


