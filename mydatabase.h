/**************************************************************************
文件名：mydatabase.h
功能模块和目的：实现与数据库的链接
开发者：程晔安
日期：8.2
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QObject>

#include<Qtsql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDriver>
#include<QtSql/QSqlError>
#include<QtSql/QSqlRecord>
#include<QtSql/QSqlTableModel>
#include<QtDebug>
#include<QtSql/QSqlField>
#include<QMessageBox>
#include<QVector>
#include"room.h"

/**************************************************************************
类名：mydatabase
功能：实现与数据库的连接，将数据库中的数据传入内存中

接口说明：与数据库的链接以及以全局变量形式与主要程序连接
开发者：程晔安
日期：8.2
更改记录：
**************************************************************************/
class myDatabase:public QObject
{
    Q_OBJECT

public:
    //默认构造函数，其中搭建与数据库的链接以及初始化列表
    myDatabase();
    ~myDatabase();
    QSqlDatabase db;

    //建立酒店房间大名单，用于初始化酒店列表
    //QVector<Room>RawRoomlist;


    //进行相关初始化，将数据放在全局变量里面
    bool InitialCustomer();
    bool InitialHotelmanager();
    bool InitialHotelAndRoom();
    bool InitialRoom();
    bool InitialOrder();
    bool InitialPlatformAdmin();

private:
    //建立链接
    bool CreateConnection();
    //初始化数据库中的列表
    bool CreatTables();

//将数据重新从内存存入数据库
public slots:
    bool Memory();

};

#endif // MYDATABASE_H




//没解决的问题：怎么新加入房间
