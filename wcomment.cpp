

/********************************************************************
文件名：wcomment.cpp
功能模块和目的：实现添加评分
开发者：程晔安
日期：8.2
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "wcomment.h"
#include "ui_wcomment.h"

#include "qmessagebox.h"
#include "mydatabase.h"

#include "mainwindow.h"
#include "order.h"
#include "hotel.h"
#include "room.h"

extern QVector<Room>RawRoomlist;


WComment::WComment(MainWindow *newparent, Order* newpOrder) :
    parent(newparent),pOrder(newpOrder),
    ui(new Ui::WComment)
{
    ui->setupUi(this);

    connect(ui->btnOk, SIGNAL(clicked(bool)), this, SLOT(Comment()));

    connect(ui->btnCancel, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked(bool)),
            parent, SLOT(show()));
}

WComment::~WComment()
{
    delete ui;
}

void WComment::Comment()
{
    //获取评分等级
    int Star;
    if(ui->radioButton->isChecked())
        Star = 1;
    else if(ui->radioButton_2->isChecked())
        Star = 2;
    else if(ui->radioButton_3->isChecked())
        Star = 3;
    else if(ui->radioButton_4->isChecked())
        Star = 4;
    else
        Star = 5;

    //将评分等级放入相应的房间中
    for(int i=0;i<RawRoomlist.size();i++)
    {
        if(pOrder->GetpRoom()->GetRoomId() == RawRoomlist[i].GetRoomId())
        {
            pOrder->GetpRoom()->SetStar(Star);
        }
    }

    QMessageBox::information(this, "ERROR",
                             "评价成功，欢迎您下次光临！", QMessageBox::Ok);

    //返回主窗口
    pOrder->SetType(5);
    this->close();
    parent->show();

}
