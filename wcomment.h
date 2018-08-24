
/**************************************************************************
文件名：wcomment.h
功能模块和目的：添加评论
开发者：程晔安
日期：8.3
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：
**************************************************************************/

#ifndef WCOMMENT_H
#define WCOMMENT_H

#include <QDialog>

#include "order.h"


/**************************************************************************
类名：wComment
功能：为已完成的订单添加评论
接口说明：有指向mainWindow的指针
开发者：程晔安
日期：8.3
更改记录：
**************************************************************************/

namespace Ui {
class WComment;
}

class MainWindow;

class WComment : public QDialog
{
    Q_OBJECT

public:
    explicit WComment(MainWindow *parent, Order* pOrder);
    ~WComment();

public slots:
    //添加评论
    void Comment();

private:
    //记录相关信息
    Ui::WComment *ui;
    MainWindow*parent;
    Order *pOrder;

};

#endif // WCOMMENT_H
