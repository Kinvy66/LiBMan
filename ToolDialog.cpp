#include "ToolDialog.h"
#include "ui_ToolDialog.h"

ToolDialog::ToolDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ToolDialog)
{
    ui->setupUi(this);
    setWindowTitle("工具菜单");
}

ToolDialog::~ToolDialog()
{
    delete ui;
}

void ToolDialog::setContent(const QString &str)
{
    
    ui->label->setText("工具-"+ str);
}

void ToolDialog::on_pushButton_OK_clicked()
{
    // TODO
    accept();
}


void ToolDialog::on_pushButton_Cancel_clicked()
{
    // TODO
    accept();
}

