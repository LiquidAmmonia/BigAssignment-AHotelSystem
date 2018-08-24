/**************************************************************************
文件名：platform.h
功能模块和目的：创建平台管理人员界面
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef PLATFORM_H
#define PLATFORM_H

#include <QWidget>
#include "QVector"
#include "QtWidgets"
#include "loginwindow1.h"

#include "hotel.h"
#include "room.h"
#include "order.h"

/**************************************************************************
类名：platform
功能：创建平台管理人员界面
接口说明：有指向newroom的指针
开发者：程晔安
日期：8.1
更改记录：
**************************************************************************/

namespace Ui {
class Platform;
}

class loginwindow1;

class Platform : public QWidget
{
    Q_OBJECT

public:
    explicit Platform(loginwindow1*parent);
    ~Platform();

private:
    //传回登陆界面的指针
    Ui::Platform *ui;

    loginwindow1*parent;
public slots:
    //刷新列表
    void Refresh1();
    void Refresh2();
    void Refresh3();
    void Refresh4();

    //显示列表
    void ShowHotel();
    void ShowRoom();
    void ShowOrder();
    void ShowCustomer();

    //审核通过列表
    void ApproveHotel();
    void ApproveRoom();
    void ApproveOrder();

    //保存并退出列表
    void SaveAndLogout();

    void STop();

    void DisAble();

};

#endif // PLATFORM_H
