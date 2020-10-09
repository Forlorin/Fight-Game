#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    input(0,1),
    QWidget(parent),
    ui(new Ui::Widget)
{
    tottime=0;
    for(int i=0;i<20;i++)
    {
        inputtemp[i]=0;
        skillrec[0][i]=0;
        skillrec[1][i]=0;
    }

    tempslot=new QLabel(this);
    tempslot->setGeometry(500,230,500,40);
    tempslot->show();

    this->setFixedSize(1000,500);
    ui->setupUi(this);
    timer=startTimer(1000/30);

    La[0]=new QLabel(this);
    La[0]->setGeometry(0,0,1000,250);
    La[0]->setText("Hello La");

    La[1]=new QLabel(this);
    La[1]->setGeometry(0,250,1000,250);
    La[1]->setText("Hello Lb");

    Lskill[0]=new QLabel(this);
    Lskill[0]->setGeometry(500,0,500,100);
    Lskill[0]->show();
    Lskill[1]=new QLabel(this);
    Lskill[1]->setGeometry(500,100,500,100);
    Lskill[1]->show();

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
    if(!keyevent->isAutoRepeat())
        input.push(key,1);

    for(int i=0;i<19;i++)
    {
        inputtemp[i]=inputtemp[i+1];
    }
    inputtemp[19]=key;

    QString str="";
    for(int i=0;i<20;i++)
    {
        if(inputtemp[i]==Qt::Key_Up)
        {
            str+="↑";
        }
        if(inputtemp[i]==Qt::Key_Down)
        {
            str+="↓";
        }
        if(inputtemp[i]==Qt::Key_Left)
        {
            str+="←";
        }
        if(inputtemp[i]==Qt::Key_Right)
        {
            str+="→";
        }
        str+=char(inputtemp[i]);
    }
    tempslot->setText(str);

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

            str+="Pri:";
            str+=QString::number(ns->getPri());
            str+=" ";

            str+="Len:";
            str+=QString::number(ns->len);
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

                if(ns->queue[j]==Qt::Key_Up)
                {
                    str+="↑";
                }
                else if(ns->queue[j]==Qt::Key_Down)
                {
                    str+="↓";
                }
                else if(ns->queue[j]==Qt::Key_Left)
                {
                    str+="←";
                }
                else if(ns->queue[j]==Qt::Key_Right)
                {
                    str+="→";
                }
                else
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

        if(np->Act()!=-1)
        {
            str="player #"+QString::number(i)+":";
            for(int j=0;j<19;j++)
            {
                skillrec[i][j]=skillrec[i][j+1];
            }
            skillrec[i][19]=np->Act();

            for(int j=0;j<20;j++)
            {
                str+=QString::number(skillrec[i][j])+" ";
            }

            Lskill[i]->setText(str);
        }
    }
}

Widget::~Widget()
{
    delete ui;
}
