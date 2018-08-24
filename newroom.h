/**************************************************************************
文件名：newroom.h
功能模块和目的：新建房间
开发者：程晔安
日期：7.29
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef NEWROOM_H
#define NEWROOM_H

#include <QWidget>

#include "QVector"
#include "room.h"
#include "hotel.h"
#include "whotel.h"
#include "room.h"

#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QGuiApplication>

/**************************************************************************
类名：NewRoom
功能：新建房间
接口说明：有指向酒店界面的指针
开发者：程晔安
日期：7.29
更改记录：
**************************************************************************/

namespace Ui {
class NewRoom;
}

class whotel;

class NewRoom : public QWidget
{
    Q_OBJECT

public:
    explicit NewRoom(whotel*parent, Hotel*pHotel);
    ~NewRoom();
    bool CheckEntering();
private:
    Ui::NewRoom *ui;

    //指向酒店界面的指针
    whotel*parent;

    //记录相关信息
    Hotel*pHotel;
    Room*pRoom;

    //记录图片存储的方法
    QString runPath;
    QString hglpName;
    QString hglpPath;


public slots:

    //保存相关信息
    void Save();
    //打开图片
    void OpenImag();
    //保存图片到相关路径下
    void SaveImag();
    //取消，返回酒店界面
    void Cancel();



};

#endif // NEWROOM_H
