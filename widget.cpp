#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    for (int i=0; i<2; i++)
    {
        hpBar[i].setParent(this);
        hpBar[i].resize(300,30);
        hpBar[i].move(50+i*400, 30);
        hpBar[i].setText("1"); //清空字体
        hpBar[i].setStyleSheet("QLabel{background-color:rgb(248,168,0);}");  //设置样式表
    }//设置血条
    for (int i=0; i<2; i++)
    {
        fighter[i].setParent(this);
        fighter[i].resize(50,80),
        fighter[i].move(i?50:700,400);
        fighter[i].setText("2");
        fighter[i].setStyleSheet("QLabel{background-color:rgb(0,168,50);}");
    }

    myTimer = new QTimer(this);
    myTimer->stop();
    myTimer->setInterval(30);
    connect(myTimer,SIGNAL(timeout()), this, SLOT(upDate()));
}

Widget::~Widget()
{

    delete ui;
}

void Widget::upDate()
{

}
