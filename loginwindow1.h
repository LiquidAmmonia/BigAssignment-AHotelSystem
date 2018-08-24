/**************************************************************************
文件名：loginwindow1.h
功能模块和目的：创捷登录图形界面。
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef loginwindow1_H
#define loginwindow1_H

#include <QWidget>
#include "registerwindow.h"
#include "hotelregister.h"
#include "mainwindow.h"
#include "whotel.h"
#include "platform.h"

/**************************************************************************
类名：loginwindow
功能：最开始的界面。连结两个注册界面和三个主要用户对象界面
接口说明：有指向hotelregister,mainwindow,platform,registerwindow,whotel的指针。
开发者：程晔安
日期：8.1
更改记录：
**************************************************************************/

namespace Ui {
class loginwindow1;
}

class registerWindow;
class hotelregister;
class MainWindow;
class whotel;
class Platform;

class loginwindow1 : public QWidget
{
    Q_OBJECT

public:
    explicit loginwindow1(QWidget *parent = 0);
    ~loginwindow1();
    void ClearPassword();

private:
    Ui::loginwindow1 *ui;

    //注册窗口
    registerWindow*pRegister ;
    hotelregister*pHtl ;

    //登录窗口，一共三个
    MainWindow*pMainwindow ;
    whotel *pWHotel ;
    Platform *pPlatform ;

public slots:
    void Login();
    void RegisterChoose();

signals:

};

#endif // loginwindow1_H
