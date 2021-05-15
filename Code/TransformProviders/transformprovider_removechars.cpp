#include "transformprovider_removechars.h"
#include "ui_transformprovider_removechars.h"
#include "MainWindow/mainwindow.h" //For signal connection

TransformProvider_removeChars::TransformProvider_removeChars(QWidget *parent)
    : TransformProvider(parent) //QWidget constructor called via TransformProvider constructor
    , ui(new Ui::TransformProvider_removeChars)
{
    ui->setupUi(this);
    displayName="Remove Characters";

    //Connect change events of all contained control to Main Window's 'transformChanged' slot to trigger an update
    connect(ui->fromCharsSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->toCharsSpinBox,QOverload<int>::of(&QSpinBox::valueChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->fromComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->toComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::transformChanged);

    //Create palettes for GUI value error highlighting
    //paletteSpinboxDefault=ui->fromCharsSpinBox->palette();
    //paletteSpinboxError=paletteSpinboxDefault;
    //paletteSpinboxError.setColor(QPalette::Base, Qt::red);
}

TransformProvider_removeChars::~TransformProvider_removeChars()
{
    delete ui;
}

void TransformProvider_removeChars::UpdateGUIvars()
{
    //Read GUI variables
    fromChars=ui->fromCharsSpinBox->value();
    toChars=ui->toCharsSpinBox->value();
    from=(fromToLocations)ui->fromComboBox->currentIndex();
    to=(fromToLocations)ui->toComboBox->currentIndex();

    /*
    bool rangeError=false;
    if ((from==fromto_front)&&(to==fromto_front)&&(fromChars>=toChars)) rangeError=true;
    if ((from==fromto_back)&&(to==fromto_back)&&(fromChars<=toChars)) rangeError=true;

    if (rangeError)
    {
       ui->fromCharsSpinBox->setPalette(paletteSpinboxError);
    }
    else
    {
        ui->fromCharsSpinBox->setPalette(paletteSpinboxDefault);
    }
    */
}

QString TransformProvider_removeChars::transform(const QString& inFullUrl, const QString& in, int index, bool& success)
{
    QString transformed=in;
    int fromIndex=0;
    int toIndex=0;
    (void)inFullUrl;
    (void)index;

    switch (from)
    {
        case fromto_front:
            fromIndex=fromChars;
            break;
        case fromto_back:
            fromIndex=in.length()-fromChars;
            break;
    }

    switch (to)
    {
        case fromto_front:
            toIndex=toChars;
            break;
        case fromto_back:
            toIndex=in.length()-toChars;
            break;
    }

    transformed.remove(fromIndex, toIndex);

    success=true;
    return transformed;
}
