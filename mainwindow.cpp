
/********************************************************************
文件名：MainWindow.cpp
功能模块和目的：用户主界面
开发者：程晔安
日期：7.30
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "qtablewidget.h"
#include "QDate"
#include "mydatabase.h"

#include "order.h"
#include "hotel.h"
#include "room.h"

#include "enums.h"
//建立排序显示

using namespace std;

extern QVector<Customer>g_Customerlist;
extern QVector<Hotel>g_Hotellist;
extern QVector<Order>g_Orderlist;

extern QVector<Room>RawRoomlist;

MainWindow::MainWindow(loginwindow1* newParent,
                       Customer* new_pCustomer) :
    parent(newParent), pCustomer(new_pCustomer),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ShowOrder();
    //装饰
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("A Place To Stay");

    //接口
    //tab1
    //查找对应酒店
    connect(ui->btnSearch, SIGNAL(clicked(bool)), this, SLOT(SearchARoomP1()));

    //显示酒店对应房间
    connect(ui->btnDetail, SIGNAL(clicked(bool)), this, SLOT(hide()));
    connect(ui->btnDetail, SIGNAL(clicked(bool)), this, SLOT(ShowDetail()));

    //保存并退出
    connect(ui->btnExit, SIGNAL(clicked(bool)), this, SLOT(SaveAndLogout()));
    //tab2
    //刷新
    connect(ui->btnRefresh, SIGNAL(clicked(bool)), this, SLOT(ShowOrder()));
    //确认付款
    connect(ui->btnPay, SIGNAL(clicked(bool)), this, SLOT(Pay()));
    //申请退款，由平台管理员控制
    connect(ui->btnRefund, SIGNAL(clicked(bool)), this, SLOT(Refund()));
    //提交相应评价
    connect(ui->btnComment, SIGNAL(clicked(bool)), this, SLOT(Comment()));

    //修改密码相关操作
    connect(ui->btnChangePass, SIGNAL(clicked(bool)), this, SLOT(ChangePassword()));
}

//析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

//输入检查函数，包括是否为空的检测和输入规范的检测
bool MainWindow::EnteringCheckP1()
{
    QString KeyCity = ui->lineSearchCity->text();
    QString KeyDistrict = ui->lineSearchDis->text();
    QString str_Days = ui->lineDays->text();
    float Days = 0;
    //判断输入是否为空
    if(KeyCity.isEmpty())
    {
        QMessageBox::information(this, "ERROR", "输入关键字不能为空",
                                 QMessageBox::Ok);
        return false;
    }
    if(str_Days.isEmpty())
    {
        QMessageBox::information(this, "ERROR", "输入日期不能为空",
                                 QMessageBox::Ok);
        return false;
    }
    else 
    {
        Days = str_Days.toFloat();
    }
    
    if((Days-(int)Days) != 0)
    {
        QMessageBox::information(this, "ERROR", "输入日期只能为整数",
                                 QMessageBox::Ok);
        return false;
    }
    //最多订房时长以及最少订房时长
    if(Days<=0||Days>30)
    {
        QMessageBox::information(this, "ERROR", "输入日期不合规范，只能在1~30之间",
                                 QMessageBox::Ok);
        return false;
    }
    return true;
}

void MainWindow::SearchARoomP1()
{
    //如果输入符合规则，就显示列表
    if(EnteringCheckP1())
    {
        temp_pHotellist.clear();
        ui->table->clear();
        ui->table->setColumnCount(5);
        ui->table->setRowCount(0);
        ui->table->setHorizontalHeaderItem(0,new QTableWidgetItem
                                           (QStringLiteral("酒店名称")));
        ui->table->setHorizontalHeaderItem(1,new QTableWidgetItem
                                           (QStringLiteral("地址")));
        ui->table->setHorizontalHeaderItem(2,new QTableWidgetItem
                                           (QStringLiteral("客房最低价格")));
        ui->table->setHorizontalHeaderItem(3,new QTableWidgetItem
                                           (QStringLiteral("联系电话")));
        ui->table->setHorizontalHeaderItem(4,new QTableWidgetItem
                                           (QStringLiteral("综合评分")));

        ui->table->horizontalHeader()->setStretchLastSection(true);
        //ui->table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

        //行选择
        ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->table->setSelectionMode(QAbstractItemView::SingleSelection);

        //输入信息
        QString tempCity = ui->lineSearchCity->text();
        QString tempDis = ui->lineSearchDis->text();
        QString str_tempType = ui->comboBox->currentText();


        //判断房间种类并进行显示
        int tempType = -1;
        if(str_tempType == "钟点房")
            tempType = 0;
        if(str_tempType == "大床房")
            tempType = 1;
        if(str_tempType == "双人房")
            tempType = 2;
        if(str_tempType == "奢华房")
            tempType = 3;
        if(str_tempType == "总统套房")
            tempType = 4;

        //将符合条件的酒店房间放在temp_Hotellist中
        for(int i=0;i<g_Hotellist.size();i++)
        {
            if(g_Hotellist[i].IsApproved())
            {
            if(tempDis.isEmpty())
            {
                if(tempCity == g_Hotellist[i].GetAddress())
                {
                    temp_pHotellist.push_back(&g_Hotellist[i]);
                }
            }
            else
            {
                if((tempCity == g_Hotellist[i].GetAddress())&&
                        (tempDis == g_Hotellist[i].GetDistrict()))
                {
                    temp_pHotellist.push_back(&g_Hotellist[i]);
                }
            }
            }
        }
        //筛选指定房型的酒店
        if(tempType >= 0)
        {
            for(int i=0; i < temp_pHotellist.size(); i++)
            {
                bool flag1 = false;
                for(int j=0;j < temp_pHotellist[i]->Roomlist.size(); j++)
                {
                    if(temp_pHotellist[i]->Roomlist[j].GetType() == tempType)
                        flag1 = true;
                }
                if(flag1 == false)
                {
                    temp_pHotellist.erase(&temp_pHotellist[i]);
                }
            }
        }
        //选择房间剩余量大于零的房间进行显示



        //选择房间显示顺序
        int SortType;
        if(ui->rbtnDefault->isChecked())
            SortType = 0;
        else if(ui->rbtnPrice->isChecked())
            SortType = 1;
        else
            SortType = 2;
        ShowHotel(SortType);
    }
}

//显示酒店
void MainWindow::ShowHotel(int SortType)
{
    for(int i=0;i<temp_pHotellist.size();i++)
    {
        ui->table->setRowCount(i+1);
        ui->table->setItem(i, 0,
                           new QTableWidgetItem(temp_pHotellist[i]->GetHotelName()));
        ui->table->setItem(i, 1,
                           new QTableWidgetItem(temp_pHotellist[i]->GetDistrict()));
        ui->table->setItem(i, 2,
                           new QTableWidgetItem(QString::number(temp_pHotellist[i]->GetMinPrice())));
        ui->table->setItem(i, 3,
                           new QTableWidgetItem(temp_pHotellist[i]->GetConsolePhone()));
        qDebug()<<temp_pHotellist[i]->GetStar();
        ui->table->setItem(i, 4,
                           new QTableWidgetItem(QString::number(temp_pHotellist[i]->GetStar())));
    }
    switch(SortType)
    {
        //按照默认方式排序排序
    case 0:

            break;
        //按照价格从低到高排序
    case 1:
           ui->table->sortItems(3, Qt::SortOrder::DescendingOrder);
        break;
    default:

        //按照评价从高到低显示
           ui->table->sortItems(5, Qt::SortOrder::AscendingOrder);
        break;
    }
}

//保存并退出
void MainWindow::SaveAndLogout()
{
    //存入数据库
    myDatabase Database;
    Database.Memory();

    //返回登陆界面
    this->close();
    parent->show();
    //清空密码
    parent->ClearPassword();
    return ;
}

int MainWindow::GetType()
{
    //输入的搜寻房间种类
    int Type;
    QString str_type[5] = {"钟点房", "大床房", "双人房", "奢华房", "总统套房"};
    QString temp = ui->comboBox->currentText();
    if(temp == "所有房型")
        Type = -1;
    else
    {
        for(int i=0;i<5;i++)
        {
            if(temp == str_type[i])
            {
                Type = i;
            }
        }
    }
    return Type;
}

Customer* MainWindow::GetpCustomer()
{
    //获取此时登陆的顾客的信息
    return pCustomer;
}

Hotel* MainWindow::GetpHotel()
{
    //获取此时选中的酒店的信息
    int row;
    row = ui->table->currentRow();
    if(row<0)
    {
        QMessageBox::information(this, "ERROR",
                                 "未选中酒店", QMessageBox::Ok);
        return NULL;
    }
    //找到酒店在全局变量中对应的指针
    QString HotelName;
    HotelName = ui->table->item(row, 0)->text();
    for(int i=0; i < temp_pHotellist.size(); i++)
    {
        if(temp_pHotellist[i]->GetHotelName() == HotelName)
        {
            return temp_pHotellist[i];
        }
    }
    return NULL;
}

QDate MainWindow::GetDate()
{
    //获取选择的日期
    QDate tempDate = ui->calendarWidget->selectedDate();
    return tempDate;
}

int MainWindow::GetDays()
{
    //获取选择的住店时长
    int tempDays = ui->lineDays->text().toInt();
    return tempDays;
}

void MainWindow::ShowDetail()
{
    //显示酒店对应的房间列表
    pChooseRoom = new ChooseRoom(this);
    pChooseRoom->show();
}

//显示该顾客的所有订单
void MainWindow::ShowOrder()
{
    //显示订单列表的表头
    temp_pOrderlist.clear();
    ui->table2->clear();
    ui->table2->setColumnCount(6);
    ui->table2->setRowCount(0);
    ui->table2->setHorizontalHeaderItem(0, new QTableWidgetItem
                                        (QStringLiteral("酒店名称")));
    ui->table2->setHorizontalHeaderItem(1, new QTableWidgetItem
                                        (QStringLiteral("房间种类")));
    ui->table2->setHorizontalHeaderItem(2, new QTableWidgetItem
                                        (QStringLiteral("订单状态")));
    ui->table2->setHorizontalHeaderItem(3, new QTableWidgetItem
                                        (QStringLiteral("开始日期")));
    ui->table2->setHorizontalHeaderItem(4, new QTableWidgetItem
                                        (QStringLiteral("订购天数")));
    ui->table2->setHorizontalHeaderItem(5, new QTableWidgetItem
                                        (QStringLiteral("退款是否成功")));

    //行选择
    ui->table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table2->setSelectionMode(QAbstractItemView::SingleSelection);



    //在全局变量中筛选出本用户的订单
    for(int i=0;i<g_Orderlist.size();i++)
    {
        if(g_Orderlist[i].GetpCustomer()->GetAccount() ==
                pCustomer->GetAccount())
        {
            temp_pOrderlist.push_back(&g_Orderlist[i]);
        }
    }

    //转换类型
    QString str_type[5] = {"钟点房", "大床房", "双人房", "奢华房", "总统套房"};
    QString str_OrderType[6] = {"已预订", "已交款",
                                "退款", "入住",
                                "待评论", "已评论"};

    //进行显示
    for(int i=0; i < temp_pOrderlist.size();i++)
    {
        ui->table2->setRowCount(i+1);

        ui->table2->setItem(i, 0, new QTableWidgetItem
                            (temp_pOrderlist[i]->GetpRoom()->GetHotelName()));
        ui->table2->setItem(i, 1, new QTableWidgetItem
                            (str_type[temp_pOrderlist[i]->GetpRoom()->GetType()]));

        ui->table2->setItem(i, 2, new QTableWidgetItem
                            (str_OrderType[temp_pOrderlist[i]->GetType()]));
        ui->table2->setItem(i, 3, new QTableWidgetItem
                            (temp_pOrderlist[i]->GetDate().toString()));
        ui->table2->setItem(i, 4, new QTableWidgetItem
                            (QString::number(temp_pOrderlist[i]->GetDays())));
        QString temp;

        if(temp_pOrderlist[i]->GetRefundApproved())
            temp = "是";
        else
            temp = "否";
        ui->table2->setItem(i, 5, new QTableWidgetItem
                            (temp));

    }



}

//改变订单种类，实现支付操作
void MainWindow::Pay()
{
    int row;
    row = ui->table2->currentRow();

    //是否选中判定
    if(row<0)
    {
        QMessageBox::information(this, "ERROR",
                                 "未选中订单", QMessageBox::Ok);
        return;
    }
    //确定选中的订单的状态
    int currType ;
    QString temp = ui->table2->item(row, 2)->text();
    QString str_OrderType[6] = {"已预订", "已交款", "退款", "已入住", "已退房", "已评论"};
    for(int i=0;i<6;i++)
    {
        if(temp == str_OrderType[i])
        {
            currType = i;
        }
    }

    //确定选中的订单的状态
    if(currType == 0)
    {
        for(int i=0;i<g_Orderlist.size();i++)
        {
            if(g_Orderlist[i].GetpRoom()->GetRoomId() ==
                    temp_pOrderlist[row]->GetpRoom()->GetRoomId())
            {
                QMessageBox::information(this, "Payment",
                                      "付款成功！", QMessageBox::Ok);
                g_Orderlist[i].SetType(1);
                break;
            }
        }

        //存一下
        myDatabase DataBase;
        DataBase.Memory();
        QMessageBox::information(this, "Saved", "信息已保存", QMessageBox::Ok);

    }

    else
    {
        QMessageBox::information(this, "ERROR",
                                 "选中的订单状态有误！", QMessageBox::Ok);

    }
}

//更改订单状态为申请退款，等待平台管理员审核
void MainWindow::Refund()
{
    int row;
    row = ui->table2->currentRow();

    //判断是否选中订单
    if(row<0)
    {
        QMessageBox::information(this, "ERROR",
                                 "未选中订单", QMessageBox::Ok);
        return;
    }
    QString temp = ui->table2->item(row, 2)->text();
    QString str_OrderType[6] = {"已预订", "已交款",
                                "退款", "入住",
                                "退房", "已评论"};

    //判断选中的订单的状态
    int currType ;
    for(int i=0;i<6;i++)
    {
        if(str_OrderType[i] == temp)
        {
            currType = i;
        }
    }

    //如果订单状态为Refund，则交由平台管理员进行审核，如果同意，则退款。
    if(currType == 1)
    {
        for(int i=0;i<g_Orderlist.size();i++)
        {
            if(g_Orderlist[i].GetpRoom()->GetRoomId() ==
                    temp_pOrderlist[row]->GetpRoom()->GetRoomId())
            {
                QMessageBox::information(this, "Refund",
                                      "退款信息提交成功，等待管理员审核", QMessageBox::Ok);
                g_Orderlist[i].SetType(2);

            }
        }

        //存一下
        myDatabase DataBase;
        DataBase.Memory();
        QMessageBox::information(this, "Saved", "信息已保存", QMessageBox::Ok);

    }
    else
    {
        QMessageBox::information(this, "ERROR",
                                 "选中的订单状态有误！", QMessageBox::Ok);

    }

}

//对已经退房的订单进行评价，评价的信息储存在相应的房间中
void MainWindow::Comment()
{
    int row;
    row = ui->table2->currentRow();

    //判断是否选中该订单
    if(row<0)
    {
        QMessageBox::information(this, "ERROR",
                                 "未选中订单", QMessageBox::Ok);
        return;
    }

    int currType ;
    QString temp;
    temp = ui->table2->item(row, 2)->text();
    QString str_OrderType[6] = {"已预订", "已交款",
                                "退款", "入住",
                                "待评论", "已评论"};
    //判断选中的订单的状态
    for(int i=0;i<6;i++)
    {
        if(str_OrderType[i] == temp)
        {
            currType = i;
        }
    }

    //进入评价栏进行评价
    if(currType == 4)
    {
        for(int i=0;i<g_Orderlist.size();i++)
        {
            if(g_Orderlist[i].GetpRoom()->GetRoomId() ==
                    temp_pOrderlist[row]->GetpRoom()->GetRoomId())
            {

                this->hide();
                pComment = new WComment(this, temp_pOrderlist[i]);
                pComment->show();
                //

            }
        }
        //存一下

    }
    else
    {
        QMessageBox::information(this, "ERROR", "订单状态有误", QMessageBox::Ok);
    }
}

void MainWindow::ChangePassword()
{
    //手机验证码程序是之后可开发的项目
    //判断旧密码输入是否正确
    QString OldPassword = ui->lineOldPassword->text();
    if(OldPassword.isEmpty())
    {
        QMessageBox::information(this, "ERROR", "未输入旧密码", QMessageBox::Ok);

    }
    if( OldPassword == pCustomer->GetPassword())
    {
        //判断新密码输入是否符合规定
        QString newPassword = ui->lineNewPasss->text();
        if(newPassword.isEmpty())
        {
            QMessageBox::information(this, "ERROR", "未输入新密码", QMessageBox::Ok);
        }
        else
        {
            //新密码设置成功，保存信息重新登录
            pCustomer->SetPassword(newPassword);
            QMessageBox::information(this, "SUCCESS", "新密码设置成功，请重新登录！", QMessageBox::Ok);
            myDatabase Database;
            Database.Memory();
            this->close();
            parent->show();

        }
    }
    else
    {
        QMessageBox::information(this, "ERROR", "旧密码错误", QMessageBox::Ok);
    }

}
