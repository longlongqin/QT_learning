#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);



    this->setWindowTitle(tr("可分页查看"));

    m_pageCount = 30;        //每页显示数据数目

//    for(int i = 0; i < 666; i++)
//    {

//        m_vec << "第 " + QString::number(i) + " 条";
//    }
    on_pushButton_clicked();  //⭐⭐⭐很重要

    //默认第一页
    setListWidget(1);
    connect(ui->upPushButton, SIGNAL(clicked()), this, SLOT(upBtnClicked()));
    connect(ui->downPushButton, SIGNAL(clicked()), this, SLOT(downBtnClicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setListWidget(const int &currentPage)
{
    if(currentPage <= 0){

        qDebug() << "Error: The currentPage can't be 0";
        return;
    }

    int startNum = m_pageCount * (currentPage - 1);

    ui->listWidget->clear();

    for(int i = 0; i < m_pageCount; i++){

        if(startNum + i >= m_vec.size())

            break;

        ui->listWidget->addItem(m_vec[startNum + i]);
    }

    m_currentPageNum = currentPage;
    m_countPageNum = m_vec.size() / m_pageCount + 1;
    ui->currentPageLabel->setText(QString::number(m_currentPageNum));
    ui->countPageLabel->setText(QString::number(m_countPageNum));

}

void Widget::upBtnClicked()
{
    setListWidget(m_currentPageNum - 1);
}

void Widget::downBtnClicked()
{
    if(m_currentPageNum >= m_countPageNum)
        return;

    setListWidget(m_currentPageNum + 1);
}

void Widget::on_pushButton_clicked()
{
    // 开始创建文件对象
    QFile file(QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Text Files (*.txt)")));

    //现在需要打开这个文件，使用stream来读取文件内容
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file); //指向该文件
    stream.setCodec("UTF-8");
    while(stream.readLineInto(&line))
    {
        m_vec.push_back(line);
    }


}
