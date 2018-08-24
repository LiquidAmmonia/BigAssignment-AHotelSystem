/*
文件名：whotel.h
功能模块和目的：创建酒店管理员的界面
开发者：程晔安
日期：8.2
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
*/
#ifndef WHOTEL_H
#define WHOTEL_H

#include <QWidget>
#include "QVector"
#include "QtWidgets"

#include "roomchange.h"
#include "loginwindow1.h"
#include "newroom.h"

#include "hotelmanager.h"
#include "hotel.h"
#include "room.h"
#include "order.h"

/**************************************************************************
类名：whotel

功能：创建酒店管理员界面
接口说明：有指向loginwindow，newroom，roomchange的指针
开发者：程晔安
日期：8.2
更改记录：
**************************************************************************/

namespace Ui {
class whotel;
}

class loginwindow1;
class RoomChange;
class NewRoom;

class whotel : public QWidget
{
    Q_OBJECT

public:
    explicit whotel(loginwindow1*parent, Hotel*pHotel);
    ~whotel();

private:
    Ui::whotel *ui;

    //可以返回到登陆界面
    loginwindow1*parent;
    //记录当前酒店的信息
    Hotel*pHotel;
    //通向其他界面
    RoomChange*pRoomChange;
    NewRoom*pNewRoom;

    //记录与此酒店相关的订单列表
    QVector<Order*>temppOrderlist ;
public slots:
    //保存退出
    void SaveAndLogout();

    //显示房间信息
    void ShowRoomInfo();

    //初始化房间信息列表标题
    void InitialRoomHeader();

    //修改房间信息
    void ChangeRoom();

    //更改订单状态：确定入住
    void CheckIn();

    //更改订单状态：确定退房
    void CheckOut();

    //显示订单信息
    void ShowOrderInfo();

    //初始化订单列表标题
    void InitialOrder();

    //创建一个新房间
    void NewARoom();
};

#endif // WHOTEL_H
