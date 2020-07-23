#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "textediter.h"
#include "painting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked(); //转入“文档编辑器”窗口

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

private:
    TextEditer *textediter; //文档编辑器 类
    Painting   *painter;    //画图程序   类
};
#endif // MAINWINDOW_H
