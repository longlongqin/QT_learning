#include "paintarea.h"

#include <QPainter>
#include <Qt>

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    image = QImage(500,500,QImage::Format_RGB32); //画布的初始化大小为500*500，使用32位颜色
    backColor = qRgb(255,255,255); //画布初始化背景色使用白色
    image.fill(backColor);
}

void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,image);
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)  //当鼠标左键按下
    {
        lastPoint = event->pos();   //获得鼠标指针的当前坐标作为起始坐标
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton) //如果鼠标左键按着 同时 移动鼠标
        //（⭐注意这里是buttons()别忘记那个“s”呀。太惨了，之前没注意这个细节）
    {
        endPoint = event->pos();  //获得鼠标指针的当前坐标作为终止坐标
        paint(image);   //绘制图形
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) //如果鼠标左键释放
    {
        endPoint = event->pos();
        paint(image);
    }
}

void PaintArea::paint(QImage &theImage)
{
    QPainter pp(&theImage);   //在theImage上绘图
    pp.drawLine(lastPoint,endPoint);   //由起始坐标和终止坐标绘制直线
    lastPoint = endPoint;  //让终止坐标变为起始坐标
    update();   //进行更新界面显示，可引起窗口重绘事件，重绘窗口
}
