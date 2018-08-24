
/**************************************************************************
文件名：hotel.h
功能模块和目的：创建基础的酒店列
开发者：程晔安
日期：7/30
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef HOTEL_H
#define HOTEL_H

#include "QString"
#include <QVector>
#include "room.h"

/**************************************************************************
类名：hotel
功能：作为最基础的酒店类，存储酒店信息和所属的房间
接口说明：可以获取酒店相关信息，以及所属的房间的相关信息
开发者：程晔安
日期：7/31
更改记录：
**************************************************************************/
using namespace std;

class Room;

class Hotel
{
public:
    //构造函数
    Hotel(QString hotelname, QString address,
          QString district, QString consolePhone,
          bool Approved);
    Hotel(QString hotelname, QString address,
          QString district,QString consolePhone);
    //析构函数
    Hotel(){}

    //端口函数
    QString GetHotelName()
    {
        return HotelName;
    }

    QString GetAddress()
    {
        return Address;
    }

    QString GetDistrict()
    {
        return District;
    }

    QString GetConsolePhone()
    {
        return ConsolePhone;
    }

    bool IsApproved()
    {
        return Approved;
    }
    void SetApproved(bool newApproved)
    {
        Approved = newApproved;
    }


    void SetRoomlist(QVector<Room>newRoomlist)
    {
        Roomlist = newRoomlist;
    }
    float GetStar();
    int GetMinPrice();

    QVector<Room>Roomlist;
private:
    QString HotelName;
    QString Address;
    QString District;
    //咨询电话，如果不填默认和相关管理员电话相同
    QString ConsolePhone;

    //是否营业执照合格
    bool Approved;




};

#endif // HOTEL_H
