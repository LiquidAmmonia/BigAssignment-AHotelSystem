#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include<QWidget>
#include"loginwindow.h"

namespace Ui {
class loginwindow;
}

class loginwindow:public QWidget
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = 0);
    ~loginwindow();
    Ui::loginwindow *ui;

public slots:void login();
private:


}


#endif // LOGINWINDOW_H
