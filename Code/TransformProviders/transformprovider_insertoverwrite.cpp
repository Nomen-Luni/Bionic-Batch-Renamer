#include "transformprovider_insertoverwrite.h"
#include "ui_transformprovider_insertoverwrite.h"
#include "MainWindow/mainwindow.h" //For signal connection

TransformProvider_insertOverwrite::TransformProvider_insertOverwrite(QWidget *parent)
    : TransformProvider(parent) //QWidget constructor called via TransformProvider constructor
    , ui(new Ui::TransformProvider_insertOverwrite)
{
    ui->setupUi(this);
    displayName=QObject::tr("Insert / Overwrite");

    //Connect change events of all contained control to Main Window's 'transformChanged' slot to trigger an update
    connect(ui->fromComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->modeComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->positionSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->textLineEdit,&QLineEdit::textEdited,(MainWindow*)parent, &MainWindow::transformChanged);
}

TransformProvider_insertOverwrite::~TransformProvider_insertOverwrite()
{
    delete ui;
}

void TransformProvider_insertOverwrite::UpdateGUIvars()
{
    from=(fromLocations)ui->fromComboBox->currentIndex();
    mode=(modes)ui->modeComboBox->currentIndex();
    position=ui->positionSpinBox->value();
    text=ui->textLineEdit->text();
}

QString TransformProvider_insertOverwrite::transform(const QString& inFullUrl, const QString& in, int index, bool& success)
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


