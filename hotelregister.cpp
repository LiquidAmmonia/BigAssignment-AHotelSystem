
/********************************************************************
文件名：
功能模块和目的：
开发者：程晔安
日期：8.2
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "hotelregister.h"
#include "ui_hotelregister.h"
#include "QMessageBox"
#include "mydatabase.h"

#include "hotelmanager.h"
#include "hotel.h"

extern QVector<HotelManager>g_HotelManagerlist;
extern QVector<Hotel>g_Hotellist;

hotelregister::hotelregister(loginwindow1*l) :
    ui(new Ui::hotelregister)
{
    ui->setupUi(this);
    parent = l;

    //装饰
    this->setWindowTitle("Get your own hotel!");
    this->setFixedSize(this->width(),this->height());

    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background,
                     QBrush(QPixmap("://register.jpg").scaled(
         this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);
    this->setFixedSize(this->width(),this->height());

    //接口
    //返回之前列表
    connect(ui->btnCancle,SIGNAL(clicked(bool)),parent,SLOT(show()));
    connect(ui->btnCancle,SIGNAL(clicked(bool)),this,SLOT(hide()));

    //主要功能函数，创建相应的酒店管理员和酒店实例
    connect(ui->btnEnter,SIGNAL(clicked(bool)), this,SLOT(SendInfo()));



}

hotelregister::~hotelregister()
{
    delete ui;
}

void hotelregister::SendInfo()
{
    bool flag = false;

    //判断同时满足才可进行后续操作
    flag = CheckEntering() && CheckHtlInfo();

    if(flag == true)
    {
        //之后可以扩展的功能单元——手机验证用户注册
        QMessageBox::information(this, "手机验证码", "请注意查收手机验证码", QMessageBox::Ok);

        //新建酒店管理员
        HotelManager newHtlManager(Account, Password,
                                   Phone, Lisence, HotelName);

        //加到全局变量中
        g_HotelManagerlist.push_back(newHtlManager);

        //新建酒店
        Hotel newHotel(HotelName, Address,
                       District, ConsolePhone);

        //加到全局变量中
        g_Hotellist.push_back(newHotel);
        myDatabase Database;
        Database.Memory();
        QMessageBox::information(this, "success!", "注册信息成功提交！等待平台管理员审核", QMessageBox::Ok);
    }

    this->close();
    parent->show();

}

//检查输入是否符合规范
bool hotelregister::CheckEntering()
{
    //检查输入是否符合规则
    bool flag = true;

    //获得局部变量
    Account = ui->lineAccount->text();
    Password = ui->linePassword->text();
    Password2 = ui->linePassword2->text();
    Phone = ui->linePhone->text();
    Lisence = ui->lineLisence->text();
    HotelName = ui->lineHotelName->text();
    ConsolePhone = ui->lineConsolePhone->text();

    //concolephone可以缺省
    if(ConsolePhone.isEmpty())
        ConsolePhone = Phone;


    Address = ui->lineAddress->text();
    District = ui->lineDistrict->text();

    //容错判断
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
    if(Lisence.isEmpty())
    {
        QMessageBox::information(this, "entering Error", "输入营业证号不能为空！",QMessageBox::Ok);
        flag = false;
    }
    if(HotelName.isEmpty())
    {
        QMessageBox::information(this, "entering Error", "输入酒店名称不能为空！",QMessageBox::Ok);
        flag = false;
    }
    if(Address.isEmpty())
    {
        QMessageBox::information(this, "entering Error", "输入城市不能为空！",QMessageBox::Ok);
        flag = false;
    }
    if(District.isEmpty())
    {
        QMessageBox::information(this, "entering Error", "输入地区不能为空！",QMessageBox::Ok);
        flag = false;
    }

    return flag;
}

//在已有的信息中查找是否有信息重复
bool hotelregister::CheckHtlInfo()
{
    bool flag = true;

    qDebug()<<Account;

    //账号名称查重
    for(int i=0;i<g_HotelManagerlist.length();i++)
        if(Account == g_HotelManagerlist[i].GetAccount())
        {
            QMessageBox::information(this, "registered", "该用户已经注册", QMessageBox::Ok);
            flag = false;
        }

    //电话号码查重
    for(int i=0;i<g_HotelManagerlist.length();i++)
    {
        if(g_HotelManagerlist[i].IsPhoneUsed(Phone))
        {
            QMessageBox::information(this, "registered", "该电话已被用户注册", QMessageBox::Ok);
            flag = false;
        }
    }

    //酒店名称查重
    for(int i=0;i<g_Hotellist.length();i++)
    {
        if(g_Hotellist[i].GetHotelName() == HotelName)
        {
            QMessageBox::information(this, "registered", "该酒店名已被注册", QMessageBox::Ok);
            flag = false;
        }
    }

    return flag;

}

