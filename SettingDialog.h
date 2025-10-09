#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
    
    void setContent(const QString& str);
    
private slots:
    void on_pushButton_OK_clicked();
    
    void on_pushButton_Cancel_clicked();
    
    void on_pushButton_Apply_clicked();
    
private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
