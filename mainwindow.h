/**************************************************************************
文件名：mainwindow.h
功能模块和目的：创建用户界面
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "QVector"

#include "chooseroom.h"
#include "loginwindow1.h"
#include "customer.h"
#include "hotel.h"
#include "room.h"
#include "order.h"
#include "wcomment.h"

/**************************************************************************
类名：mainwindow
功能：创建用户界面，处理用户输入信息，向用户呈现相关信息。
接口说明：有指向loginwindow,chooseroom,wcomment的指针
开发者：程晔安
日期：8.1
更改记录：
**************************************************************************/

namespace Ui {
class MainWindow;
}

class loginwindow1;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(loginwindow1*parent, Customer*pCustomer);
    ~MainWindow();
    //提供用户界面的相关信息给chooseroom界面，以实现订单的创建。
    int GetType();
    Customer* GetpCustomer();
    Hotel* GetpHotel();
    QDate GetDate();
    int GetDays();
    //将酒店列表打印出来
    void ShowHotel(int SortType);

    //第一个tab编辑页中的输入检测
    bool EnteringCheckP1();
public slots:
    //tab1
    void SearchARoomP1();
    void SaveAndLogout();
    void ShowDetail();
    //tab2
    void ShowOrder();

    void Pay();
    void Refund();
    void Comment();

    //tab3
    //改变密码操作
    void ChangePassword();

private:
    Ui::MainWindow *ui;

    //指向不同界面的指针
    loginwindow1*parent ;

    ChooseRoom* pChooseRoom ;
    WComment* pComment ;

    //代表该用户界面所代表的用户的信息
    Customer* pCustomer ;

    //创建临时酒店指针列表
    QVector<Hotel*>temp_pHotellist;
    //创建临时订单列表
    QVector<Order*>temp_pOrderlist;
};

#endif // MAINWINDOW_H
