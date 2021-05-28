#include "transformprovider_searchreplace.h"
#include "ui_transformprovider_searchreplace.h"
#include "MainWindow/mainwindow.h" //For signal connection
#include <QRegularExpression>

TransformProvider_searchReplace::TransformProvider_searchReplace(QWidget *parent)
    : TransformProvider(parent) //QWidget constructor called via TransformProvider constructor
    , ui(new Ui::TransformProvider_searchReplace)
{
    ui->setupUi(this);
    displayName=QObject::tr("Search & Replace");

    //Connect change events of all contained control to Main Window's 'transformChanged' slot to trigger an update
    connect(ui->caseSensitiveSearchCheckBox,&QCheckBox::toggled,(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->regularExpressionCheckBox,&QCheckBox::toggled,(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->replaceWithLineEdit,&QLineEdit::textEdited,(MainWindow*)parent, &MainWindow::transformChanged);
    connect(ui->searchForLineEdit,&QLineEdit::textEdited,(MainWindow*)parent, &MainWindow::transformChanged);
}

TransformProvider_searchReplace::~TransformProvider_searchReplace()
{
    delete ui;
}

void TransformProvider_searchReplace::UpdateGUIvars()
{
    caseSensitiveSearch=ui->caseSensitiveSearchCheckBox->isChecked();
    regularExpression=ui->regularExpressionCheckBox->isChecked();
    replaceWith=ui->replaceWithLineEdit->text();
    searchFor= ui->searchForLineEdit->text();
}

QString TransformProvider_searchReplace::transform(const QString& inFullUrl, const QString& in, int index, bool& success)
{
    QString transformed=in;
    (void)inFullUrl;
    (void)index;

    if (regularExpression)
    {
        QRegularExpression::PatternOption patternOption=caseSensitiveSearch? QRegularExpression::PatternOption::NoPatternOption : QRegularExpression::PatternOption::CaseInsensitiveOption;
        QRegularExpression regexp(searchFor, patternOption);
        transformed.replace(regexp,replaceWith);
    }
    else
    {
        Qt::CaseSensitivity cs=caseSensitiveSearch?Qt::CaseSensitive : Qt::CaseInsensitive;
        transformed.replace(searchFor,replaceWith,cs);
    }
    success=true;
    return transformed;
}

