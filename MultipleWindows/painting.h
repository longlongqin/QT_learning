#ifndef PAINTING_H
#define PAINTING_H

#include <QMainWindow>

#include "paintarea.h"
#include <QScrollArea> //添加画布（提供 横向、纵向的滚动条）


namespace Ui {
class Painting;
}

class Painting : public QMainWindow
{
    Q_OBJECT

public:
    explicit Painting(QWidget *parent = nullptr);
    ~Painting();

private:
    Ui::Painting *ui;


private:
PaintArea *area;
QScrollArea *scrollArea;

};

#endif // PAINTING_H
