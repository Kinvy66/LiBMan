#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("系统设置");
    
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

/**
 * @brief 设置显示内容
 * @param str
 */
void SettingDialog::setContent(const QString &str)
{
    ui->label->setText(str);
}



void SettingDialog::on_pushButton_OK_clicked()
{
    accept();
}


void SettingDialog::on_pushButton_Cancel_clicked()
{
    accept();
}


void SettingDialog::on_pushButton_Apply_clicked()
{
    accept();
}

