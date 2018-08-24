/**************************************************************************
文件名：abstractuser.h
功能模块和目的：建立AbstractUser类
开发者:程晔安
日期：2018/7/28
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：7/28最后修改
**************************************************************************/

#ifndef AbstractUser_H
#define AbstractUser_H

#include"QString"

/*************************************************************************
类名：AbstractUser.h
功能：作为用户基类
接口说明：外部可获取账号、密码、手机等信息；
        可判断密码是否正确，手机是否已经用于注册；
        可更改密码。
开发者：程晔安
日期：7/28
更改记录：7/28最后修改
**************************************************************************/

class AbstractUser
{

public:
    //构造函数
    AbstractUser(QString newAccount, QString newPassword,
                 QString newPhone);
    //默认构造函数
    AbstractUser()
    {

    }
    //析构函数
    ~AbstractUser(){}

    //获取账号、密码、手机号
    QString GetAccount()
    {
        return Account;
    }
    QString GetPassword()
    {
        return Password;
    }
    QString GetPhone()
    {
        return Phone;
    }

    //判断密码是否正确
    bool IsCorrect(QString aPassword);
    //设置密码
    void SetPassword(QString aPassword)
    {
        Password = aPassword;
    }

    //检查手机号是否已经注册，手机号对外不可见
    bool IsPhoneUsed(QString newPhone)
    {
        if(Phone == newPhone)
            return true;
        return false;
    }

protected:
    //私有成员：账号、密码、手机
    QString Account;
    QString Password;
    QString Phone;



};

#endif // AbstractUser_H
