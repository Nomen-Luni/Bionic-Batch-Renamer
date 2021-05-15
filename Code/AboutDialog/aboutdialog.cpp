#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "version.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QString aboutText=ui->aboutLabel->text();
    ui->aboutLabel->setText(aboutText.replace("SOFTWARE_VERSION",SOFTWARE_VERSION,Qt::CaseSensitive));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
