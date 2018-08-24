/********************************************************************
文件名：roomchange.cpp
功能模块和目的：实现对房间信息的修改
开发者：程晔安
日期：8.3
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**********************************************************************/

#include "roomchange.h"
#include "ui_roomchange.h"

#include "enums.h"
#include "room.h"
#include "hotel.h"



using namespace std;

extern QVector<Hotel>g_Hotellist;


RoomChange::RoomChange(whotel*newparent, Room*newpRoom) :
    parent(newparent),pRoom(newpRoom),
    ui(new Ui::RoomChange)
{
    ui->setupUi(this);
    //装饰
    ShowOldInfo();

    this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("APlaceToStay--Change Room");

    //slots

    //返回酒店主界面
    connect(ui->btnCancel, SIGNAL(clicked(bool)), this, SLOT(Cancel()));

    //保存相关信息
    connect(ui->btnSave, SIGNAL(clicked(bool)), this, SLOT(Save()));

    //打开图片及显示
    connect(ui->btnOpen,SIGNAL(clicked(bool)), this, SLOT(OpenImag()));

    //保存图片到相关文件夹
    connect(ui->btnSaveImag, SIGNAL(clicked(bool)), this, SLOT(SaveImag()));



}

RoomChange::~RoomChange()
{
    delete ui;
}

//返回
void RoomChange::Cancel()
{
    this->close();
    parent->show();
}

//打开图片并打印在预览界面中
void RoomChange::OpenImag()
{
    //获取文件exe路径
    runPath = QCoreApplication::applicationDirPath();
    //新文件姓名
    hglpName = "photo";
    //文件存储路径
    hglpPath = QString("%1/%2").arg(runPath).arg(hglpName);

    QString filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",
                                                  tr("Images (*.png *.bmp *.jpg)"));
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
        ui->labelimag->setPixmap(QPixmap::fromImage(img.scaled(ui->labelimag->size())));
    }


}

//保存图片文件
void RoomChange::SaveImag()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QString Name = ui->lineName->text();
    screen->grabWindow(ui->labelimag->winId()).save(QString("%1/%2.jpg").arg(hglpPath).arg(Name));

    pRoom->SetImages(QString("./photo/%1.jpg").arg(Name));

    QMessageBox::information(this, "SAVED", "图片已保存在.exe文件路径中", QMessageBox::Ok);

}

//保存相关信息
void RoomChange::Save()
{
    int newNumber = ui->lineNum->text().toInt();
    pRoom->SetNumber(newNumber);
    float newDiscount = ui->lineDiscount->text().toFloat();
    pRoom->SetDiscount(newDiscount);
    QString newDicription = ui->lineDiscription->text();
    pRoom->SetDiscription(newDicription);
    int newprice = ui->linePrice->text().toInt();
    pRoom->SetPrice(newprice);


    //自动将审核过程调为“未审”
    //更改完信息之后需要重新审核
    pRoom->SetApproved(false);
    QMessageBox::information(this, "SUCCESS",
                             "保存成功！等待管理员审核", QMessageBox::Ok);
    this->close();
    parent->show();
}

//显示更改前信息作为lineEdit的老信息
void RoomChange::ShowOldInfo()
{
    ui->lineNum->setText(QString::number(pRoom->GetNumber()));
    ui->lineDiscount->setText(QString::number(pRoom->GetDiscount(), 'f', 2));
    ui->lineDiscription->setText(pRoom->GetDiscription());
    ui->linePrice->setText(QString::number(pRoom->GetPrice()));
    QImage img;
    if(!(img.load(pRoom->GetImages()))) //加载图像
    {
        QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
        return;
    }
    ui->labelimag->setPixmap(QPixmap::fromImage(img.scaled(ui->labelimag->size())));


}


