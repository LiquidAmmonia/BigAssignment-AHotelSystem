
/********************************************************************
文件名：room.cpp
功能模块和目的：实现Room类的构造函数
开发者：程晔安
日期：7.29
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "room.h"


//从数据库读入时的构造函数
Room::Room(QString newHotelName,
           bool newApproved, int newPrice,
           int newNumber, int newType, float newDiscount,
           QString newImages, QString newDiscription,
           int newStar):
    HotelName(newHotelName),Approved(newApproved),
    Price(newPrice), Number(newNumber), Type(newType),
    Discount(newDiscount), Images(newImages),
    Discription(newDiscription),
    Star(newStar)
{
    //用作房间的唯一标志
    RoomID = HotelName + QString::number(Type);
    curDays = Number;


}

//新建房间对象时的构造函数
Room::Room(QString newHotelName, int newPrice,
           int newNumber, int newType)
{
    HotelName = newHotelName;
    Approved = false;
    Price = newPrice;
    Number = newNumber;
    Type = newType;
    Discount = 1.0;
    Images = ":/standard.jpg";
    Discription = "商家很懒，什么也没留下。";
    //0代表尚未有评论
    Star = 0;
    RoomID = HotelName + QString::number(Type);
    curDays = Number;
}

