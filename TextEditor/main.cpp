#include "mainwindow.h"

#include <QApplication>

#include <QTextCodec> //设置编码
#include "logindlg.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale()); //设置编码


    LoginDlg dlg; //建立自己新建的类的对象dlg
    if(dlg.exec() == QDialog::Accepted) // 利用Accepted返回值判断按钮是否被按下
    {
        w.show(); //如果被按下，显示主窗口
        return a.exec(); //程序一直执行，直到主窗口关闭
    }
    else
        return 0; //如果没有被按下，则不进入主窗口，整个程序结束运行

}
