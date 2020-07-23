#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;


protected:
    void setListWidget(const int &currentPage);

protected slots:
    void upBtnClicked();
    void downBtnClicked();

private slots:
    void on_pushButton_clicked();

private:
    QVector<QString> m_vec;
    int m_pageCount;       //每页显示的数目

    int m_currentPageNum; //当前页数
    int m_countPageNum;   //总页数

    QString line;
};
#endif // WIDGET_H
