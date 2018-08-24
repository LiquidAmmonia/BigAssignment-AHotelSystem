/**************************************************************************
文件名：order.h
功能模块和目的：创建基础的订单类
开发者：程晔安
日期：8.2
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef ORDER_H
#define ORDER_H

#include "QDate"
#include "customer.h"
#include "room.h"

/**************************************************************************
类名：Order.h
功能：记录订单信息
接口说明：有指向房间和用户的指针
开发者：程晔安
日期：8.2
更改记录：
**************************************************************************/

class Customer;
class Room;

class Order
{
public:
    //两种构造函数，分别应用于实际创建对象和从数据库读取对象两种情况
    Order(QDate newDate, int newDays,
          Room* new_pRoom, Customer* new_pCustomer);
    Order(QDate newDate, int newDays, int newType,
          bool RefundApproved,
          Room* new_pRoom, Customer* new_pCustomer);


    Order(){}

    //获取房间指针
    Room* GetpRoom()
    {
        return pRoom;
    }
    //获取用户指针
    Customer* GetpCustomer()
    {
        return pCustomer;
    }

    //设置订单种类
    bool SetType(int newType)
    {
        if(newType >=0&&newType<6)
            Type = newType;
        else
           return false;
        return true;

    }

    //返回订单开始日期
    QDate GetDate()
    {
        return Date;
    }
    //返回订单订房时间
    int GetDays()
    {
        return Days;
    }
    //返回订单种类
    int GetType()
    {
       return Type;
    }
    //返回订单退款审核是否通过
    bool GetRefundApproved()
    {
        return RefundApproved;
    }
    //设置订单退款审核是否通过
    void SetRefundApproved(bool newApproved)
    {
        RefundApproved = newApproved;
    }


private:
    QDate Date;
    //订购天数
    int Days;
    //订单的状态：已预定、已交款、退款、入住、退房、已评论
    int Type;

    bool RefundApproved;

    Room* pRoom ;
    Customer* pCustomer ;



};

#endif // ORDER_H
