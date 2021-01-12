#include "formsd.h"
#include "ui_formsd.h"

Formsd::Formsd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formsd)
{
    ui->setupUi(this);
}

Formsd::~Formsd()
{
    delete ui;
}

void Formsd::on_Formsd_windowTitleChanged(const QString &title)
{

}
