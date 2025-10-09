#ifndef TOOLDIALOG_H
#define TOOLDIALOG_H

#include <QDialog>

namespace Ui {
class ToolDialog;
}

class ToolDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToolDialog(QWidget *parent = nullptr);
    ~ToolDialog();
    
    void setContent(const QString& str);
    
private slots:
    void on_pushButton_OK_clicked();
    
    void on_pushButton_Cancel_clicked();
    
private:
    Ui::ToolDialog *ui;
};

#endif // TOOLDIALOG_H
