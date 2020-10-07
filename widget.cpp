#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    input(0,1),
    QWidget(parent),
    ui(new Ui::Widget)
{
    tottime=0;

    this->setFixedSize(1000,500);
    ui->setupUi(this);
    timer=startTimer(1000/2);

    La[0]=new QLabel(this);
    La[0]->setGeometry(0,0,1000,250);
    La[0]->setText("Hello La");

    La[1]=new QLabel(this);
    La[1]->setGeometry(0,250,1000,250);
    La[1]->setText("Hello Lb");

    for(int i=0;i<2;i++)
    {
        La[i]->show();
        La[i]->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    }

    Ltime=new QLabel(this);
    Ltime->setGeometry(750,200,250,100);
    Ltime->show();
}

void Widget::timerEvent(QTimerEvent *)
{
    input.update();
    viewupdate();
    Ltime->setText(QString::number(tottime++));
}

void Widget::keyPressEvent(QKeyEvent *keyevent)
{
    int key=keyevent->key();
    qDebug()<<char(key);
    if(!keyevent->isAutoRepeat())
        input.push(key,1);
    viewupdate();
}

void Widget::viewupdate()
{
    for(int i=0;i<2;i++)
    {
        QString str="";
        str+="Skill slot #";
        str+=QString::number(i);
        str+="\n";

        player* np=&input.pl[i];

        bool hasA=0;

        for(int i=0;i<skill_num;i++)
        {
            skillslot* ns=&np->skills[i];

            if(np->skills[i].empty)
                continue;
            str+="Skill #";
            str+=QString::number(i);
            str+=": ";

            str+="Pri: ";
            str+=QString::number(ns->getPri());
            str+=" ";

            str+="Queue: ";

            for(int j=0;j<ns->len;j++)
            {
                if(ns->flag==j)
                    str+="(";
                else if(ns->flag>j)
                    str+="_";
                else
                    str+=" ";
                str+=char(ns->queue[j]);
                if(ns->flag==j)
                    str+=")";
                else if(ns->flag>j)
                    str+="_";
                else
                    str+=" ";
            }

            if(ns->isAct())
                str+=" Acting!",hasA=1;
            str+="\n";
        }

        if(hasA)
        {
            str+="";
        }

        str+="Now Acting: ";
        str+=QString::number(np->Act());
        str+="\n";

        La[i]->setText(str);
    }
}

Widget::~Widget()
{
    delete ui;
}
