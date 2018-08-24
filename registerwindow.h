/**************************************************************************
文件名：registerwindow.h
功能模块和目的：创建用户注册界面
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include "loginwindow1.h"

/**************************************************************************
类名：registerwindow
功能：创建用户注册界面
接口说明：有指向loginwindow1的指针
开发者：程晔安
日期：8.1
更改记录：
**************************************************************************/

namespace Ui {
class registerWindow;
}


class loginwindow1;

class registerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit registerWindow(loginwindow1 *l);
    ~registerWindow();

private:
    Ui::registerWindow *ui;

    //回到登陆界面的指针
    loginwindow1 *parent;
    //界面上输入的信息作为私有成员
    QString Account;
    QString Password;
    QString Password2;
    QString Phone;

    //检查输入规范问题
    bool CheckEntering();

    //检查已有的顾客名单的信息是否重复
    bool CheckCusInfo();

public slots:
    //主要的功能函数
    void SendInfo();

};

#endif // REGISTERWINDOW_H
