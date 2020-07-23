#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCloseEvent>
#include <QLabel>

//添加前置声明
class QLineEdit;
class QDialog;
class QLabel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


public:
    void newFile(); //新建文件
    bool maybeSave(); //判断是否需要保存
    bool save(); //保存
    bool saveAs(); //另存为
    bool saveFile(const QString& fileName); //保存文件

    bool loadFile(const QString& fileName); //加载（打开）文件

private slots:
    void on_action_New_triggered();

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();

    void on_action_Open_triggered();

    void on_action_Close_triggered();

    void on_action_Exit_triggered();

    void on_action_Undo_triggered();

    void on_action_Cut_triggered();

    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_textEdit_textChanged();

    void showFindText();
    void on_action_Find_triggered();

    void showCursorPos(); //在状态栏显示光标所在的行号、列号

private:
    bool isUntitled; //为真则表示文件未保存过，否则表示已经保存
    QString curFile; //保存当前打开的文件的路径

    QLineEdit *findLineEdit;
    QDialog *findDlg;

    QLabel *statusLable; //状态栏添加一个标签部件用来显示一般的提示信息（需要使用addWidget()函数）
    QLabel *permanent; //在状态栏显示永久信息（需要使用addPermanentWidget()函数）

protected:
    void closeEvent(QCloseEvent *event); //关闭事件
};
#endif // MAINWINDOW_H
