#include "mainwindow.h"

#include <QApplication>

#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale()); //设置编码

    w.show();
    return a.exec();
}
