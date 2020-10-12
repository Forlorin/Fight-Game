#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    input(0,0),
    QWidget(parent),
    ui(new Ui::Widget)
{

    nact=1;
    frime=3;
    ndx=0;
    ndy=0;
    hasK=0;

    nstat=1;

    cstat=new QPushButton(this);
    cstat->setGeometry(860,800,100,50);
    cstat->setText(QString::number(nstat));
    connect(cstat,SIGNAL(pressed()),this,SLOT(changestat()));
    cstat->show();

    timer=-1;
    timer=startTimer(1000/frime);

    cinair=new QPushButton(this);
    cinair->setGeometry(860,900,100,50);
    cinair->setText(QString::number(in_air));
    connect(cinair,SIGNAL(pressed()),this,SLOT(changein_air()));
    cinair->show();

    pbut=new QPushButton(this);
    pbut->setGeometry(860,600,100,50);
    pbut->setText("pause");
    connect(pbut,SIGNAL(pressed()),this,SLOT(pac()));

    cx[0]=new QPushButton(this);
    cx[1]=new QPushButton(this);
    cy[0]=new QPushButton(this);
    cy[1]=new QPushButton(this);
    connect(cx[0],&QPushButton::pressed,this,[=](){changexy(-1,0);});
    connect(cx[1],&QPushButton::pressed,this,[=](){changexy(1,0);});
    connect(cy[0],&QPushButton::pressed,this,[=](){changexy(0,-1);});
    connect(cy[1],&QPushButton::pressed,this,[=](){changexy(0,1);});

    cx[0]->setGeometry(860,720,50,50);
    cx[0]->setText("x-");
    cx[1]->setGeometry(860,660,50,50);
    cx[1]->setText("x+");
    cy[0]->setGeometry(920,720,50,50);
    cy[0]->setText("y-");
    cy[1]->setGeometry(920,660,50,50);
    cy[1]->setText("y+");

    nextact=new QPushButton(this);
    nextact->setGeometry(750,600,100,50);
    nextact->setText("next");
    connect(nextact,SIGNAL(pressed()),this,SLOT(changeact()));
    nextact->show();

    actit=new QPushButton(this);
    actit->setGeometry(750,660,100,50);
    actit->setText("act");
    connect(actit,SIGNAL(pressed()),this,SLOT(act()));
    actit->show();

    ctime=new QPushButton(this);
    ctime->setGeometry(750,720,100,50);
    ctime->setText(QString::number(frime));
    connect(ctime,SIGNAL(pressed()),this,SLOT(changetime()));
    ctime->show();

    fight=new FightObject(500,250,0,0);

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            cha[i][j]=new QLabel(this);
            cha[i][j]->setGeometry(500,650,0,0);
            cha[i][j]->show();
        }
    }

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

    this->setFixedSize(1000,1000);
    ui->setupUi(this);

    La[0]=new QLabel(this);
    La[0]->setGeometry(0,0,500,500);
    La[0]->setText("Hello La");

    La[1]=new QLabel(this);
    La[1]->setGeometry(0,500,500,500);
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

    //fight->player[0].do_act(0,-10);
}

void Widget::timerEvent(QTimerEvent *)
{
    viewupdate();
    int st0,st1,p1,p2;
    input.getSt(st0,st1,p1,p2,nstat,nstat);
    fight->player[0].do_act(st0,p1);
    //viewupdate();
    Ltime->setText(QString::number(tottime++));
    input.update();
    fight->player[0].update();
}

void Widget::keyPressEvent(QKeyEvent *keyevent)
{
    int key=keyevent->key();
    if(!keyevent->isAutoRepeat())
        input.push(key,1);

    hasK=1;

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
            if(i<10)
                str+=" ";
            str+=QString::number(i);
            str+=": ";

            str+="Pri:";
            if(ns->getPri()>0)
                str+=" ";
            str+=QString::number(ns->getPri());
            str+=" ";

            str+="Sta:";
            str+=QString::number(ns->status);
            str+=" ";

            str+="Ref:";
            str+=QString::number(ns->id);
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

            if(ns->isAct(nstat))
                str+=" Acting!",hasA=1;
            str+="\n";
        }

        if(hasA)
        {
            str+="";
        }

//        str+="Now Acting: ";
//        int tid,tpri;
//        np->Act(nstat,tid,tpri);
//        str+=QString::number(tid);
//        str+="\n";

        La[i]->setText(str);

//        if(tid!=0)
//        {
//            str="player #"+QString::number(i)+":";
//            for(int j=0;j<19;j++)
//            {
//                skillrec[i][j]=skillrec[i][j+1];
//            }
//            skillrec[i][19]=tid;

//            for(int j=0;j<20;j++)
//            {
//                str+=QString::number(skillrec[i][j])+" ";
//            }

//            Lskill[i]->setText(str);
//        }
    }

    cha[0][0]->hide();
    cha[0][0]->hide();

    qDebug()<<fight->player[0].act_doing<<' '<<fight->player[0].act_timer;

    Hitbox nhit;
    nhit=fight->player[0].get_hitbox();
    int dx,dy,dw,dh;
    int ox=600,oy=600;
    QString timg;
    nhit.get(dx,dy,dw,dh,timg);
    dx*=4;
    dy*=4;
    dw*=4;
    dh*=4;
    cha[0][0]->setGeometry(ox+dx+ndx,oy-dy-ndy,dw,dh);
    cha[0][0]->setStyleSheet("QLabel{border-image: url("+timg+")}");
    qDebug()<<timg;
    cha[0][0]->show();

    nhit=fight->player[0].get_atabox();
    nhit.get(dx,dy,dw,dh,timg);
    dx*=4;
    dy*=4;
    dw*=4;
    dh*=4;
    cha[0][1]->setGeometry(ox+dx,oy-dy,dw,dh);
    cha[0][1]->setStyleSheet("QLabel{border-image: url("+timg+")}");
    qDebug()<<timg;
    cha[0][1]->show();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeact()
{
    nact+=1;
    if(nact==27)
        nact=0;
    nextact->setText(QString::number(nact));
}

void Widget::changetime()
{
    killTimer(timer);
    frime/=2;
    if(frime==0)
        frime=30;
    timer=startTimer(1000/frime);
    ctime->setText(QString::number(frime));
}

void Widget::changestat()
{
    nstat+=1;
    if(nstat==2||nstat==3)
        changein_air();
    if(nstat==6)
        nstat=1;
    cstat->setText(QString::number(nstat));
}

void Widget::changein_air()
{
    in_air=!in_air;
    fight->player[0].set_in_air(in_air);
    cinair->setText(QString::number(in_air));
}

void Widget::changexy(int a, int b)
{
    ndx+=a;
    ndy+=b;
    pbut->setText(QString::number(ndx)+" "+QString::number(ndy));
    viewupdate();
}

void Widget::act()
{
    fight->player[0].do_act(nact,-10);
}

void Widget::pac()
{
    if(timer!=-1)
    {
        killTimer(timer);
        timer=-1;
    }
    else
    {
        timer=startTimer(1000/frime);
    }
}
