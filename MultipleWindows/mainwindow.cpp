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
    textediter = new TextEditer(this);
    textediter->show();

}

void MainWindow::on_pushButton_2_clicked()
{
    painter = new Painting(this);
    painter->show();
}
