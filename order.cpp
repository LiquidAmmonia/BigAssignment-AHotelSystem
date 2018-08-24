
/********************************************************************
文件名：order.cpp
功能模块和目的：实现Order类的构造函数
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "order.h"

//用于程序中创建时
Order::Order(QDate newDate, int newDays,
             Room* new_pRoom, Customer* new_pCustomer):
    Date(newDate),Days(newDays),
    pRoom(new_pRoom),pCustomer(new_pCustomer)
{
    RefundApproved = false;
    Type = 0;
}

//用于将数据库的信息放入内存中时
Order::Order(QDate newDate, int newDays, int newType,
             bool newRefundApproved,
             Room* new_pRoom, Customer* new_pCustomer):
    Date(newDate),Days(newDays),Type(newType),
    RefundApproved(newRefundApproved),
    pRoom(new_pRoom),pCustomer(new_pCustomer)
{

}
