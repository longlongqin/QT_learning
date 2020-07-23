#include "mainwindow.h"
#include "ui_mainwindow.h"

//用于：使用代码创建动作与添加图标
#include <QAction>
#include <QIcon>

#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <Qt>

#include <QLineEdit>
#include <QDialog>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isUntitled = true; //初始化文件为 未保存状态
    curFile = tr("未命名.txt"); // 初始化文件名为“未命名.txt”
    setWindowTitle(curFile); //初始化窗口标题为文件名

    findDlg = new QDialog(this);
    findDlg->setWindowTitle("查找");
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *btn = new QPushButton(tr("查找下一个"), findDlg);
    QVBoxLayout *layout = new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(btn);
    connect(btn,SIGNAL(clicked()), this, SLOT(showFindText()));


    connect(ui->textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(showCursorPos()));

    //在状态栏添加一个标签部件用来显示一般的提示信息
    statusLable = new QLabel;
    statusLable->setMinimumSize(150,20); //设置标签最小尺寸
    statusLable->setFrameShape(QFrame::WinPanel); //设置标签形状
    statusLable->setFrameShadow(QFrame::Sunken); //设置标签阴影
    ui->statusbar->addWidget(statusLable);  //在状态栏添加一个标签
    statusLable->setText(tr("欢迎！"));

    //在状态栏显示永久信息（在最右端显示）
    permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);
    permanent->setText(
                tr("<a href=\"https://wizardforcel.gitbooks.io/qt-beginning/content/11.html\">教程</a>"));
    permanent->setOpenExternalLinks(true);
    ui->statusbar->addPermanentWidget(permanent);


    //ui->pushButton->setText(tr("新窗口"));

    /*
    //创建新的动作1
    QAction *openAction = new QAction(tr("&打开"),this);
    //添加图标
    QIcon icon(":/myImages/images/fileopen.png");
    openAction->setIcon(icon);
    //设置快捷键
    openAction->setShortcut(QKeySequence(tr("ctrl+O")));
    //在文件菜单中设置新的打开动作
    ui->menu_F->addAction(openAction);

    //创建新的动作1
    QAction *closeAction = new QAction(tr("&关闭"),this);
    QIcon icon2(":/myImages/images/window-close.png");
    closeAction->setIcon(icon2);
    closeAction->setShortcut(QKeySequence(tr("ctrl+C")));
    ui->menu_F->addAction(closeAction);
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    if(maybeSave() == true)
    {
        isUntitled = true;
        curFile = tr("未命名.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave()
{
    if(ui->textEdit->document()->isModified()) //如果文档被更改了
    {
        //自定义一个警告对话框
        QMessageBox box;
        box.setWindowTitle("警告");
        box.setIcon(QMessageBox::Warning);
        box.setText("是否保存该文本？");
        QPushButton *yesBtn = box.addButton(tr("是(&Y)"), QMessageBox::YesRole);
        box.addButton(tr("否(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton(tr("取消"), QMessageBox::RejectRole);

        box.exec();
        if(box.clickedButton() == yesBtn)
            return save();
        else if(box.clickedButton() == cancelBtn)
            return false;
    }

    return true; //如果文档没有被更改，则直接返回true
}

bool MainWindow::save()
{
    if(isUntitled)
        return saveAs(); //如果文档以前没有保存过，那么执行另存为操作saveAs()
    else
        return saveFile(curFile); //如果已经保存过，那么调用saveFile()执行文件保存操作
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("另存为"),curFile);

    if(fileName.isEmpty())
        return false;

    return  saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        // %1和%2分别对应后面arg两个参数，/n起换行的作用
        QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法写入文件%1:\n %2").arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    //鼠标指针变为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<ui->textEdit->toPlainText();
    //鼠标恢复原来状态
    QApplication::restoreOverrideCursor();
    isUntitled = false;
    //获得文件的标准路径
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}

void MainWindow::on_action_New_triggered()
{
    newFile();
}

void MainWindow::on_action_Save_triggered()
{
    save();
}

void MainWindow::on_action_SaveAs_triggered()
{
    saveAs();
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName); //新建QFike对象
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法读取文件 %1: \n%2.")
                             .arg(fileName).arg(file.errorString()));
        return false; //只读方式打开文件，出错则提示，并返回false
    }

    QTextStream in(&file); //新建文本流对象
    QApplication::setOverrideCursor(Qt::WaitCursor); // 鼠标指针变为等待状态
    //读取文件的全部文本内容，并添加到编辑器中
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor(); // 鼠标指针恢复原来的状态

    //设置当前文件
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;

}

void MainWindow::on_action_Open_triggered() //打开动作
{
    if(maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this);

        //如果文件名不为空，则加载文件
        if(!fileName.isEmpty())
        {
            loadFile(fileName);
            ui->textEdit->setVisible(true);
        }
    }
}

void MainWindow::on_action_Close_triggered() //关闭动作
{
    if(maybeSave())
        ui->textEdit->setVisible(false);
}

void MainWindow::on_action_Exit_triggered() //退出动作
{
    //先执行关闭操作，在退出程序
    //qApp是指向应用程序的全局指针
    on_action_Close_triggered();
    qApp->quit();
}

void MainWindow::on_action_Undo_triggered() //撤销
{
    ui->textEdit->undo();
}

void MainWindow::on_action_Cut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_action_Copy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_action_Paste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //如果maybeSave()函数 返回true，则关闭程序
    if(maybeSave())
        event->accept();
    else    //否则忽略改事件
        event->ignore();
}

void MainWindow::on_textEdit_textChanged() //为文本编辑区添加 滚动条
//参考：https://blog.csdn.net/HHT0506/article/details/100567581
{
    ui->textEdit->moveCursor(QTextCursor::End);
}

void MainWindow::showFindText()
{
    QString str = findLineEdit->text();
    if(ui->textEdit->find(str,QTextDocument::FindBackward))
    {
        //查找到之后高亮显示
        QPalette palette = ui->textEdit->palette();
        palette.setColor(QPalette::Highlight,
                         palette.color(QPalette::Active,QPalette::Highlight));
        ui->textEdit->setPalette(palette);
    }
    else
        QMessageBox::warning(this, tr("查找"), tr("找不到: %1").arg(str));
}

void MainWindow::on_action_Find_triggered()
{
    findDlg->show();
}


#include <QPlainTextEdit>
void MainWindow::showCursorPos() //在状态栏显示光标所在的行号、列号(参考：https://stackoverrun.com/cn/q/13109015）
{
    int row = ui->textEdit->textCursor().blockNumber()+1;
    int column = ui->textEdit->textCursor().columnNumber()+1;
    ui->statusbar->showMessage(QString("行 %1 列 %2").arg(row).arg(column));
}
