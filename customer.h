/**************************************************************************
文件名：customer.h
功能模块和目的：创建Customer类
开发者：程晔安
日期：7/27
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：最后更改 7/28
**************************************************************************/


#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "AbstractUser.h"
#include "QString.h"
#include "mydatabase.h"
#include <QVector>
#include "order.h"

using namespace std;

/**************************************************************************
类名：Customer.h
功能：平台用户的信息存储和功能操作
接口说明：
开发者：程晔安
日期：7/28
更改记录：
**************************************************************************/

class Customer:public AbstractUser
{

    friend class myDatabase;


public:
    Customer(QString newAccount, QString newPassword,
             QString Phone, int newTotalCost );
    Customer(QString newAccount, QString newPassword, QString Phone );
    Customer(){}

    //建立每个人的购物车总价，以便多个订单同时缴费
    int GetTotalCost()
    {
        return totalCost;
    }
    void SetTotalCost(int newTotalCost)
    {
        totalCost = newTotalCost;
    }



private:
    //存在数据库中
    int totalCost;
};

#endif // CUSTOMER_H
