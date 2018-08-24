/**************************************************************************
文件名：roomchange.h
功能模块和目的：更改房间信息
开发者：程晔安
日期：7.28
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/
#ifndef ROOMCHANGE_H
#define ROOMCHANGE_H

#include <QWidget>

#include "QVector"
#include "room.h"
#include "whotel.h"

#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QGuiApplication>


/**************************************************************************
类名：Roomchange
功能：创建更改房间信息的相关操作和界面
接口说明：有指向whotel的指针
开发者：程晔安
日期：7.28
更改记录：
**************************************************************************/

namespace Ui {
class RoomChange;
}

class whotel;

class RoomChange : public QWidget
{
    Q_OBJECT

public:
    explicit RoomChange(whotel*parent, Room*pRoom);
    ~RoomChange();

private:
    Ui::RoomChange *ui;

    //指向whotel以及记录信息
    whotel*parent;
    Room*pRoom;

    //储存图片用
    QString runPath;
    QString hglpName;
    QString hglpPath;

public slots:
    //保存信息
    void Save();
    //打开图片
    void OpenImag();
    //保存图片到相关路径
    void SaveImag();
    //取消操作
    void Cancel();
    //显示旧的房间信息
    void ShowOldInfo();
};

#endif // ROOMCHANGE_H
