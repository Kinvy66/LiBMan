#include "FunctionDialog.h"
#include "ui_FunctionDialog.h"

FunctionDialog::FunctionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FunctionDialog)
{
    ui->setupUi(this);
}

FunctionDialog::~FunctionDialog()
{
    delete ui;
}
