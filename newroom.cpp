
/********************************************************************
文件名：newroom.cpp
功能模块和目的：创建界面以输入新房间信息
开发者：程晔安
日期：8.2
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "newroom.h"
#include "ui_newroom.h"

#include "enums.h"
#include "room.h"
#include "hotel.h"

using namespace std;

extern QVector<Hotel>g_Hotellist;
extern QVector<Room>RawRoomlist;

//创建界面新建酒店房间
NewRoom::NewRoom(whotel*newparent, Hotel*newHotel) :
    parent(newparent),pHotel(newHotel),
    ui(new Ui::NewRoom)
{
    ui->setupUi(this);

    pRoom = new Room(pHotel->GetHotelName(), 500, 3, -1);
    //装饰
    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("Create A New Room");

    //slots

    connect(ui->btnCancel, SIGNAL(clicked(bool)), this, SLOT(Cancel()));
    connect(ui->btnEnter, SIGNAL(clicked(bool)), this, SLOT(Save()));
    connect(ui->btnOpen,SIGNAL(clicked(bool)), this, SLOT(OpenImag()));
    connect(ui->btnSaveImage, SIGNAL(clicked(bool)), this, SLOT(SaveImag()));

}

NewRoom::~NewRoom()
{
    delete ui;
}

//取消返回
void NewRoom::Cancel()
{

    this->close();
    parent->show();
}

//打开酒店房间需要张贴的图片
void NewRoom::OpenImag()
{
    //获取文件exe路径
    runPath = QCoreApplication::applicationDirPath();
    //新文件姓名
    hglpName = "photo";
    //文件存储路径
    hglpPath = QString("%1/%2").arg(runPath).arg(hglpName);

    QString filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",
                                                  tr("Images (*.png *.bmp *.jpg)"));
    //是否打开成功
    if(filename.isEmpty())
        return;
    else
    {
        QImage img;
        if(!(img.load(filename))) //加载图像
        {
            QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
            return;
        }
        ui->lableImage->setPixmap(QPixmap::fromImage(img.scaled(ui->lableImage->size())));
    }


}

//保存图片
void NewRoom::SaveImag()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QString Name = ui->lineName->text();
    screen->grabWindow(ui->lableImage->winId()).save(QString("%1/%2.jpg").arg(hglpPath).arg(Name));

    pRoom->SetImages(QString("./photo/%1.jpg").arg(Name));
    QMessageBox::information(this, "SAVED", "图片已保存在.exe文件路径的Photo文件夹中。", QMessageBox::Ok);

}

//保存所有信息
void NewRoom::Save()
{
    //检查输入
    bool flag0 = CheckEntering();
    if(flag0 == false)
        return ;

    //房间数量
    int newNumber = ui->lineNum->text().toInt();
    pRoom->SetNumber(newNumber);
    //酒店房间优惠，可以缺省
    if(!ui->lineDiscount->text().isEmpty())
    {
        float newDiscount = ui->lineDiscount->text().toFloat();
        pRoom->SetDiscount(newDiscount);
    }
    //酒店房间介绍，可以缺省
    if(!ui->lineDiscription->text().isEmpty())
    {
    QString newDicription = ui->lineDiscription->text();
    pRoom->SetDiscription(newDicription);
    }
    //价格
    int newprice = ui->linePrice->text().toInt();
    pRoom->SetPrice(newprice);

    int newType = ui->comboBox->currentIndex();
    pRoom->SetType(newType);
    //判断是否已经有相应类型的房间，如果有，不能重复创建，而应该在修改界面改变
    //相应房间数量

    bool flag = true;
    QVector<Room>tempRoomlist = pHotel->Roomlist;
    for(int i=0;i<tempRoomlist.size();i++)
    {
        if(tempRoomlist[i].GetType() == newType)
            flag = false;
    }
    if(flag == true)
    {

        Room aRoom = *pRoom;

        pHotel->Roomlist.append(aRoom);
        QMessageBox::information(this, "SUCCESS", "成功添加！等待管理员审核",
                                 QMessageBox::Ok);

        //自动将审核过程调为“未审”
        pRoom->SetApproved(false);


        this->close();
        parent->show();
    }
    else
    {
        QMessageBox::information(this, "FAILED", "添加失败，已经有相应类型房间",
                                 QMessageBox::Ok);
    }


}

bool NewRoom::CheckEntering()
{
    //价格、类型、数量必填
    if(ui->lineNum->text().isEmpty()||
            ui->linePrice->text().isEmpty()||
            ui->comboBox->currentText().isEmpty())
    {
        QMessageBox::information(this, "ERROR", "信息不全",
                                 QMessageBox::Ok);
        return false;
    }
    return true;
}
