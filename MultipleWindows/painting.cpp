#include "painting.h"
#include "ui_painting.h"



Painting::Painting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Painting)
{
    ui->setupUi(this);
    setWindowTitle(tr("画图程序"));

    resize(700,500);  //主窗口大小设置为700*500
    area = new PaintArea;
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark); //scrollArea对象的背景色设置为Dark
    scrollArea->setWidget(area);    //讲话不添加到scrollArea
    scrollArea->widget()->setMinimumSize(800,600); //scrollArea初始化的大小设置为800*600
    setCentralWidget(scrollArea); //将scrollArea加入到主窗口的中心区
}

Painting::~Painting()
{
    delete ui;
}


