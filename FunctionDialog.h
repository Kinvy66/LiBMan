#ifndef FUNCTIONDIALOG_H
#define FUNCTIONDIALOG_H

#include <QDialog>

namespace Ui {
class FunctionDialog;
}

class FunctionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FunctionDialog(QWidget *parent = nullptr);
    ~FunctionDialog();
    
private slots:
    void on_pushButton_Save_clicked();
    
    void on_pushButton_Cancel_clicked();
    
private:
    Ui::FunctionDialog *ui;
};

#endif // FUNCTIONDIALOG_H
