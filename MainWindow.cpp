#include "MainWindow.h"
#include <QComboBox>
#include <QTimer>
#include <QFileDialog>

#if !SARIBBON_USE_3RDPARTY_FRAMELESSHELPER
#include "SAFramelessHelper.h"
#endif

#include "SARibbonApplicationButton.h"
#include "SARibbonBar.h"
#include "SARibbonButtonGroupWidget.h"
#include "SARibbonCategory.h"
#include <QCheckBox>
#include "SARibbonColorToolButton.h"
#include <QComboBox>
#include "SARibbonCustomizeDialog.h"
#include "SARibbonCustomizeWidget.h"
#include "SARibbonGallery.h"

#include "SARibbonMenu.h"
#include "SARibbonPanel.h"
#include "SARibbonQuickAccessBar.h"
#include "SARibbonToolButton.h"
#include "SARibbonCtrlContainer.h"
#include "colorWidgets/SAColorGridWidget.h"
#include "colorWidgets/SAColorPaletteGridWidget.h"
#include "SARibbonSystemButtonBar.h"
#include "SARibbonApplicationWidget.h"
#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCalendarWidget>
#include <QDebug>
#include <QElapsedTimer>
#include <QFile>
#include <QFileDialog>
#include <QFontComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QStatusBar>
#include <QTextEdit>
#include <QTextStream>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QShortcut>
#include <QLineEdit>
#include <QDialogButtonBox>

#include "AboutDialog.h"
#include "ToolDialog.h"
#include "SettingDialog.h"
#include "FunctionDialog.h"
#include "Log.h"



MainWindow::MainWindow(QWidget* parent) : SARibbonMainWindow(parent)
{
    setWindowIcon(QIcon(":/icon/icon/Li.svg"));
    
    setWindowTitle(("新能源电池全生命周期数值模拟软件"));
    // setWindowTitle(("Demo"));
    
    setWindowModified(true);
    
    appWidget = new ApplicationWidget(this);
    setCentralWidget(appWidget);
    
    
    SARibbonBar* ribbon = ribbonBar();
    
    
    mActionsManager = new SARibbonActionsManager(ribbonBar());  // 申明过程已经自动注册所有action
    
    // 取消 applicationButton 
    ribbon->setApplicationButton(nullptr);

    
    // 通过setContentsMargins设置ribbon四周的间距
    ribbon->setContentsMargins(5, 0, 5, 0);
    
    // 添加主标签页,
    SARibbonCategory* categoryMain = ribbon->addCategoryPage(tr("&主页"));
    categoryMain->setObjectName(("categoryMain"));
    createCategoryMain(categoryMain);
    
    
    // 添加条件标签页
    SARibbonCategory* categoryCondition = ribbon->addCategoryPage(tr("&条件"));
    categoryCondition->setObjectName(("categoryCondition"));
    createCategoryCondition(categoryCondition);
    
    
    // 添加条计算标签页
    SARibbonCategory* categoryCaculator = ribbon->addCategoryPage(tr("&计算"));
    categoryCaculator->setObjectName(("categoryCaculator"));
    createCategoryCaculator(categoryCaculator);
    
    
    // 添加条计算标签页
    SARibbonCategory* categoryOther = ribbon->addCategoryPage(tr("&其他"));
    categoryOther->setObjectName(("categoryOther"));
    createCategoryOther(categoryOther);
    
    
    // ribbonBar()->setRibbonStyle(SARibbonBar::RibbonStyleLooseTwoRow);
    
    createApplicationMenuButton();
    
    //! 全屏显示
    showMaximized();
    // this->resize(800, 600);   // 窗口大小 800x600
    
    
}

MainWindow::~MainWindow() {}


/**
 * @brief 创建界面左上角的菜单按钮
 */
void MainWindow::createApplicationMenuButton()
{
    SARibbonQuickAccessBar* quickAccessBar = ribbonBar()->quickAccessBar();
    
    
    // 1. 文件
    QToolButton* fileAction = new QToolButton(this);
    fileAction->setText("文件");
    fileAction->setPopupMode(QToolButton::InstantPopup); // 点击直接弹出菜单
    
    QMenu* fileMenu = new QMenu(this);
    fileMenu->addAction(createAction("新建", ":/icon/icon/icon_gu99np4tjn/new_small.svg"));
    QAction* openAction = createAction("打开", ":/icon/icon/icon_gu99np4tjn/open_small.svg");
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpenFile);
    fileMenu->addAction(openAction);
    fileMenu->addAction(createAction("保存", ":/icon/icon/icon_gu99np4tjn/save_small.svg"));
    fileAction->setStyleSheet("QToolButton::menu-indicator { image: none; }");
    fileAction->setMenu(fileMenu);
    quickAccessBar->addWidget(fileAction);
    
    // 2. 工具
    QToolButton* toolAction = new QToolButton(this);
    toolAction->setText("工具");
    toolAction->setPopupMode(QToolButton::InstantPopup); 
    
    QMenu* toolMenu = new QMenu(this);

    QAction* tool1 =  createAction("功能1", ":/icon/icon/icon_gu99np4tjn/tool.svg");
    connect(tool1, &QAction::triggered, this, &MainWindow::onActionTool);
    toolMenu->addAction(tool1);
    QAction* tool2 =  createAction("功能2", ":/icon/icon/icon_gu99np4tjn/tool.svg");
    toolMenu->addAction(tool2);
    connect(tool2, &QAction::triggered, this, &MainWindow::onActionTool);
    
    // 功能3（带子菜单）
    QMenu* subMenu = new QMenu("功能3", this);  // 创建二级菜单
    QAction* sub1 = createAction("子功能3-1", nullptr);
    subMenu->addAction(sub1);
    QAction* sub2 = createAction("子功能3-2", nullptr);
    subMenu->addAction(sub2);
    QAction* sub3 = createAction("子功能3-3", nullptr);
    subMenu->addAction(sub3);
    connect(sub1, &QAction::triggered, this, &MainWindow::onActionTool);
    connect(sub2, &QAction::triggered, this, &MainWindow::onActionTool);
    connect(sub3, &QAction::triggered, this, &MainWindow::onActionTool);
    toolMenu->addMenu(subMenu);
    
    QAction* tool4 =  createAction("功能4", nullptr);
    toolMenu->addAction(tool4);
    connect(tool4, &QAction::triggered, this, &MainWindow::onActionTool);

    toolAction->setStyleSheet("QToolButton::menu-indicator { image: none; }");
    toolAction->setMenu(toolMenu);
    
    quickAccessBar->addWidget(toolAction);
    
    // 3. 系统设置
    QToolButton* settingAction = new QToolButton(this);
    settingAction->setText("系统设置");
    settingAction->setPopupMode(QToolButton::InstantPopup);
    
    QMenu* settingMenu = new QMenu(this);
    
    QAction* setting1 =  createAction("系统设置1", ":/icon/icon/icon_gu99np4tjn/setting.svg");
    connect(setting1, &QAction::triggered, this, &MainWindow::onActionSetting);
    settingMenu->addAction(setting1);
    
    QAction* setting2 =  createAction("系统设置2", nullptr);
    connect(setting2, &QAction::triggered, this, &MainWindow::onActionSetting);
    settingMenu->addAction(setting2);
    
    settingAction->setStyleSheet("QToolButton::menu-indicator { image: none; }");
    settingAction->setMenu(settingMenu);
    
    quickAccessBar->addWidget(settingAction);
    
    
    // 4. 关于
    QAction* aboutAction = createAction("关于", nullptr, "about-menu");
    quickAccessBar->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onActionAbout);
    
    
    // quickAccessBar->addSeparator();
    
}

/**
 * @brief 关于菜单
 */
void MainWindow::onActionAbout()
{
    AboutDialog* abuotDlg = new AboutDialog(this);
    
    abuotDlg->exec();
    // abuotDlg.fromXml("customize.xml");
}

/**
 * @brief 工具菜单
 */
void MainWindow::onActionTool()
{
    QAction *action = qobject_cast<QAction*>(sender()); // 获取发送信号的对象
    
    if (action) {
        QString text = action->text();
        ToolDialog* dlg = new ToolDialog(this);
        dlg->setContent(text);
        dlg->exec();
    }
}

/**
 * @brief 系统设置菜单
 */
void MainWindow::onActionSetting()
{
    QAction *action = qobject_cast<QAction*>(sender()); // 获取发送信号的对象
    
    if (action) {
        QString text = action->text();
        SettingDialog* dlg = new SettingDialog(this);
        dlg->setContent(text);
        dlg->exec();
    }
}

/**
 * @brief 参数配置
 */
void MainWindow::onActionFunction()
{
    FunctionDialog* dlg = new FunctionDialog(this);
    dlg->exec();
}

/**
 * @brief 打开文件
 */
void MainWindow::onOpenFile()
{
    QString defaultDir = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "打开文件",
        defaultDir,                     // 默认目录
        "所有文件 (*.*);;文本文件 (*.txt);;图像文件 (*.png *.jpg)"
        );
    
    if (!fileName.isEmpty()) {
        // label->setText("已选择文件:\n" + fileName);
        LOG_INFO("打开文件:" + fileName, appWidget->getLogWidget());
        
    } else {
        LOG_INFO("未选择任何文件", appWidget->getLogWidget());
    }
}


/**
 * @brief 主页标签菜单
 * @param page
 */
void MainWindow::createCategoryMain(SARibbonCategory* page)
{
    //! 1
    //! panel 1 start
    //!
    
    SARibbonPanel* panelFile = page->addPanel(tr("文件"));
    
    // actionNew - 新建
    QAction* actionNew = createAction(tr("新建"), ":/menu_icon/icon/icon_atotayfbjar/xinjian.svg");
    connect(actionNew, &QAction::triggered, this, [this](bool b) {
        Q_UNUSED(b);
        // this->mTextedit->append("actSaveion clicked");
        this->setWindowModified(false);
        // 更新状态后，需要手动调用ribbonbar刷新重绘标题，目前ribbonbar不会自动检测WindowModified状态
        this->ribbonBar()->repaint();
    });
    actionNew->setShortcut(QKeySequence(QLatin1String("Ctrl+N")));
    addAction(actionNew);
    panelFile->addLargeAction(actionNew);
    
    // actionOpen - 打开
    QAction* actionOpen = createAction(tr("打开"), ":/menu_icon/icon/icon_atotayfbjar/bg-open-folder.svg");
    connect(actionOpen, &QAction::triggered, this, [this](bool b) {
        Q_UNUSED(b);
        // this->mTextedit->append("actSaveion clicked");
        this->setWindowModified(false);
        // 更新状态后，需要手动调用ribbonbar刷新重绘标题，目前ribbonbar不会自动检测WindowModified状态
        this->ribbonBar()->repaint();
    });
    connect(actionOpen, &QAction::triggered, this, &MainWindow::onOpenFile);
    actionOpen->setShortcut(QKeySequence(QLatin1String("Ctrl+O")));
    addAction(actionOpen);
    panelFile->addLargeAction(actionOpen);
    
    
    // actionSave - 报存
    QAction* actionSave = createAction(tr("保存"), ":/menu_icon/icon/icon_atotayfbjar/save-3-fill.svg");
    connect(actionSave, &QAction::triggered, this, [this](bool b) {
        Q_UNUSED(b);
        // this->mTextedit->append("actSaveion clicked");
        this->setWindowModified(false);
        // 更新状态后，需要手动调用ribbonbar刷新重绘标题，目前ribbonbar不会自动检测WindowModified状态
        this->ribbonBar()->repaint();
    });
    actionSave->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));
    addAction(actionSave);
    panelFile->addLargeAction(actionSave);
    
    // actionSave - 报存
    QAction* actionClose = createAction(tr("关闭"), ":/menu_icon/icon/icon_atotayfbjar/folder-close-fill.svg");
    connect(actionClose, &QAction::triggered, this, [this](bool b) {
        Q_UNUSED(b);
        // this->mTextedit->append("actSaveion clicked");
        this->setWindowModified(false);
        // 更新状态后，需要手动调用ribbonbar刷新重绘标题，目前ribbonbar不会自动检测WindowModified状态
        this->ribbonBar()->repaint();
    });
    actionClose->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));
    addAction(actionClose);
    panelFile->addLargeAction(actionClose);
    
    //! 2
    //! panel 2 
    //!
    SARibbonPanel* panel2 = page->addPanel(("panel 2"));
    
    QAction* actionFunction1 = createAction(tr("功能1"), ":/icon/icon/folder-cog.svg");
    addAction(actionFunction1);
    connect(actionFunction1, &QAction::triggered, this, &MainWindow::onActionFunction);
    panel2->addLargeAction(actionFunction1);
    
    QAction* actionFunction2 = createAction(tr("功能2"), ":/icon/icon/folder-star.svg");
    addAction(actionFunction2);
    connect(actionFunction2, &QAction::triggered, this, &MainWindow::onActionFunction);
    panel2->addLargeAction(actionFunction2);
    
    
    QAction* actionFunction3 = createAction(tr("功能3"), ":/icon/icon/folder-stats.svg");
    addAction(actionFunction3);
    connect(actionFunction3, &QAction::triggered, this, &MainWindow::onActionFunction);
    panel2->addLargeAction(actionFunction3);

}

/**
 * @brief 条件标签菜单
 * @param page
 */
void MainWindow::createCategoryCondition(SARibbonCategory* page)
{
    SARibbonPanel* panel3 = page->addPanel(tr("panale3"));
    
    QAction* actionFunction1 = createAction(tr("功能1"), ":/icon/icon/folder-checkmark.svg");
    addAction(actionFunction1);
    connect(actionFunction1, &QAction::triggered, this, &MainWindow::onActionFunction);
    panel3->addLargeAction(actionFunction1);
    
    QAction* actionFunction2 = createAction(tr("功能2"), ":/icon/icon/folder-table.svg");
    addAction(actionFunction2);
    connect(actionFunction2, &QAction::triggered, this, &MainWindow::onActionFunction);
    panel3->addLargeAction(actionFunction2);
    
    
    QAction* actionFunction3 = createAction(tr("功能3"), ":/icon/icon/folder-stats.svg");
    addAction(actionFunction3);
    connect(actionFunction3, &QAction::triggered, this, &MainWindow::onActionFunction);
    panel3->addLargeAction(actionFunction3);
}

/**
 * @brief 计算标签菜单
 * @param page
 */
void MainWindow::createCategoryCaculator(SARibbonCategory* page)
{
    SARibbonPanel* panale4 = page->addPanel(tr("panale4"));
    
    QAction* actionFunction1 = createAction(tr("功能1"), ":/menu_icon/icon/icon_gu99np4tjn/chakanshuji.svg");
    addAction(actionFunction1);
    panale4->addLargeAction(actionFunction1);
    
    QAction* actionFunction2 = createAction(tr("功能2"), ":/menu_icon/icon/icon_gu99np4tjn/chuansong.svg");
    addAction(actionFunction2);
    panale4->addLargeAction(actionFunction2);
    
    
    QAction* actionFunction3 = createAction(tr("功能3"), ":/menu_icon/icon/icon_gu99np4tjn/dalou.svg");
    addAction(actionFunction3);
    panale4->addLargeAction(actionFunction3);
    
    
    
    SARibbonPanel* panale5 = page->addPanel(tr("panale5"));
    
    QAction* actionFunction4 = createAction(tr("功能4"), ":/menu_icon/icon/icon_gu99np4tjn/duowei.svg");
    addAction(actionFunction4);
    panale5->addLargeAction(actionFunction4);
    
    QAction* actionFunction5 = createAction(tr("功能5"), ":/menu_icon/icon/icon_gu99np4tjn/fenbianshuai.svg");
    addAction(actionFunction5);
    panale5->addLargeAction(actionFunction5);
    
    
    QAction* actionFunction6 = createAction(tr("功能6"), ":/menu_icon/icon/icon_gu99np4tjn/gengduo-2.svg");
    addAction(actionFunction6);
    panale5->addLargeAction(actionFunction6);
    
    QAction* actionFunction7 = createAction(tr("功能7"), ":/menu_icon/icon/icon_gu99np4tjn/gongju.svg");
    addAction(actionFunction7);
    panale5->addLargeAction(actionFunction7);
    
    QAction* actionFunction8 = createAction(tr("功能8"), ":/menu_icon/icon/icon_gu99np4tjn/guanxi.svg");
    addAction(actionFunction8);
    panale5->addLargeAction(actionFunction8);
}

/**
 * @brief 其他标签菜单
 * @param page
 */
void MainWindow::createCategoryOther(SARibbonCategory* page)
{
    SARibbonPanel* panale7 = page->addPanel(tr("panale7"));
    
    QAction* actionFunction1 = createAction(tr("功能1"), ":/menu_icon/icon/icon_gu99np4tjn/nizhuan.svg");
    addAction(actionFunction1);
    panale7->addLargeAction(actionFunction1);
    
    QAction* actionFunction2 = createAction(tr("功能2"), ":/menu_icon/icon/icon_gu99np4tjn/paihang.svg");
    addAction(actionFunction2);
    panale7->addLargeAction(actionFunction2);
    
    
    QAction* actionFunction3 = createAction(tr("功能3"), ":/menu_icon/icon/icon_gu99np4tjn/tishi.svg");
    addAction(actionFunction3);
    panale7->addLargeAction(actionFunction3);
    
    QAction* actionFunction4 = createAction(tr("功能4"), ":/menu_icon/icon/icon_gu99np4tjn/xingtai.svg");
    addAction(actionFunction4);
    panale7->addLargeAction(actionFunction4);
    
}

/**
 * @brief 创建动作
 * @param text 动作文本
 * @param iconurl 图标路径
 * @param objName 对象名称
 * @return 创建的动作指针
 *
 * cn:创建带有文本、图标和对象名称的动作
 * en:Create an action with text, icon, and object name
 */
QAction* MainWindow::createAction(const QString& text, const QString& iconurl, const QString& objName)
{
    QAction* act = new QAction(this);
    act->setText(text);
    act->setIcon(QIcon(iconurl));
    act->setObjectName(objName);
    return act;
}

/**
 * @brief 创建动作（重载版本）
 * @param text 动作文本
 * @param iconurl 图标路径
 * @return 创建的动作指针
 *
 * cn:创建带有文本和图标的动作，对象名称使用文本内容
 * en:Create an action with text and icon, using the text content as the object name
 */
QAction* MainWindow::createAction(const QString& text, const QString& iconurl)
{
    QAction* act = new QAction(this);
    act->setText(text);
    act->setIcon(QIcon(iconurl));
    act->setObjectName(text);
    return act;
}

