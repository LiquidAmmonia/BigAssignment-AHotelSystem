/**************************************************************************
文件名：hotelregister.h
功能模块和目的：酒店管理员注册图形界面
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef hotelregister_H
#define hotelregister_H

/**************************************************************************
类名：hotelregister
功能：创建图形界面。创建相应的酒店管理员和酒店账号
接口说明：
开发者：程晔安
日期：
更改记录：
**************************************************************************/
#include <QWidget>
#include "loginwindow1.h"

namespace Ui {
class hotelregister;
}
//直接继承由登陆界面
class loginwindow1;

class hotelregister : public QWidget
{
    Q_OBJECT

public:
    explicit hotelregister(loginwindow1 *l );
    ~hotelregister();

private:
    Ui::hotelregister *ui;

    //用于返回到登录界面
    loginwindow1 *parent;

    //局部变量
    QString Account;
    QString Password;
    QString Password2;
    QString Phone;
    QString Lisence;
    QString HotelName;
    QString ConsolePhone;
    QString Address;
    QString District;

    //检查输入是否合理
    bool CheckEntering();
    //检查已有的酒店注册信息，防止重复
    bool CheckHtlInfo();

public slots:
    //保存和处理相关的信息
    void SendInfo();

};

#endif // hotelregister_H
