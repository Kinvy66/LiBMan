#include "AboutDialog.h"
#include "ui_AboutDialog.h"
#include <QClipboard>
#include <QApplication>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowTitle("关于");
    
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_pushButton_OK_clicked()
{
    accept(); // 等效于 this->close();
}


void AboutDialog::on_pushButton_Copy_clicked()
{
    QString text = ui->label_about->text();
    
    // 去除 QLabel 中的换行符号格式问题（如果有）
    text.replace("<br>", "\n");
    text.replace("<br/>", "\n");
    text.replace("&nbsp;", " ");
    
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);
    accept();
    
    // 可选：提示复制成功
    // QMessageBox::information(this, tr("复制成功"), tr("关于信息已复制到剪贴板。"));
}

