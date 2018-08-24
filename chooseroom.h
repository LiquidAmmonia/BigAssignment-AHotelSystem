/**************************************************************************
文件名：ChooseRoom.h
功能模块和目的：
开发者：程晔安
日期：
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef CHOOSEROOM_H
#define CHOOSEROOM_H

#include <QDialog>

#include "customer.h"
#include "hotel.h"
#include "room.h"

namespace Ui {
class ChooseRoom;
}

class MainWindow;

class ChooseRoom : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseRoom(MainWindow *parent);
    ~ChooseRoom();

    //函数作用：显示房间列表
    void ShowRoom();

public slots:
    //槽作用：做好建立订单之前的准备
    void MakeAnOrder();
    //槽作用：新建订单
    void EnterOrder();
private:
    //私有指针：
    Ui::ChooseRoom *ui ;
    //回到MainWindow
    MainWindow *parent ;
    //建立针对某位用户的房间暂时列表
    QVector<Room*>tempRoomlist ;
    //订单的起始日期和住房时长
    QDate tempDate ;
    int tempDays;
};

#endif // CHOOSEROOM_H
