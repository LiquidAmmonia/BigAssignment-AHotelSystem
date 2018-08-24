/**************************************************************************
文件名：room.h
功能模块和目的：创建基础的房间类
开发者：程晔安
日期：7.28
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/

#ifndef ROOM_H
#define ROOM_H

#include "QString"

/**************************************************************************
类名：Room
功能：作为基础的房间类
接口说明：可以获得房间类的各种属性
开发者：程晔安
日期：7.28
更改记录：
**************************************************************************/


class Room
{

public:

    //构造函数
    Room(){}
    Room(QString newHotelName,
         bool newApproved, int newPrice,
         int newNumber, int newType, float newDiscount,
         QString newImages, QString newDiscription,
         int newStar);
    Room(QString hotelname,
         int Price, int Number, int Type);

    //接口函数
    QString GetHotelName()
    {
        return HotelName;
    }

    bool IsApproved()
    {
        return Approved;
    }
    void SetApproved(bool newApproved)
    {
        Approved = newApproved;
    }


    int GetPrice()
    {
        return Price;
    }
    void SetPrice(int newPrice)
    {
        Price = newPrice;
    }

    int GetNumber()
    {
        return Number;
    }
    void SetNumber(int newNumber)
    {
        Number = newNumber;
    }

    int GetType()
    {
        return Type;
    }
    void SetType(int newType)
    {
        Type = newType;
    }

    void SetDiscount(float newDiscount)
    {
        Discount = newDiscount;
    }
    float GetDiscount()
    {
        return Discount;
    }

    QString GetImages()
    {
        return Images;
    }
    void SetImages(QString newImages)
    {
        Images = newImages;
    }

    QString GetDiscription()
    {
        return Discription;
    }
    void SetDiscription(QString newDiscription)
    {
        Discription = newDiscription;
    }

    int GetStar()
    {
        return Star;
    }
    void SetStar(int newStar)
    {
        int temp = Star;
        Star = (newStar + temp)/2;
    }

    QString GetRoomId()
    {
        return RoomID;
    }

    int GetRealPrice()
    {
        return (int)(Price * Discount);
    }

    int curDays;
private:
    QString HotelName;
    bool Approved;
    int Price;
    int Number;
    //总共有五种类型的房子
    int Type;
    float Discount;
    QString Images;
    QString Discription;
    //打分星级
    int Star;

    QString RoomID;
};

#endif // ROOM_H
