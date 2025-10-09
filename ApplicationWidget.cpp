#include "ApplicationWidget.h"
#include "ui_ApplicationWidget.h"

#include <QTimer>
#include <QDebug>
#include <QRandomGenerator>

#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkNew.h>
#include <vtkSphereSource.h>
#include <vtkSTLReader.h>
#include <vtkConeSource.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>

#include "Log.h"


ApplicationWidget::ApplicationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ApplicationWidget)
{
    ui->setupUi(this);
    renderData();
    modelTree();
    parametersTree();
    LOG_INFO("启动软件", ui->plainTextEdit);
    
    QTimer* m_timer = new QTimer(this);
    m_timer->setInterval(3000);
    
    connect(m_timer, &QTimer::timeout, this, &ApplicationWidget::on1Second);
    m_timer->start();
}

ApplicationWidget::~ApplicationWidget()
{
    delete ui;
}

/**
 * @brief 渲染数据
 */
void ApplicationWidget::renderData()
{
    vtkNew<vtkRenderer> renderer;
    
    ui->openGLWidget->renderWindow()->AddRenderer(renderer);
    ui->openGLWidget->renderWindow()->Render();
   
    
    std::array<std::array<double, 3>, 8> pts = {
        { { {0, 0, 0} }
         ,{ {1, 0, 0} }
         ,{ {1, 1, 0} }
         ,{ {0, 1, 0} }
         ,{ {0, 0, 1} }
         ,{ {1, 0, 1} }
         ,{ {1, 1, 1} }
         ,{ {0, 1, 1} }}
    };
    
    std::array<std::array<vtkIdType, 4>, 6> ordering = {
        { { {0, 1, 2, 3} }
         ,{ {4, 5, 6, 7} }
         ,{ {0, 1, 5, 4} }
         ,{ {1, 2, 6, 5} }
         ,{ {2, 3, 7, 6} }
         ,{ {3, 0, 4, 7} }}
    };
    
    vtkNew<vtkPolyData> cube;
    vtkNew<vtkPoints> points;
    vtkNew<vtkCellArray> polys;
    vtkNew<vtkFloatArray> scalars;
    

    
    for (int i = 0; i < pts.size(); ++i) {
        points->InsertPoint(i, pts[i].data());
        scalars->InsertTuple1(i, i);
    }
    
    for (auto&& i : ordering) {
        polys->InsertNextCell(vtkIdType(i.size()), i.data());
    }
    
    cube->SetPoints(points);
    cube->SetPolys(polys);
    cube->GetPointData()->SetScalars(scalars);
    
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(cube);
    mapper->SetScalarRange(cube->GetScalarRange());
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
    
}

/**
 * @brief 模型树
 */
void ApplicationWidget::modelTree()
{
    ui->treeWidget->setHeaderLabel("模型");
    
    QTreeWidgetItem *Group1 = new QTreeWidgetItem( ui->treeWidget);
    Group1->setText(0, "模型组1");
    
    
    // 子节点
    QTreeWidgetItem *m1 = new QTreeWidgetItem(Group1);
    m1->setText(0, "模型1");
    
    QTreeWidgetItem *m2 = new QTreeWidgetItem(Group1);
    m2->setText(0, "模型2");
    
    QTreeWidgetItem *m3 = new QTreeWidgetItem(Group1);
    m3->setText(0, "模型3");
    
    QTreeWidgetItem *m4 = new QTreeWidgetItem(Group1);
    m4->setText(0, "模型4");
    
    QTreeWidgetItem *m5 = new QTreeWidgetItem(Group1);
    m5->setText(0, "模型5");
    
    QTreeWidgetItem *m6 = new QTreeWidgetItem(Group1);
    m6->setText(0, "模型6");
    
    QTreeWidgetItem *m7 = new QTreeWidgetItem(Group1);
    m7->setText(0, "模型7");
    
    QTreeWidgetItem *m8 = new QTreeWidgetItem(Group1);
    m8->setText(0, "模型8");

}

/**
 * @brief 参数配置
 */
void ApplicationWidget::parametersTree()
{
    ui->treeWidget_parametes->setColumnCount(2);
    ui->treeWidget_parametes->setHeaderHidden(true);
    
    QTreeWidgetItem *group1 = new QTreeWidgetItem( ui->treeWidget_parametes);
    group1->setText(0, "属性信息");
    group1->setFlags(Qt::ItemIsEnabled);
    
    QTreeWidgetItem *item1 = new QTreeWidgetItem(group1);
    item1->setText(0, "参数1");
    item1->setText(1, "192");
    item1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item1->setFlags(item1->flags() | Qt::ItemIsEditable);
    
    QTreeWidgetItem *item2 = new QTreeWidgetItem(group1);
    item2->setText(0, "参数2");
    item2->setText(1, "{-0, 3}");
    item2->setFlags(item2->flags() | Qt::ItemIsEditable);
    
    QTreeWidgetItem *item3 = new QTreeWidgetItem(group1);
    item3->setText(0, "参数3");
    item3->setText(1, "{-0, 3}");
    item3->setFlags(item3->flags() | Qt::ItemIsEditable);
    
    
    QTreeWidgetItem *item4 = new QTreeWidgetItem(group1);
    item4->setText(0, "参数4");
    item4->setText(1, "%12");
    item4->setFlags(item4->flags() | Qt::ItemIsEditable);
    
    // ===== 参数组2 =====
    QTreeWidgetItem *group2 = new QTreeWidgetItem( ui->treeWidget_parametes);
    group2->setText(0, "参数组2");
    group2->setFlags(Qt::ItemIsEnabled);
    
    for (int i = 0; i < 6; ++i) {
        QTreeWidgetItem *g2Item = new QTreeWidgetItem(group2);
        g2Item->setText(0, "参数" + QString::number(i+1));
        g2Item->setText(1, QString::number(QRandomGenerator::global()->bounded(200)));
        g2Item->setFlags(g2Item->flags() | Qt::ItemIsEditable); 
    }
    
    
    // ===== 参数组3 =====
    QTreeWidgetItem *group3 = new QTreeWidgetItem( ui->treeWidget_parametes);
    group3->setText(0, "参数组3");
    group3->setFlags(Qt::ItemIsEnabled);
    
    for (int i = 0; i < 20; ++i) {
        QTreeWidgetItem *g3Item = new QTreeWidgetItem(group3);
        g3Item->setText(0, "参数" + QString::number(i+1));
        g3Item->setText(1, QString::number(QRandomGenerator::global()->bounded(300)));
        g3Item->setFlags(g3Item->flags() | Qt::ItemIsEditable); 
    }
        
    
    // 展开全部节点
    ui->treeWidget_parametes->expandAll();
    
    
    ui->treeWidget_parametes->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止所有列默认编辑
    
    connect(ui->treeWidget_parametes, &QTreeWidget::itemDoubleClicked, this,
            [=](QTreeWidgetItem *item, int column) {
                if (column == 1) // 仅当点击第二列时
                    ui->treeWidget_parametes->editItem(item, column);
            });
    
    connect(ui->treeWidget_parametes, &QTreeWidget::itemChanged, this, &ApplicationWidget::onParametersChanged);
}

QPlainTextEdit *ApplicationWidget::getLogWidget()
{
    return ui->plainTextEdit;
}

void ApplicationWidget::on1Second()
{
    static uint32_t i = 0;
    LOG_INFO("输出日志-" + QString::number(i), ui->plainTextEdit);
    i++;
    
}

/**
 * @brief  参数修改
 * @param item
 * @param column
 */
void ApplicationWidget::onParametersChanged(QTreeWidgetItem *item, int column)
{
    if (column == 1) {
        QString str = QString("配置项修改:") + item->text(0) +  QString("=>") + item->text(1);
        LOG_INFO(str, ui->plainTextEdit);
    }

}
