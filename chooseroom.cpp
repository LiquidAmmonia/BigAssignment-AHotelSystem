

/*
文件名：chooseroom.cpp
功能模块和目的：房间选择界面的功能实现
开发者：程晔安
日期：8.1
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
*/

#include "chooseroom.h"
#include "ui_chooseroom.h"

#include "QMessageBox"
#include "qtablewidget.h"
#include "Qdate"
#include "mydatabase.h"

#include "mainwindow.h"
#include "order.h"
#include "hotel.h"
#include "room.h"

using namespace std;
extern QVector<Order>g_Orderlist;
extern QVector<Room>RawRoomlist;

ChooseRoom::ChooseRoom(MainWindow *newParent) :
    parent(newParent),
    ui(new Ui::ChooseRoom)
{
    ui->setupUi(this);
    MakeAnOrder();
    //装饰

    this->setWindowTitle("Choose your room!");
    this->setFixedSize(this->width(),this->height());


    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //接口

    //确定生成订单
    connect(ui->btnOrder, SIGNAL(clicked(bool)), this, SLOT(EnterOrder()));

    //关闭窗口操作
    connect(ui->btnBack, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(ui->btnBack, SIGNAL(clicked(bool)), parent, SLOT(show()));

    //刷新列表
    connect(ui->btnRefresh, SIGNAL(clicked(bool)), this, SLOT(MakeAnOrder()));
}

ChooseRoom::~ChooseRoom()
{
    delete ui;
}

void ChooseRoom::MakeAnOrder()
{
    //初始化这个列表
    tempRoomlist.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem
                                             (QStringLiteral("房间图片")));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem
                                             (QStringLiteral("房间类型")));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem
                                             (QStringLiteral("房间价格")));   
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem
                                             (QStringLiteral("房间折扣")));
    ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem
                                             (QStringLiteral("房间数量")));
    ui->tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem
                                             (QStringLiteral("房间评分")));
    ui->tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem
                                             (QStringLiteral("卖家描述")));

    //开始进行显示
    //Hotel* tempHotel = parent->GetpHotel();
    tempDate = parent->GetDate();
    tempDays = parent->GetDays();
    int tempType = parent->GetType();

    //筛选可能的房间信息
    //如果有Type进行筛选
    if(tempType >= 0)
    {

        for(int i=0;i<parent->GetpHotel()->Roomlist.size();i++)
        {
            if(parent->GetpHotel()->Roomlist[i].GetType() == tempType)
            {
                tempRoomlist.push_back(&parent->GetpHotel()->Roomlist[i]);
            }

        }
    }
    else
    {
        for(int i=0;i<parent->GetpHotel()->Roomlist.size();i++)
        {
            tempRoomlist.push_back(&parent->GetpHotel()->Roomlist[i]);
        }
    }

    //筛选现在还剩下的房间
    //遍历订单筛选出已经被订的相应房间的时间，实现显示时显示剩余房间数
    for(int i = 0; i < tempRoomlist.size(); i++)
    {
        tempRoomlist[i]->curDays = tempRoomlist[i]->GetNumber();
        for(int j = 0; j < g_Orderlist.size(); j++)
        {
            int token = 0;
            if((g_Orderlist[j].GetpRoom()->GetRoomId() ==
                    tempRoomlist[i]->GetRoomId())
                    &&(g_Orderlist[j].GetType() != 5))
            {
                for(int k=0;k < g_Orderlist[j].GetDays(); k++)
                {
                    QDate tempOrderDay = g_Orderlist[j].GetDate().addDays(k);
                    for(int m = 0;m < tempDays;m++)
                    {
                        QDate tempRoomDate = tempDate.addDays(m);
                        if(tempOrderDay == tempRoomDate)
                        {

                            token = 1;
                        }
                    }
                }
            }
            if(token == 1)
            {
                tempRoomlist[i]->curDays--;
            }
        }
    }

    //转换类型
    QString str_type[5] = {"钟点房", "大床房", "双人房", "奢华房", "总统套房"};


    //输出筛选过后的酒店信息
    for(int i=0;i<tempRoomlist.size();i++)
    {
        if(tempRoomlist[i]->curDays > 0)
        {
            ui->tableWidget->setRowCount(i+1);
            ui->tableWidget->setRowHeight(i+1,100);

            QLabel *label = new QLabel("");

            label->setPixmap(QPixmap(tempRoomlist[i]->GetImages()).scaled(125,150));

            ui->tableWidget->setCellWidget(i, 0, label);
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem
                                     (str_type[tempRoomlist[i]->GetType()]));
            int actPrice = tempRoomlist[i]->GetDiscount()*tempRoomlist[i]->GetPrice();
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem
                                     (QString::number(actPrice)));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem
                                     (QString::number(tempRoomlist[i]->GetDiscount(),'f',2)));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem
                                     (QString::number(tempRoomlist[i]->curDays)));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem
                                     (QString::number(tempRoomlist[i]->GetStar())));
            ui->tableWidget->setItem(i, 6, new QTableWidgetItem
                                     (tempRoomlist[i]->GetDiscription()));
        }

    }
    //三种排列方式
    if(ui->rbtndefault->isChecked())
    {

    }
    else if (ui->rbtnPrice->isChecked())
    {
        //按照价格升序排列
        ui->tableWidget->sortByColumn(2, Qt::SortOrder::AscendingOrder);
    }
    else
    {
        //按照评分降序排列
        ui->tableWidget->sortByColumn(4, Qt::SortOrder::DescendingOrder);
    }
}

//确认订单
void ChooseRoom::EnterOrder()
{
    int row;

    row = ui->tableWidget->currentRow();


    //选中判断
    if(row<0)
    {
        QMessageBox::information(this, "ERROR",
                                 "未选中订单", QMessageBox::Ok);
        return;
    }

    //新建订单
    Room* tempRoom = tempRoomlist[row];

    Order newOrder(tempDate, tempDays, tempRoom, parent->GetpCustomer());

    g_Orderlist.push_back(newOrder);

    QMessageBox::information(this, "SUCCESS", "订购成功！可以在订单列表中查询。",
                             QMessageBox::Ok);
}


