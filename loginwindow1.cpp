/********************************************************************
文件名：loginwindow1.cpp
功能模块和目的：实现登录操作，包括注册和进入主界面
开发者：程晔安
日期：8.2
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "loginwindow1.h"
#include "ui_loginwindow1.h"
#include "qstring.h"
#include <QMessageBox>
#include "QRadioButton"
#include "registerwindow.h"
#include "mydatabase.h"
#include "QDebug"


#include "customer.h"
#include "hotelmanager.h"
#include "hotel.h"
#include "platformadmin.h"
#include "order.h"

//外部变量
extern QVector<Customer>g_Customerlist;
extern QVector<HotelManager>g_HotelManagerlist;
extern QVector<Hotel>g_Hotellist;
extern QVector<PlatformAdmin>g_PlatformAdminlist;
extern QVector<Order>g_Orderlist;


//清空密码，以便再次登陆
void loginwindow1::ClearPassword()
{
    ui->linePassword->clear();
}

loginwindow1::loginwindow1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginwindow1)
{
    ui->setupUi(this);

//装饰


    this->setWindowTitle("APlaceToStay");
    //this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background,
                     QBrush(QPixmap("./standard.jpg").scaled(
         this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);
    this->setFixedSize(this->width(),this->height());
    //this->setWindowFlags(Qt::FramelessWindowHint);

    ui->linePassword->setEchoMode(QLineEdit::Password);

//初始化列表，将相应信息放在全局变量中

    myDatabase Database;
    Database.InitialCustomer();
    Database.InitialRoom();
    Database.InitialHotelmanager();
    Database.InitialHotelAndRoom();
    Database.InitialPlatformAdmin();
    Database.InitialOrder();


//slots

    //点击注册，根据radiobutton的选择不同实现不同身份相应窗口的跳转
    connect(ui->btnRegister,SIGNAL(clicked(bool)),this,SLOT(RegisterChoose()));
    connect(ui->btnRegister,SIGNAL(clicked(bool)),this,SLOT(hide()));

    //确认登陆
    connect(ui->btnEnter,SIGNAL(clicked(bool)),this,SLOT(Login()));



}

loginwindow1::~loginwindow1()
{
    delete ui;
}

void loginwindow1::Login()
{
    //获取账号密码信息
    QString account = ui->lineAccount->text();
    QString password = ui->linePassword->text();

    //总体的容错判断
    if(password.isEmpty())//密码不能为空
    {
        QMessageBox msgBox;
        msgBox.setText("请输入密码");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        return ;
    }
    //账号不能为空
    if(account.isEmpty())
    {
        QMessageBox::information(this, "Error", "请输入用户名", QMessageBox::Ok);
        return ;
    }

    //判断用户名密码是否正确
    //登录用户界面
    if(ui->btnCustomer->isChecked())
    {
        ui->lineAccount->clear();
        ui->linePassword->clear();
        bool flag = 0;
        //判断登陆信息
        for (int i=0;i<g_Customerlist.size();i++)
        {
            if((account == g_Customerlist[i].GetAccount())&&
                    (password == g_Customerlist[i].GetPassword()))
            {
                flag = 1;
                QMessageBox::information(this, "SUCCESS",
                                         "登录成功", QMessageBox::Ok);
                this->close();
                pMainwindow = new MainWindow(this, &g_Customerlist[i]);
                pMainwindow->show();
            }

        }
        if(flag == 0)
        {
            QMessageBox::information(this, "FAILED", "用户名或密码错误",
                                     QMessageBox::Ok);
            ui->linePassword->clear();
        }
    }

    //登录酒店管理员界面
    else if(ui->btnHotelM->isChecked())
    {
        ui->lineAccount->clear();
        ui->linePassword->clear();
        bool flag = false;

        //判断登陆信息
        for(int i=0;i<g_HotelManagerlist.size();i++)
        {
            //登陆成功
            if((account == g_HotelManagerlist[i].GetAccount())&&
                    (password == g_HotelManagerlist[i].GetPassword()))
            {
                //建立暂时酒店列表
                QString tempHotelName;
                tempHotelName = g_HotelManagerlist[i].GetHotelName();
                for(int j=0;j<g_Hotellist.size();j++)
                {
                    if(g_Hotellist[j].GetHotelName() == tempHotelName)
                    {
                        if(g_Hotellist[j].IsApproved())
                        {
                            flag = true;
                            QMessageBox::information(this, "SUCCESS",
                                                     "登录成功！",
                                                     QMessageBox::Ok);
                            this->close();
                            pWHotel = new whotel(this, &g_Hotellist[j]);
                            pWHotel->show();
                        }
                        else
                        {
                            //如果酒店尚未通过平台审核，也不能登陆
                            QMessageBox::information(this, "Failed",
                                                     "酒店尚未通过平台审核",
                                                     QMessageBox::Ok);
                            ui->linePassword->clear();
                        }
                    }
                }
            }


        }
        if(flag == false)
        {

            QMessageBox::information(this, "FAILED", "登录失败"
                                     , QMessageBox::Ok);
            ui->linePassword->clear();
        }
    }

    //登录平台管理员界面
    else
    {
        ui->lineAccount->clear();
        ui->linePassword->clear();
        bool flag = 0;

        for (int i=0;i<g_PlatformAdminlist.size();i++)
        {
            if((account == g_PlatformAdminlist[i].GetAccount())&&
                    (password == g_PlatformAdminlist[i].GetPassword()))
            {
                flag = 1;
                QMessageBox::information(this, "SUCCESS",
                                         "登录成功", QMessageBox::Ok);
                this->close();
                pPlatform = new Platform(this);
                pPlatform->show();
            }

        }
        if(flag == 0)
        {
            QMessageBox::information(this, "FAILED", "用户名或密码错误",
                                     QMessageBox::Ok);
            ui->linePassword->clear();
        }
    }
}

//选择用户或者酒店注册
void loginwindow1::RegisterChoose()
{

    //进入用户注册界面
    if(ui->btnCustomer->isChecked())
    {
        pRegister = new registerWindow(this);
        pRegister->show();
    }
    //平台管理员界面，唯一账号，不可注册
    //唯一账号：
    //账号：kkk
    //密码：1234567890
    else if (ui->btnPlatformM->isChecked())
    {
        QMessageBox::information(this,
                                 "ERROR",
                                 "管理员账户不能被注册，请联系平台负责人找回账号",
                                 QMessageBox::Ok);

    }

    //进入酒店管理员注册界面
    else
    {
        pHtl = new hotelregister(this);
        pHtl->show();
    }
}
