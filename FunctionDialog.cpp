#include "FunctionDialog.h"
#include "ui_FunctionDialog.h"

FunctionDialog::FunctionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FunctionDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("参数配置");
}

FunctionDialog::~FunctionDialog()
{
    delete ui;
}

void FunctionDialog::on_pushButton_Save_clicked()
{
    accept();
}


void FunctionDialog::on_pushButton_Cancel_clicked()
{
    accept();
}

