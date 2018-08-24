/********************************************************************
文件名：platform.cpp
功能模块和目的：实现平台管理员类的函数
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "platform.h"
#include "ui_platform.h"

#include "QMessageBox"
#include "qtablewidget.h"
#include "QDate"
#include "mydatabase.h"
#include "QVector"

#include "order.h"
#include "hotel.h"
#include "room.h"

#include "enums.h"

using namespace std;

extern QVector<Hotel>g_Hotellist;
extern QVector<Order>g_Orderlist;
extern QVector<Room>RawRoomlist;

extern QVector<Customer>g_Customerlist;

Platform::Platform(loginwindow1 *newparent) :
    parent(newparent),
    ui(new Ui::Platform)
{
    //将三种列表先显示出来
    ui->setupUi(this);
    ShowHotel();
    ShowRoom();
    ShowOrder();

    ShowCustomer();

    //装饰

    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("A Place To Stay ::Platform");
    //接口
    //刷新按钮
    connect(ui->btnRefreshtable1, SIGNAL(clicked(bool)), this, SLOT(Refresh1()));
    connect(ui->btnRefreshtable2, SIGNAL(clicked(bool)), this, SLOT(Refresh2()));
    connect(ui->btnRefreshtable3, SIGNAL(clicked(bool)), this, SLOT(Refresh3()));

    connect(ui->btnRefreshTable4, SIGNAL(clicked(bool)), this, SLOT(Refresh4()));

    //分别通过对酒店、房间、退款行为的显示。
    connect(ui->btnApproveHotel, SIGNAL(clicked(bool)), this, SLOT(ApproveHotel()));
    connect(ui->btnApproveRoom, SIGNAL(clicked(bool)), this, SLOT(ApproveRoom()));
    connect(ui->btnApproveOrder, SIGNAL(clicked(bool)), this, SLOT(ApproveOrder()));
    connect(ui->btnSTOP, SIGNAL(clicked(bool)), this, SLOT(STop()));

    connect(ui->btnDisable, SIGNAL(clicked(bool)), this, SLOT(DisAble()));

    //保存并退出
    connect(ui->btnSaveAndExit, SIGNAL(clicked(bool)), this, SLOT(SaveAndLogout()));

}

Platform::~Platform()
{
    delete ui;
}

//显示酒店列表
void Platform::ShowHotel()
{
    //显示酒店列表表头
    ui->table1->clear();
    ui->table1->setColumnCount(5);
    ui->table1->setHorizontalHeaderItem(0, new QTableWidgetItem
                                        (QStringLiteral("酒店名称")));
    ui->table1->setHorizontalHeaderItem(1, new QTableWidgetItem
                                        (QStringLiteral("酒店城市")));
    ui->table1->setHorizontalHeaderItem(2, new QTableWidgetItem
                                        (QStringLiteral("酒店地址")));
    ui->table1->setHorizontalHeaderItem(3, new QTableWidgetItem
                                        (QStringLiteral("酒店联系电话")));
    ui->table1->setHorizontalHeaderItem(4, new QTableWidgetItem
                                        (QStringLiteral("是否通过审查")));

    ui->table1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table1->setSelectionMode(QAbstractItemView::SingleSelection);

    //显示未审核信息个数
    int num = 0;
    //显示酒店列表内容
    for(int i=0;i<g_Hotellist.size();i++)
    {
        ui->table1->setRowCount(i+1);
        ui->table1->setItem(i, 0,
                            new QTableWidgetItem(g_Hotellist[i].GetHotelName()));
        ui->table1->setItem(i, 1,
                            new QTableWidgetItem(g_Hotellist[i].GetAddress()));
        ui->table1->setItem(i, 2,
                            new QTableWidgetItem(g_Hotellist[i].GetDistrict()));
        ui->table1->setItem(i, 3,
                            new QTableWidgetItem(g_Hotellist[i].GetConsolePhone()));
        QString temp;
        if(g_Hotellist[i].IsApproved())
            temp = "是";
        else
        {
            temp = "否";
            num++;
        }
        ui->table1->setItem(i, 4,
                            new QTableWidgetItem(temp));
    }

    ui->labelHotelNum->setText(QString::number(num) + "待审核");

}


//显示酒店的房间列表
void Platform::ShowRoom()
{
    //显示表头
    ui->table2->clear();
    ui->table2->setColumnCount(7);
    ui->table2->setHorizontalHeaderItem(0, new QTableWidgetItem
                                        (QStringLiteral("酒店名称")));
    ui->table2->setHorizontalHeaderItem(1, new QTableWidgetItem
                                        (QStringLiteral("房间种类")));

    ui->table2->setHorizontalHeaderItem(2, new QTableWidgetItem
                                        (QStringLiteral("房间照片")));
    ui->table2->setHorizontalHeaderItem(3, new QTableWidgetItem
                                        (QStringLiteral("房间个数")));
    ui->table2->setHorizontalHeaderItem(4, new QTableWidgetItem
                                        (QStringLiteral("房间价格")));
    ui->table2->setHorizontalHeaderItem(5, new QTableWidgetItem
                                        (QStringLiteral("房间描述")));
    ui->table2->setHorizontalHeaderItem(6, new QTableWidgetItem
                                        (QStringLiteral("是否通过审查")));

    //行选中
    ui->table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table2->setSelectionMode(QAbstractItemView::SingleSelection);

    //依次显示表的内容

    //显示未审核信息个数
    int num = 0;
    //显示信息的总行数
    int count = 1;

    for(int i=0;i<g_Hotellist.size();i++)
    {
        for(int j=0;j<g_Hotellist[i].Roomlist.size();j++)
        {

            QVector<Room>tempRoomlist = g_Hotellist[i].Roomlist;
            ui->table2->setRowCount(count);

            ui->table2->setItem(count-1, 0,
                                new QTableWidgetItem(tempRoomlist[j].GetHotelName()));
            QString str_type[5] = {"钟点房", "大床房", "双人房", "奢华房", "总统套房"};
            ui->table2->setItem(count-1, 1,
                                new QTableWidgetItem(str_type[tempRoomlist[j].GetType()]));

            QLabel *label = new QLabel("");

            label->setPixmap(QPixmap(tempRoomlist[j].GetImages()).scaled(125,150));

            ui->table2->setCellWidget(count-1, 2, label);

            ui->table2->setItem(count-1, 3,
                                new QTableWidgetItem(QString::number(tempRoomlist[j].GetNumber())));
            ui->table2->setItem(count-1, 4,
                                new QTableWidgetItem(QString::number(tempRoomlist[j].GetPrice())));
            ui->table2->setItem(count-1, 5,
                                new QTableWidgetItem(tempRoomlist[j].GetDiscription()));

            QString temp;
            if(tempRoomlist[j].IsApproved())
                temp = "是";
            else
            {
                temp = "否";
                num++;
            }

            ui->table2->setItem(count-1, 6,
                                new QTableWidgetItem(temp));
            count++;
        }
    }

    ui->labelNum2->setText(QString::number(num) + "待审核");

}

//显示订单列表
void Platform::ShowOrder()
{
    //显示表头
    ui->table3->clear();
    ui->table3->setColumnCount(7);
    ui->table3->setHorizontalHeaderItem(0, new QTableWidgetItem
                                        (QStringLiteral("顾客账号")));
    ui->table3->setHorizontalHeaderItem(1, new QTableWidgetItem
                                        (QStringLiteral("酒店姓名")));
    ui->table3->setHorizontalHeaderItem(2, new QTableWidgetItem
                                        (QStringLiteral("房间类型")));
    ui->table3->setHorizontalHeaderItem(3, new QTableWidgetItem
                                        (QStringLiteral("住房日期")));
    ui->table3->setHorizontalHeaderItem(4, new QTableWidgetItem
                                        (QStringLiteral("住房天数")));
    ui->table3->setHorizontalHeaderItem(5, new QTableWidgetItem
                                        (QStringLiteral("订单状态")));
    ui->table3->setHorizontalHeaderItem(6, new QTableWidgetItem
                                        (QStringLiteral("是否允许退款")));


    //单行选中
    ui->table3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table3->setSelectionMode(QAbstractItemView::SingleSelection);

    //显示内容

    //显示未审核信息个数
    int num = 0;
    for(int i=0;i<g_Orderlist.size();i++)
    {
        ui->table3->setRowCount(i+1);

        ui->table3->setItem(i, 0,
                            new QTableWidgetItem(g_Orderlist[i].GetpCustomer()->GetAccount()));
        ui->table3->setItem(i, 1,
                            new QTableWidgetItem(g_Orderlist[i].GetpRoom()->GetHotelName()));
        QString str_type[5] = {"钟点房", "大床房", "双人房", "奢华房", "总统套房"};
        ui->table3->setItem(i, 2,
                            new QTableWidgetItem(str_type[g_Orderlist[i].GetpRoom()->GetType()]));
        ui->table3->setItem(i, 3,
                            new QTableWidgetItem(g_Orderlist[i].GetDate().toString("dd.MM.yyyy")));
        ui->table3->setItem(i, 4,
                            new QTableWidgetItem(QString::number(g_Orderlist[i].GetDays())));
        QString str_OrderType[6] = {"已预订", "已交款", "退款", "已入住", "已退房", "已评论"};
        ui->table3->setItem(i, 5,
                            new QTableWidgetItem(str_OrderType[g_Orderlist[i].GetType()]));
        QString temp;
        if(g_Orderlist[i].GetRefundApproved())
            temp = "是";
        else
        {
            temp = "否";

        }
        ui->table3->setItem(i, 6,
                            new QTableWidgetItem(temp));
        if((!g_Orderlist[i].GetRefundApproved())&&(g_Orderlist[i].GetType() == 2))
        {
            num++;
        }

    }

    ui->labelRefundNum->setText(QString::number(num) + "待审核");

}

//刷新界面即为重新显示三种表
void Platform::Refresh1()
{
    ShowHotel();
}

void Platform::Refresh2()
{
    ShowRoom();
}

void Platform::Refresh3()
{
    ShowOrder();
}

//审核通过酒店列表
void Platform::ApproveHotel()
{
    int row;
    row = ui->table1->currentRow();
    //是否选中的判断
    if(row == -1)
    {
        QMessageBox::information(this, "ERROR", "未选中酒店！", QMessageBox::Ok);
        return;
    }
    if(g_Hotellist[row].IsApproved() == false)
    {
        g_Hotellist[row].SetApproved(true);
        QMessageBox::information(this, "SUCCESS", "审核成功！", QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, "ERROR", "该酒店已经通过审核！",
                                 QMessageBox::Ok);
    }


}

//审核通过酒店的房间
void Platform::ApproveRoom()
{
    int row;
    row = ui->table2->currentRow();
    //是否选中判断
    if(row == -1)
    {
        QMessageBox::information(this, "ERROR", "未选中房间！", QMessageBox::Ok);
        return ;
    }
    QString tempHotelName;
    int tempRoomType;
    QString tt = ui->table2->item(row, 1)->text();

    //类型转换
    tempHotelName = ui->table2->item(row, 0)->text();
    QString str_type[5] = {"钟点房", "大床房", "双人房", "奢华房", "总统套房"};

    for(int i=0;i<5;i++)
    {
        if(str_type[i] == tt)
        {
            tempRoomType = i;
        }
    }


    //找到相应的酒店进行修改
    int inow, jnow;
    for(int i=0;i<g_Hotellist.size();i++)
    {
        if(g_Hotellist[i].GetHotelName() == tempHotelName)
        {
            for(int j=0;j<g_Hotellist[i].Roomlist.size();j++)
            {
                if(g_Hotellist[i].Roomlist[j].GetType() == tempRoomType)
                {
                    inow = i;
                    jnow = j;
                }
            }
        }
    }

    //判断房间的审核是否通过并进行更改状态

    if(g_Hotellist[inow].Roomlist[jnow].IsApproved() == false)
    {
        g_Hotellist[inow].Roomlist[jnow].SetApproved(true);
        QMessageBox::information(this, "SUCCESS", "审核成功！",
                                 QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, "ERROR", "房间已审核！",
                                 QMessageBox::Ok);
    }
}

//审核退款操作
void Platform::ApproveOrder()
{
    int row;
    row = ui->table3->currentRow();
    //选中判断
    if(g_Orderlist[row].GetType() == 2)
    {
        if(g_Orderlist[row].GetRefundApproved() == false)
        {
            g_Orderlist[row].SetRefundApproved(true);

            QMessageBox::information(this, "SUCCESS", "允许退款成功！",
                                     QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(this, "ERROR", "订单已经退款，不必重复操作！",
                                     QMessageBox::Ok);
        }
    }
    //订单的状态判断
    else
    {
        QMessageBox::information(this, "ERROR", "订单不在退款阶段！",
                                 QMessageBox::Ok);
    }
}

//保存退出
void Platform::SaveAndLogout()
{
    //存入数据库
    myDatabase Database;
    Database.Memory();

    //显示登陆页面
    this->close();
    parent->show();
}

void Platform::STop()
{
    int row;
    row = ui->table1->currentRow();
    //是否选中的判断
    if(row == -1)
    {
        QMessageBox::information(this, "ERROR", "未选中酒店！", QMessageBox::Ok);
        return;
    }
    if(g_Hotellist[row].IsApproved() == false)
    {

        QMessageBox::information(this, "ERROR", "酒店本来就未通过审核！", QMessageBox::Ok);
    }
    else
    {
        g_Hotellist[row].SetApproved(false);
        QMessageBox::information(this, "SUCCESS", "酒店信息下架成功！",
                                 QMessageBox::Ok);
    }


}

void Platform::ShowCustomer()
{
    ui->table4->clear();
    ui->table4->setColumnCount(3);

    ui->table4->setHorizontalHeaderItem(0, new QTableWidgetItem
                                        (QStringLiteral("账号名称")));
    ui->table4->setHorizontalHeaderItem(1, new QTableWidgetItem
                                        (QStringLiteral("账号手机")));
    ui->table4->setHorizontalHeaderItem(2, new QTableWidgetItem
                                        (QStringLiteral("账号密码")));

    //行选中
    ui->table4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table4->setSelectionMode(QAbstractItemView::SingleSelection);

    for(int i=0;i<g_Customerlist.size();i++)
    {
        ui->table4->setRowCount(i+1);

        ui->table4->setItem(i, 0,
                            new QTableWidgetItem(g_Customerlist[i].GetAccount()));
        ui->table4->setItem(i, 1,
                            new QTableWidgetItem(g_Customerlist[i].GetPhone()));
        ui->table4->setItem(i, 2,
                            new QTableWidgetItem(g_Customerlist[i].GetPassword()));
    }



}

void Platform::Refresh4()
{
    ShowCustomer();
}

void Platform::DisAble()
{
    int row;
    row = ui->table4->currentRow();
    //是否选中的判断
    if(row == -1)
    {
        QMessageBox::information(this, "ERROR", "未选中酒店！", QMessageBox::Ok);
        return;
    }
    g_Customerlist.erase(&g_Customerlist[row]);
    QMessageBox::information(this, "SUCCESS", "删除成功", QMessageBox::Ok);
}

