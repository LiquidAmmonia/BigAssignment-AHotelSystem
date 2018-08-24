
/********************************************************************
文件名：platformadmin.cpp
功能模块和目的：实现platform类的构造函数
开发者：程晔安
日期：
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "platformadmin.h"
#include "QString"

//构造函数
PlatformAdmin::PlatformAdmin(QString newAccount, QString newPassword,
                             QString newPhone):
    AbstractUser(newAccount, newPassword, newPhone)
{

}
