#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SARibbonMainWindow.h"
#include "ApplicationWidget.h"

class SARibbonCategory;
class SARibbonContextCategory;
class SARibbonCustomizeWidget;
class SARibbonActionsManager;
class SARibbonQuickAccessBar;
class SARibbonButtonGroupWidget;
class SARibbonPanel;
class SARibbonApplicationWidget;
class QTextEdit;
class QComboBox;
class QCloseEvent;
class QLineEdit;


class MainWindow : public SARibbonMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private:
    void createApplicationMenuButton();
    void createCategoryMain(SARibbonCategory* page);
    void createCategoryCondition(SARibbonCategory* page);
    void createCategoryCaculator(SARibbonCategory* page);
    void createCategoryOther(SARibbonCategory* page);
    
    QAction* createAction(const QString& text, const QString& iconurl, const QString& objName);
    QAction* createAction(const QString& text, const QString& iconurl);
    
private Q_SLOTS:
    void onActionAbout();
    
private:
    
    SARibbonActionsManager* mActionsManager { nullptr };
    
    ApplicationWidget* appWidget;
    
};

#endif // MAINWINDOW_H
