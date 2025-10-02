#include "MainWindow.h"
#include <QComboBox>
#include <QTimer>

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


MainWindow::MainWindow(QWidget* parent) : SARibbonMainWindow(parent)
{
    setWindowIcon(QIcon(":/icon/icon/SA.svg"));
    
    // setWindowTitle(("新能源电池全生命周期数值模拟软件"));
    setWindowTitle(("Demo"));
    
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
    // showMaximized();
    this->resize(800, 600);   // 窗口大小 800x600
    
    
}

MainWindow::~MainWindow() {}


/**
 * @brief 创建界面左上角的菜单按钮
 */
void MainWindow::createApplicationMenuButton()
{
    SARibbonQuickAccessBar* quickAccessBar = ribbonBar()->quickAccessBar();
    
    // QAction* fileAction = createAction("文件", nullptr, "file-menu");
       
    // QMenu* fileMenu = new QMenu("文件", this);
    
    
    // fileMenu->addAction(createAction("新建", nullptr));
    // fileMenu->addAction(createAction("打开", nullptr));
    
    // quickAccessBar->addMenuAction(fileMenu->menuAction());
    // fileAction->setMenu(fileMenu);
    
    // quickAccessBar->addMenuAction(fileAction);
    
    
    QToolButton* fileAction = new QToolButton(this);
    fileAction->setText("文件");
    fileAction->setPopupMode(QToolButton::InstantPopup); // 点击直接弹出菜单
    
    QMenu* fileMenu = new QMenu(this);
    fileMenu->addAction(createAction("新建", nullptr));
    fileMenu->addAction(createAction("打开", nullptr));
    fileAction->setStyleSheet("QToolButton::menu-indicator { image: none; }");
    fileAction->setMenu(fileMenu);
    quickAccessBar->addWidget(fileAction);
    
    
    QAction* toolAction = createAction("工具", nullptr, "tool-menu");
    quickAccessBar->addAction(toolAction);
    
    QAction* settingAction = createAction("系统设置", nullptr, "setting-menu");
    quickAccessBar->addAction(settingAction);
    
    
    QAction* aboutAction = createAction("关于", nullptr, "about-menu");
    quickAccessBar->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onActionAbout);
    
    
    // quickAccessBar->addSeparator();
    
}

/**
 * @brief 关于按钮
 */
void MainWindow::onActionAbout()
{
    QDialog abuotDlg(this);
    abuotDlg.exec();
    // abuotDlg.fromXml("customize.xml");
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
    panel2->addLargeAction(actionFunction1);
    
    QAction* actionFunction2 = createAction(tr("功能2"), ":/icon/icon/folder-star.svg");
    addAction(actionFunction2);
    panel2->addLargeAction(actionFunction2);
    
    
    QAction* actionFunction3 = createAction(tr("功能3"), ":/icon/icon/folder-stats.svg");
    addAction(actionFunction3);
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
    panel3->addLargeAction(actionFunction1);
    
    QAction* actionFunction2 = createAction(tr("功能2"), ":/icon/icon/folder-table.svg");
    addAction(actionFunction2);
    panel3->addLargeAction(actionFunction2);
    
    
    QAction* actionFunction3 = createAction(tr("功能3"), ":/icon/icon/folder-stats.svg");
    addAction(actionFunction3);
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

