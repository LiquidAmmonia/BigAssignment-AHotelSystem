/**************************************************************************
文件名：hotelmanager.h
功能模块和目的：建立酒店管理员类
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef HOTELMANAGER_H
#define HOTELMANAGER_H

#include "AbstractUser.h"
#include "mydatabase.h"

using namespace std;
//建立酒店管理者。

//AbstractUser为直接父类
class HotelManager:public AbstractUser
{
    //会有一些友元来处理订单


public:
    //构造函数
    HotelManager(QString Account, QString Password,
                 QString Phone, QString lisence, QString hotelname);
    //析构函数
    HotelManager(){}

    //获取酒店管理员创建酒店时所提交的营业执照号
    //之后可拓展：由其它外接数据库判断营业执照号是否有效
    QString GetLisence()
    {
        return Lisence;
    }
    //获取酒店管理者相对应的酒店名称
    QString GetHotelName()
    {
        return HotelName;
    }

private:
    QString Lisence;//经营执照
    QString HotelName;//唯一对应一个酒店的名称

};

#endif // HOTELMANAGER_H
