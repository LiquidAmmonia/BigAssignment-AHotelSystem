
/********************************************************************
文件名：myDatabase.cpp
功能模块和目的：完成于数据库的连接
开发者：程晔安
日期：8.2
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "mydatabase.h"
#include "customer.h"
#include "hotel.h"
#include "hotelmanager.h"
#include "room.h"
#include "order.h"
#include "platformadmin.h"

extern QVector<Customer>g_Customerlist;
extern QVector<Hotel>g_Hotellist;
extern QVector<HotelManager>g_HotelManagerlist;
extern QVector<Order>g_Orderlist;
extern QVector<PlatformAdmin>g_PlatformAdminlist;

extern QVector<Room>RawRoomlist;

//在构造时完成connect，创建表
myDatabase::myDatabase()
{
    CreateConnection();
    CreatTables();

}

myDatabase::~myDatabase()
{
}

//创建数据库连接
bool myDatabase::CreateConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "connection");

    db.setDatabaseName("HotelManagement.db");
    if(!db.open())
    {
        QMessageBox msg;
        msg.setText("无法打开数据库");
        msg.setWindowTitle("Error");
        msg.exec();
        return false;
    }
    return true;
}

//创建表头
bool myDatabase::CreatTables()
{
    QSqlQuery query(db);

    //创建用户列表
    query.prepare("create table IF NOT EXISTS Customer"
                  "(Account VARCHAR, Password VARCHAR, Phone VARCHAR, Totalamount INT)");
    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Customer!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}


    //创建酒店管理员列表
    query.prepare("create table IF NOT EXISTS HotelManager"
                  "(Account VARCHAR, Password VARCHAR, Phone VARCHAR, "
                  "Lisence VARCHAR, Hotelname VARCHAR)");
    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Hotelmanager!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}


    //创建酒店列表
    query.prepare("create table IF NOT EXISTS Hotel"
                  "(Hotelname VARCHAR, Address VARCHAR, "
                  "District VARCHAR, "
                  "Consolephone VARCHAR, Approved BOOLEAN)");

    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Hotel!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}

    //创建酒店房间大列表
    query.prepare("create table IF NOT EXISTS Room"
                  "(Hotelname VARCHAR, Approved BOOLEAN, "
                  "Price INT, Number INT, "
                  "Type INT, Discount FLOAT, "
                  "Images VARCHAR, Discription VARCHAR, "
                  "Star INT)");

    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Room!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}

    //创建订单列表
    //Order为关键字，所以用Orderer作为表名
    query.prepare("create table IF NOT EXISTS Orderer"
                  "(Date VARCHAR, Days INT, Types INT, "
                  "RefundApproved BOOLEAN, CustomerName VARCHAR, "
                  "RoomId VARCHAR)");
    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Order!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}

    //创建平台管理员列表
    query.prepare("create table IF NOT EXISTS PlatformAdmin"
                  "(Account VARCHAR, Password VARCHAR, "
                  "Phone VARCHAR)");
    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table PlatformAdmin!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}

return true;

}

//对各个列表进行初始化，即将其存储在全局变量之中

//初始化顾客列表
bool myDatabase::InitialCustomer()
{
    QSqlQuery query(db);
    query.exec("select * from Customer");

    //依次取出数据，初始化全局变量
    while(query.next())
    {
        QString Account = query.value(0).toString();
        QString Password = query.value(1).toString();
        QString Phone = query.value(2).toString();
        int TotalNum = query.value(3).toInt();

        Customer c(Account, Password, Phone, TotalNum);
        g_Customerlist.append(c);
    }
    return true;
}

//初始化房间列表
bool myDatabase::InitialRoom()
{
    QSqlQuery query(db);
    query.exec("select * from Room");

    while(query.next())
    {
        QString newHotelName = query.value(0).toString();
        bool newApproved = query.value(1).toBool();
        int newPrice = query.value(2).toInt();
        int newNumber = query.value(3).toInt();
        int newType = query.value(4).toInt();
        float newDiscount = query.value(5).toFloat();
        QString newImages = query.value(6).toString();
        QString newDiscription = query.value(7).toString();
        int newStar = query.value(8).toInt();

        //依次取出信息放在RawRoomlist中，作为初始的房间大名单
        Room newRoom(newHotelName, newApproved, newPrice, newNumber,
                     newType, newDiscount, newImages, newDiscription,
                     newStar);
        RawRoomlist.append(newRoom);

    }
    return true;
}

//初始化酒店管理员列表
bool myDatabase::InitialHotelmanager()
{
    QSqlQuery query(db);
    query.exec("select * from Hotelmanager");

    while(query.next())
    {
        QString Account = query.value(0).toString();
        QString Password = query.value(1).toString();
        QString Phone = query.value(2).toString();
        QString Lisence = query.value(3).toString();
        QString Hotelname = query.value(4).toString();

        HotelManager h(Account, Password, Phone, Lisence, Hotelname);


        g_HotelManagerlist.append(h);
    }
    return true;
}

//在初始化Hotel类的同时，其实同时将Room的信息写入。
bool myDatabase::InitialHotelAndRoom()
{
    QSqlQuery query(db);
    query.exec("select * from Hotel");

    while(query.next())
    {
        QString Hotelname = query.value(0).toString();
        QString Address = query.value(1).toString();
        QString District = query.value(2).toString();
        QString Consolephone = query.value(3).toString();
        bool Approved = query.value(4).toBool();




        Hotel h(Hotelname, Address, District,
                Consolephone, Approved);

        QVector<Room>tempRoomlist;

        //根据房间信息，将酒店房间的列表中的酒店放入酒店的私有成员中
        for(int i=0;i<RawRoomlist.length();i++)
        {
            if(RawRoomlist[i].GetHotelName() == Hotelname)
            {
                tempRoomlist.append(RawRoomlist[i]);
            }
        }
        h.SetRoomlist(tempRoomlist);

        g_Hotellist.append(h);
    }


    return true;
}

//初始化订单列表
bool myDatabase::InitialOrder()
{
    QSqlQuery query(db);
    query.exec("select * from Orderer");

    while(query.next())
    {
        QString newDatestr = query.value(0).toString();
        int newDays = query.value(1).toInt();
        int newTypes = query.value(2).toInt();
        bool newRefundApproved = query.value(3).toBool();
        QString newCustomerName = query.value(4).toString();
        QString newRoomID = query.value(5).toString();

        QDate newDate = QDate::fromString(newDatestr,"dd.MM.yyyy");

        Customer* new_pCustomer = NULL;
        Room* new_pRoom = NULL;

        //寻找相应信息的顾客指针
        for(int i=0;i<g_Customerlist.length();i++)
        {
            if(g_Customerlist[i].GetAccount() == newCustomerName)
            {
                new_pCustomer = &g_Customerlist[i];
            }
        }


        //寻找相应的房间指针
        for(int i=0;i<RawRoomlist.length();i++)
        {

            if(RawRoomlist[i].GetRoomId() == newRoomID)
            {

                new_pRoom = &RawRoomlist[i];
            }
        }


        Order newOrder(newDate, newDays, newTypes,
                       newRefundApproved, new_pRoom,
                       new_pCustomer);


        //加入全局变量中
        g_Orderlist.append(newOrder);

        qDebug()<<g_Orderlist[0].GetpRoom()->GetDiscription();

    }
    return true;
}

//初始化平台管理员的全局变量
bool myDatabase::InitialPlatformAdmin()
{
    QSqlQuery query(db);
    query.exec("select * from PlatformAdmin");

    while(query.next())
    {
        QString Account = query.value(0).toString();
        QString Password = query.value(1).toString();
        QString Phone = query.value(2).toString();


        //添加到全局变量中
        PlatformAdmin c(Account, Password, Phone);
        g_PlatformAdminlist.append(c);
    }
    return true;
}

//将全局变量中的信息存回数据库中
bool myDatabase::Memory()
{
    QSqlQuery query(db);

    //更新顾客列表
    query.exec("DELETE from Customer");

    query.prepare("insert into Customer VALUES(?,?,?,?)");

    for(int i=0;i<g_Customerlist.size();i++)
      {
        query.bindValue(0,g_Customerlist[i].GetAccount());
        query.bindValue(1,g_Customerlist[i].GetPassword());

        query.bindValue(2,g_Customerlist[i].GetPhone());
        query.bindValue(3,g_Customerlist[i].GetTotalCost());
        bool success = query.exec();
        if(!success)
        {

            QMessageBox msg;
        msg.setText(QStringLiteral("更新顾客表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();}}

    //更新酒店列表
    query.exec("DELETE from Hotel");
    query.prepare("insert into Hotel values(?,?,?,?,?)");
    for(int i=0;i<g_Hotellist.size();i++)
      { query.bindValue(0,g_Hotellist[i].GetHotelName());
        query.bindValue(1,g_Hotellist[i].GetAddress());
        query.bindValue(2,g_Hotellist[i].GetDistrict());
        query.bindValue(3,g_Hotellist[i].GetConsolePhone());
        query.bindValue(4,g_Hotellist[i].IsApproved());
        bool success=query.exec();
        if(!success)
        {QMessageBox msg;
        msg.setText(QStringLiteral("更新酒店列表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();}}


    //更新酒店管理员列表
    query.exec("DELETE from Hotelmanager");
    query.prepare("insert into Hotelmanager values(?,?,?,?,?)");
    for(int i=0;i<g_HotelManagerlist.size();i++)
      { query.bindValue(0,g_HotelManagerlist[i].GetAccount());
        query.bindValue(1,g_HotelManagerlist[i].GetPassword());
        query.bindValue(2,g_HotelManagerlist[i].GetPhone());
        query.bindValue(3,g_HotelManagerlist[i].GetLisence());
        query.bindValue(4,g_HotelManagerlist[i].GetHotelName());

        bool success=query.exec();
        if(!success)
        {

            QMessageBox msg;
        msg.setText(QStringLiteral("更新酒店管理员列表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();
        }
    }

    //更新房间列表

    //先更新酒店房间大列表
    RawRoomlist.clear();
    for(int i=0;i<g_Hotellist.length();i++)
    {
        for(int j=0;j<g_Hotellist[i].Roomlist.length();j++)
        {
            RawRoomlist.append(g_Hotellist[i].Roomlist[j]);
        }
    }


    query.exec("DELETE from Room");
    query.prepare("insert into Room values(?,?,?,?,?,?,?,?,?)");
    for(int i=0;i<RawRoomlist.size();i++)
    {

        qDebug()<<RawRoomlist[i].GetImages();

        query.bindValue(0,RawRoomlist[i].GetHotelName());
        query.bindValue(1,RawRoomlist[i].IsApproved());
        query.bindValue(2,RawRoomlist[i].GetPrice());
        query.bindValue(3,RawRoomlist[i].GetNumber());
        query.bindValue(4,RawRoomlist[i].GetType());
        query.bindValue(5,RawRoomlist[i].GetDiscount());
        query.bindValue(6,RawRoomlist[i].GetImages());
        query.bindValue(7,RawRoomlist[i].GetDiscription());
        query.bindValue(8,RawRoomlist[i].GetStar());

        bool success=query.exec();

        if(!success)
        {
            QMessageBox msg;
        msg.setText(QStringLiteral("更新酒店房间列表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();
        }
    }

    //更新订单列表
    query.exec("DELETE from Orderer");
    query.prepare("insert into Orderer values(?,?,?,?,?,?)");
    for(int i=0;i<g_Orderlist.size();i++)
    {

        query.bindValue(0,g_Orderlist[i].GetDate().toString("dd.MM.yyyy"));
        query.bindValue(1,g_Orderlist[i].GetDays());
        query.bindValue(2,g_Orderlist[i].GetType());
        query.bindValue(3,g_Orderlist[i].GetRefundApproved());

        query.bindValue(4,g_Orderlist[i].GetpCustomer()->GetAccount());
        query.bindValue(5,g_Orderlist[i].GetpRoom()->GetRoomId());

        bool success=query.exec();
        if(!success)
        {
            QMessageBox msg;
        msg.setText(QStringLiteral("更新订单列表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();
        }
    }

    //更新平台管理员列表
    query.exec("DELETE from PlatformAdmin");

    query.prepare("insert into PlatformAdmin VALUES(?,?,?)");

    for(int i=0;i<g_PlatformAdminlist.size();i++)
      {
        query.bindValue(0,g_PlatformAdminlist[i].GetAccount());
        query.bindValue(1,g_PlatformAdminlist[i].GetPassword());

        query.bindValue(2,g_PlatformAdminlist[i].GetPhone());

        bool success = query.exec();
        if(!success)
        {

            QMessageBox msg;
        msg.setText(QStringLiteral("更新平台管理员列表失败!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();}}


    return true;
}

