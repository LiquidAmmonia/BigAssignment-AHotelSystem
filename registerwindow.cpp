
/********************************************************************
文件名：registerwindow.cpp
功能模块和目的：显示注册界面
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "QMessageBox"

#include"customer.h"

extern QVector<Customer>g_Customerlist;

//可跳回登陆界面
registerWindow::registerWindow(loginwindow1*l):
    ui(new Ui::registerWindow)
{
    ui->setupUi(this);
    parent = l;
    //装饰
    ui->linePassword->setEchoMode(QLineEdit::Password);
    ui->linePassword2->setEchoMode(QLineEdit::Password);


    this->setWindowTitle("APlaceToStay--Register");
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background,
                     QBrush(QPixmap("://register.jpg").scaled(
         this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);
    this->setFixedSize(this->width(),this->height());

    //接口

    //返回登陆主界面
    connect(ui->btnCancel,SIGNAL(clicked(bool)),parent,SLOT(show()));
    connect(ui->btnCancel,SIGNAL(clicked(bool)),this,SLOT(hide()));

    //主要实现功能函数
    connect(ui->btnEnter,SIGNAL(clicked(bool)), this,SLOT(SendInfo()));

}

registerWindow::~registerWindow()
{
    delete ui;
}

//接受用户输入并处理
void registerWindow::SendInfo()
{
    bool flag = false;

    //必须两次判断都成立才可进行之后操作
    flag = CheckEntering() && CheckCusInfo();

    if(flag == true)
    {
        //之后可以扩展的功能单元——手机验证用户注册
        QMessageBox::information(this, "手机验证码", "请注意查收手机验证码", QMessageBox::Ok);

        //加入全局变量
        Customer newCustomer(Account,Password,Phone);

        g_Customerlist.push_back(newCustomer);

        QMessageBox::information(this, "success!", "注册成功！", QMessageBox::Ok);
    }

    //成功后返回主窗口
    this->close();
    parent->show();

}

//判断输入是否符合规定
bool registerWindow::CheckEntering()
{
    //检查账户和密码的输入是否符合规则
    bool flag = true;

    //接收用户输入
    Password = ui->linePassword->text();
    Password2 = ui->linePassword2->text();
    Account = ui->lineAccount->text();
    Phone = ui->linePhone->text();

    //判断
    if(Password.isEmpty())
    {
        QMessageBox::information(this, "entering Error", "输入密码不能为空", QMessageBox::Ok);
        flag = false;
    }
    if(Password.length()<6||Password.length()>11)
    {
        QMessageBox::information(this, "length Error", "密码长度应在6~11位以内", QMessageBox::Ok);
        flag = false;
    }
    if(Password != Password2)
    {
        QMessageBox::information(this, "different Entering", "两次密码输入不同", QMessageBox::Ok);
        flag = false;
    }
    if(Account.isEmpty())
    {
        QMessageBox::information(this, "entering Error", "输入账户不能为空！",QMessageBox::Ok);
        flag = false;
    }
    if(Phone.isEmpty())
    {
        QMessageBox::information(this, "entering Error", "输入电话不能为空！",QMessageBox::Ok);
        flag = false;
    }
    if(Phone.length()!=11)
    {
        QMessageBox::information(this, "entering Error", "输入电话号码应为11位！",QMessageBox::Ok);
        flag = false;
    }
    return flag;

}

//判断是否与已有信息冲突，即不能重复注册
bool registerWindow::CheckCusInfo()
{
    bool flag = true;

    //账号重复
    for(int i=0;i<g_Customerlist.length();i++)
        if(Account == g_Customerlist[i].GetAccount())
        {
            QMessageBox::information(this, "registered", "该用户已经注册", QMessageBox::Ok);
            flag = false;
        }

    //电话号码重复
    for(int i=0;i<g_Customerlist.length();i++)
    {
        if(g_Customerlist[i].IsPhoneUsed(Phone))
        {
            QMessageBox::information(this, "registered", "该电话已被用户注册", QMessageBox::Ok);
            flag = false;
        }
    }

    return flag;

}


