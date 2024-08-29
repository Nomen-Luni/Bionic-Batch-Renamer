#include "TransformProvider_InsertOverwrite.h"
#include "ui_TransformProvider_InsertOverwrite.h"
#include "MainWindow/MainWindow.h" //For signal connection

TransformProvider_InsertOverwrite::TransformProvider_InsertOverwrite(QWidget *parent)
    : TransformProvider(parent) //QWidget constructor called via TransformProvider constructor
    , ui(new Ui::TransformProvider_InsertOverwrite)
{
    ui->setupUi(this);
    displayName=QObject::tr("Insert / Overwrite");

    //Connect change events of all contained control to Main Window's 'transformChanged' slot to trigger an update
    connect(ui->fromComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::doTransforms);
    connect(ui->modeComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::doTransforms);
    connect(ui->positionSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),(MainWindow*)parent, &MainWindow::doTransforms);
    connect(ui->textLineEdit,&QLineEdit::textEdited,(MainWindow*)parent, &MainWindow::doTransforms);
}

TransformProvider_InsertOverwrite::~TransformProvider_InsertOverwrite()
{
    delete ui;
}

void TransformProvider_InsertOverwrite::updateGUIvars()
{
    from=(fromLocations)ui->fromComboBox->currentIndex();
    mode=(modes)ui->modeComboBox->currentIndex();
    position=ui->positionSpinBox->value();
    text=ui->textLineEdit->text();
}

QString TransformProvider_InsertOverwrite::transform(const QString& inFullUrl, const QString& in, int index, bool& success)
{
    QString transformed=in;
    int atIndex;
    (void)inFullUrl;
    (void)index;


    switch (from)
    {
        case from_front:
            atIndex=position;
            break;
        case from_back:
            atIndex=in.length()-position;
            break;
    }

    switch(mode)
    {
        case insert:
            transformed.insert(atIndex,text);
            break;
        case overwrite:
            transformed.replace(atIndex,text.length(), text);
            break;
    }
    success=true;
    return transformed;
}


