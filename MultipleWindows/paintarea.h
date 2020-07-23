#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>

//实现涂鸦功能
#include <QMouseEvent>
#include <QPoint>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);

signals:


protected:
    void paintEvent(QPaintEvent*); //重绘事件
private:
    QImage image; //QImage类对象，用于在其上绘图
    QRgb backColor; //QRgb颜色对象，存储image的背景色


protected:
    void mousePressEvent(QMouseEvent *); //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event); //鼠标释放事件
    void paint(QImage &theImage); //绘图
private:
    QPoint lastPoint, endPoint; //定义两个坐标对象存放鼠标指针的前后两个坐标
//    QPixmap pix;
};

#endif // PAINTAREA_H
