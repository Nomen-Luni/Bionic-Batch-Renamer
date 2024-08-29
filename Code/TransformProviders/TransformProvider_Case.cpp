#include "TransformProvider_Case.h"
#include "ui_TransformProvider_Case.h"
#include "MainWindow/MainWindow.h" //For signal connection

TransformProvider_Case::TransformProvider_Case(QWidget *parent)
    : TransformProvider(parent) //QWidget constructor called via TransformProvider constructor
    , ui(new Ui::TransformProvider_Case)
{
    ui->setupUi(this);
    displayName=QObject::tr("Uppercase / Lowercase");

    //Connect change events of all contained control to Main Window's 'transformChanged' slot to trigger an update
    connect(ui->modeComboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),(MainWindow*)parent, &MainWindow::doTransforms);//MainWindow::doTransforms);
}

TransformProvider_Case::~TransformProvider_Case()
{
    delete ui;
}

void TransformProvider_Case::updateGUIvars()
{
    mode=(modes)(ui->modeComboBox->currentIndex());
}

QString TransformProvider_Case::transform(const QString& inFullUrl, const QString& in, int index, bool& success)
{
    QString transformed;
    (void)inFullUrl;
    (void)index;

    switch (mode)
    {
    case upper_case:
        transformed=in.toUpper();
        break;
    case lower_case:
        transformed=in.toLower();
        break;
    case title_case:
        transformed=toTitleCase(in);
        break;
    case first_letter_uppercase:
        transformed=capitaliseFirstLetter(in);
        break;
    }

    success=true;
    return transformed;
}

QString TransformProvider_Case::toTitleCase(const QString& string)
{
    QStringList parts = string.split(' ', Qt::SkipEmptyParts);
    for (int i = 0; i < parts.size(); ++i)
    {
        parts[i]=parts[i].toLower();
        parts[i].replace(0, 1, parts[i][0].toUpper());
    }
    return parts.join(" ");
}

QString TransformProvider_Case::capitaliseFirstLetter(const QString& string)
{
    QString result=string.toLower();
    int index=0;
    foreach (QChar character,result)
    {
        if (character.isLetter())
        {
            result[index]=character.toUpper();
            break;
        }
        index++;
    }
    return result;
}


