
/********************************************************************
文件名：whotel.cpp
功能模块和目的：实现酒店平台
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "whotel.h"
#include "ui_whotel.h"

#include "QMessageBox"
#include "qtablewidget.h"
#include "QDate"
#include "mydatabase.h"
#include "QVector"

#include "order.h"
#include "hotel.h"
#include "room.h"

#include "enums.h"

using namespace std ;

extern QVector<HotelManager>g_HotelManagerlist;
extern QVector<Hotel>g_Hotellist;
extern QVector<Order>g_Orderlist;

extern QVector<Room>RawRoomlist;

whotel::whotel(loginwindow1 *newParent,
               Hotel* new_pHotel) :
    parent(newParent), pHotel(new_pHotel),
    ui(new Ui::whotel)
{
    ui->setupUi(this);

    //装饰
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("APlaceToStay__Hotel");

    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table2->setSelectionMode(QAbstractItemView::SingleSelection);
    //初始显示
    ShowRoomInfo();
    ShowOrderInfo();
    //接口

    //保存并推出
    connect(ui->btnExit, SIGNAL(clicked(bool)), this, SLOT(SaveAndLogout()));

    //显示所属房间信息
    connect(ui->btnRefresh, SIGNAL(clicked(bool)), this, SLOT(ShowRoomInfo()));

    //更改房间信息
    connect(ui->btnChange, SIGNAL(clicked(bool)), this, SLOT(ChangeRoom()));

    //更改订单状态：入住
    connect(ui->btnCheckIn, SIGNAL(clicked(bool)), this, SLOT(CheckIn()));

    //更改订单状态：确认退房
    connect(ui->btnCheckOut, SIGNAL(clicked(bool)), this, SLOT(CheckOut()));

    //刷新
    connect(ui->btnRefresh_2, SIGNAL(clicked(bool)), this, SLOT(ShowOrderInfo()));

    //新建房间
    connect(ui->btnNew, SIGNAL(clicked(bool)), this, SLOT(NewARoom()));
}

whotel::~whotel()
{
    delete ui;
}

//保存并退出
void whotel::SaveAndLogout()
{
    //链接数据库
    myDatabase Database;
    Database.Memory();
    //返回登录窗口
    this->close();
    parent->show();
    //密码清空
    parent->ClearPassword();
    return ;
}

//显示房间信息
void whotel::ShowRoomInfo()
{

    //初始化表头
    InitialRoomHeader();

    //开始显示
    QVector<Room> tempRoomlist = pHotel->Roomlist;
    for(int i=0;i<tempRoomlist.size();i++)
    {
        ui->table->setRowCount(i+1);
        //类型转换
        QString temp_enter;
        if(tempRoomlist[i].IsApproved())
            temp_enter = "已过审";
        else
            temp_enter = "未过审";

        //显示价格和数量
        ui->table->setItem(i, 0,
                           new QTableWidgetItem(temp_enter));
        ui->table->setItem(i, 1,
                           new QTableWidgetItem(
                               QString::number(tempRoomlist[i].GetPrice())));
        ui->table->setItem(i, 2,
                           new QTableWidgetItem(
                               QString::number(tempRoomlist[i].GetNumber())));
        //房间种类
        //转换类型
        QString str_type[5] = {"钟点房", "大床房", "双人房", "奢华房", "总统套房"};

        ui->table->setItem(i, 3,
                           new QTableWidgetItem(
                               str_type[tempRoomlist[i].GetType()]));
        //折扣
        ui->table->setItem(i, 4,
                           new QTableWidgetItem(
                               QString::number(tempRoomlist[i].GetDiscount(), 'f', 2)));
        //图片
        QLabel *label = new QLabel("");

        qDebug()<<tempRoomlist[i].GetImages();
        label->setPixmap(QPixmap(tempRoomlist[i].GetImages()).scaled(125,150));

        ui->table->setCellWidget(i, 5, label);
        //商家描述
        ui->table->setItem(i, 6,
                           new QTableWidgetItem(
                               tempRoomlist[i].GetDiscription()));
    }



}

//创建基础房间表头
void whotel::InitialRoomHeader()
{
    ui->table->clear();
    ui->table->setColumnCount(7);
    ui->table->setHorizontalHeaderItem(0, new QTableWidgetItem
                                       (QStringLiteral("是否通过审核")));
    ui->table->setHorizontalHeaderItem(1, new QTableWidgetItem
                                       (QStringLiteral("价格")));
    ui->table->setHorizontalHeaderItem(2, new QTableWidgetItem
                                       (QStringLiteral("数量")));
    //房间种类不可更改
    ui->table->setHorizontalHeaderItem(3, new QTableWidgetItem
                                       (QStringLiteral("房间种类")));
    ui->table->setHorizontalHeaderItem(4, new QTableWidgetItem
                                       (QStringLiteral("折扣")));
    ui->table->setHorizontalHeaderItem(5, new QTableWidgetItem
                                       (QStringLiteral("图片")));
    ui->table->setHorizontalHeaderItem(6, new QTableWidgetItem
                                       (QStringLiteral("商家描述")));

}

//改变房间信息
void whotel::ChangeRoom()
{
    int row = ui->table->currentRow();

    //判断是否选中房间
    if(row == -1)
    {
        QMessageBox::information(this, "ERROR", "未选中房间！", QMessageBox::Ok);
        return ;
    }
    //传入对应房间指针，进入RoomChange界面
    Room* pRoom = &pHotel->Roomlist[row];
    pRoomChange = new RoomChange(this, pRoom);
    pRoomChange->show();
}

//初始化订单表头
void whotel::InitialOrder()
{
    ui->table2->clear();
    ui->table2->setColumnCount(5);
    ui->table2->setHorizontalHeaderItem(0, new QTableWidgetItem
                                        (QStringLiteral("卖家账号")));
    ui->table2->setHorizontalHeaderItem(1, new QTableWidgetItem
                                        (QStringLiteral("卖家电话")));
    ui->table2->setHorizontalHeaderItem(2, new QTableWidgetItem
                                        (QStringLiteral("订购房型")));
    ui->table2->setHorizontalHeaderItem(3, new QTableWidgetItem
                                        (QStringLiteral("订单状态")));
    ui->table2->setHorizontalHeaderItem(4, new QTableWidgetItem
                                        (QStringLiteral("预计入住时间")));
    ui->table2->setHorizontalHeaderItem(0, new QTableWidgetItem
                                        (QStringLiteral("住房时间")));
}

//显示订单表
void whotel::ShowOrderInfo()
{
    InitialOrder();
    temppOrderlist.clear();
    //开始显示

    //选择酒店对应的订单并放入暂时的订单列表中
    for(int i=0;i< g_Orderlist.size();i++)
    {
        if(g_Orderlist[i].GetpRoom()->GetHotelName() ==
                pHotel->GetHotelName())
        {
            temppOrderlist.push_back(&g_Orderlist[i]);
        }
    }

    //显示
    for(int i=0;i< temppOrderlist.size();i++)
    {
        ui->table2->setRowCount(i+1);

        //显示用户账号和手机号
        ui->table2->setItem(i, 0,
                            new QTableWidgetItem(
                                temppOrderlist[i]->GetpCustomer()->GetAccount()));
        ui->table2->setItem(i, 1,
                            new QTableWidgetItem(
                                temppOrderlist[i]->GetpCustomer()->GetPhone()));
        //转换类型
        QString str_RoomType[5] = {"钟点房", "大床房", "双人房", "奢华房", "总统套房"};

        //显示房间型号
        ui->table2->setItem(i, 2,
                            new QTableWidgetItem(
                                str_RoomType[temppOrderlist[i]->GetpRoom()->GetType()]));
        //转换类型
        //显示订单状态
        QString str_OrderType[6] = {"已预订", "已交款", "退款", "已入住", "已退房", "已评论"};
        ui->table2->setItem(i, 3,
                            new QTableWidgetItem(
                                str_OrderType[temppOrderlist[i]->GetType()]));
        //显示订单的起始日期
        ui->table2->setItem(i, 4,
                            new QTableWidgetItem(
                                temppOrderlist[i]->GetDate().toString("dd.MM.yyyy")));
        //先对应天数
        ui->table2->setItem(i, 5,
                            new QTableWidgetItem(
                                QString::number(temppOrderlist[i]->GetDays())));

    }

}

//更改订单状态：确认入住
void whotel::CheckIn()
{
   int row = ui->table2->currentRow();

   //判断是否选中订单
   if(row == -1)
   {
       QMessageBox::information(this, "ERROR", "未选中订单！", QMessageBox::Ok);
       return ;
   }

   //判断订单的状态是否为已缴费
   if(temppOrderlist[row]->GetType() == 1)
   {
       for(int i=0;i<g_Orderlist.size();i++)
       {
           //在订单列表中选中对应订单
           if((g_Orderlist[i].GetpRoom()->GetRoomId() ==
               temppOrderlist[row]->GetpRoom()->GetRoomId())&&
                   (g_Orderlist[i].GetpCustomer()->GetAccount() ==
                    temppOrderlist[row]->GetpCustomer()->GetAccount()))
           {
               g_Orderlist[i].SetType(3);
               QMessageBox::information(this, "SUCCESS", "更改成功",
                                        QMessageBox::Ok);
           }
       }
   }
   else
   {
       QMessageBox::information(this, "FAILED", "订单状态有误！",
                                QMessageBox::Ok);

   }
}

//更改订单状态：确定退房
void whotel::CheckOut()
{
    int row = ui->table2->currentRow();
    //判断是否选中了订单
    if(row == -1)
    {
        QMessageBox::information(this, "ERROR", "未选中订单！", QMessageBox::Ok);
        return ;
    }

    //判断选中订单状态
    if(temppOrderlist[row]->GetType() == 3)
    {
        for(int i=0;i<g_Orderlist.size();i++)
        {
            //从订单列表中选出相应的订单
            if((g_Orderlist[i].GetpRoom()->GetRoomId() ==
                temppOrderlist[row]->GetpRoom()->GetRoomId())&&
                    (g_Orderlist[i].GetpCustomer()->GetAccount() ==
                     temppOrderlist[row]->GetpCustomer()->GetAccount()))
            {
                g_Orderlist[i].SetType(4);
                QMessageBox::information(this, "SUCCESS", "更改成功",
                                         QMessageBox::Ok);
            }
        }
    }
    else
    {
        //订单状态不符
        QMessageBox::information(this, "FAILED", "订单状态有误！",
                                 QMessageBox::Ok);
    }


}

//创建新房间
void whotel::NewARoom()
{
    this->hide();
    //转向创建新房间界面
    pNewRoom = new NewRoom(this, pHotel);
    pNewRoom->show();
}

