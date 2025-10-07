#include "ToolDialog.h"
#include "ui_ToolDialog.h"

ToolDialog::ToolDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ToolDialog)
{
    ui->setupUi(this);
}

ToolDialog::~ToolDialog()
{
    delete ui;
}
