#include "logindlg.h"
#include "ui_logindlg.h"

#include <QMessageBox> //使用对话框

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginBtn_clicked()
{
    //判断用户名、密码是否正确。如果错误则弹出对话框警告
    //trimmed()可以去除字符串前后的空白字符
    if(ui->usrLineEdit->text().trimmed() == tr("1")
            && ui->pwdLineEdit->text().trimmed() == tr("1"))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this, tr("waring"), tr("用户名或密码错误！"));

        //当输入用户名或密码错误时，清空内容 并 将光标定位至用户名输入处
        ui->usrLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->usrLineEdit->setFocus();
    }
}
