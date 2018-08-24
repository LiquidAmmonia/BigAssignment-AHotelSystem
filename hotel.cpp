/********************************************************************
文件名：hotel.cpp
功能模块和目的：
开发者：程晔安
日期：8.2
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "hotel.h"
#include <QVector>
#include "room.h"

//用于程序中创建酒店类的构造函数
Hotel::Hotel(QString newhotelname, QString newaddress,
             QString newdistrict, QString newconsolePhone):
    HotelName(newhotelname), Address(newaddress),
    District(newdistrict), ConsolePhone(newconsolePhone)
{
    Approved = false;

}

//用于从数据库中读取时的构造函数
Hotel::Hotel(QString newhotelname, QString newaddress,
             QString newdistrict, QString newconsolePhone,
             bool newApproved):
    HotelName(newhotelname), Address(newaddress),
    District(newdistrict), ConsolePhone(newconsolePhone),
    Approved(newApproved)
{


}
//建立两个函数而不直接使用默认值的原因是防止部分默认值被初始化。

//获取用户评价星级
float Hotel::GetStar()
{
    float star = 0;
    for(int i=0;i<this->Roomlist.size();i++)
    {
        star += this->Roomlist[i].GetStar();
    }
    return (star/this->Roomlist.size());
}

//获取本酒店中最低价格房间，以在房间列表显示
int Hotel::GetMinPrice()
{
    int min = this->Roomlist[0].GetRealPrice() ;
    //遍历搜索
    for(int i=0;i<this->Roomlist.size();i++)
    {
        if(min > this->Roomlist[i].GetRealPrice())
            min =  this->Roomlist[i].GetRealPrice();
    }
    return min;
}
