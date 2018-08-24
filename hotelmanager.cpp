
/********************************************************************
文件名：hotelmanager.cpp
功能模块和目的：实现hotelmanager类的构造函数
开发者：程晔安
日期：8.2
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "hotelmanager.h"

//hotelmanager类的默认构造函数
//Lisence为营业执照，不再程序中体现作用，但是储存在数据库中，
//用作之后其他查询和审查作用

HotelManager::HotelManager(QString newAccount, QString newPassword,
                           QString newPhone,
                           QString newLisence, QString newHotelname):
    AbstractUser(newAccount, newPassword, newPhone),
    Lisence(newLisence), HotelName(newHotelname)
{

}
