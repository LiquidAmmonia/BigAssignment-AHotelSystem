
/********************************************************************
文件名：main.cpp
功能模块和目的：主函数
开发者：程晔安
日期：7.27
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "mainwindow.h"
#include <QApplication>
#include"loginwindow1.h"
#include"mydatabase.h"

#include <QVector>

#include "customer.h"
#include "hotelmanager.h"
#include "hotel.h"
#include "order.h"
#include "platformadmin.h"

#include "QFile"
using namespace std;

//声明全局变量
QVector<Customer>g_Customerlist;
QVector<HotelManager>g_HotelManagerlist;
QVector<Hotel>g_Hotellist;
QVector<Order>g_Orderlist;
QVector<PlatformAdmin>g_PlatformAdminlist;

//所有房间放在一个容器中
QVector<Room>RawRoomlist;

//添加QSS
QString getQssContent()
{
    QFile styleSheet(":/qtStyleSheet.txt");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return "";
    }
    return styleSheet.readAll();
}

//主函数
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    a.setStyleSheet(getQssContent());

    //打开登陆界面
    loginwindow1 w;
    w.show();
    return a.exec();
}
