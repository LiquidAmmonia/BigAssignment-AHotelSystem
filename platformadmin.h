/**************************************************************************
文件名：platformAdmin.h
功能模块和目的：创建平台管理员
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef PLATFORMADMIN_H
#define PLATFORMADMIN_H

#include "abstractuser.h"
#include "QString"
#include "mydatabase.h"
#include <QVector>
/**************************************************************************
类名：PlatformAdmin
功能：创建基础的平台管理员类
接口说明：
开发者：程晔安
日期：
更改记录：
**************************************************************************/
using namespace std;

class PlatformAdmin:public AbstractUser
{

    friend class myDatabase;

public:
    //构造函数
    PlatformAdmin(QString newAccount, QString newPassword,
                  QString Phone);
    PlatformAdmin(){}


};

#endif // PLATFORMADMIN_H
