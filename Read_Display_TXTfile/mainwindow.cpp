#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // 开始创建文件对象
    QFile file(QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Text Files (*.txt)")));

    //现在需要打开这个文件，使用stream来读取文件内容
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file); //指向该文件
    QString text = stream.readAll();

    QMessageBox box;
    box.setText(text);
    box.exec();
    file.close();

}
