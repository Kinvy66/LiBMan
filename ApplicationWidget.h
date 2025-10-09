#ifndef APPLICATIONWIDGET_H
#define APPLICATIONWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTreeWidget>
#include <QPlainTextEdit>


namespace Ui {
class ApplicationWidget;
}

class ApplicationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ApplicationWidget(QWidget *parent = nullptr);
    ~ApplicationWidget();
    
    void renderData();
    void modelTree();
    void parametersTree();
    QPlainTextEdit* getLogWidget();
    
public slots:
    void on1Second();
    void onParametersChanged(QTreeWidgetItem *item, int column);
   

private:
    Ui::ApplicationWidget *ui;
    
    QTimer* m_timer;
};

#endif // APPLICATIONWIDGET_H
