#include "inputslot.h"
#include <QDebug>

void inputslot::push(int id,bool face)
{
    switch(id)
    {
    case Qt::Key_A:
    case Qt::Key_D:
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_J:
    case Qt::Key_K:
    case Qt::Key_L:
    case Qt::Key_U:
    case Qt::Key_I:
    case Qt::Key_O:
        pl[0].push(trans(id,face));
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
        pl[1].push(trans(id,face));
        break;
    default:
        qDebug()<<"Error push fail :"<<id;
    }
}

void inputslot::update()
{
    pl[0].update();
    pl[1].update();
}

void inputslot::getSt(int &a, int &b)
{
    a=pl[0].Act();
    b=pl[1].Act();
}

int inputslot::trans(int id,bool face)
{
    switch(id)
    {
    case Qt::Key_W:
    case Qt::Key_Up:
        return Qt::Key_Up;
    case Qt::Key_A:
        if(face)
        return Qt::Key_Left;
        return Qt::Key_Right;
    case Qt::Key_Left:
        if(face)
        return Qt::Key_Right;
        return Qt::Key_Left;
    case Qt::Key_D:
        if(face)
        return Qt::Key_Right;
        return Qt::Key_Left;
    case Qt::Key_Right:
        if(face)
        return Qt::Key_Left;
        return Qt::Key_Right;
    case Qt::Key_S:
    case Qt::Key_Down:
        return Qt::Key_Down;
    case Qt::Key_J:
    case Qt::Key_1:
        return Qt::Key_J;
    case Qt::Key_K:
    case Qt::Key_2:
        return Qt::Key_K;
    case Qt::Key_L:
    case Qt::Key_3:
        return Qt::Key_L;
    case Qt::Key_U:
    case Qt::Key_4:
        return Qt::Key_U;
    case Qt::Key_I:
    case Qt::Key_5:
        return Qt::Key_I;
    case Qt::Key_O:
    case Qt::Key_6:
        return Qt::Key_O;

    default:
        qDebug()<<"Error Keytrans "<<id;
        return 0;
    }
}

inputslot::inputslot(int a, int b)
{
    pl[0]=player(a);
    pl[1]=player(b);
}

void skillslot::push(int id)
{
    if(flag>=len)
    {
        return;
    }
    if(id==queue[flag])
    {
        timer=time[flag];
        ++flag;
    }
    else
    {
        timer=0;
        flag=0;
    }
}

void skillslot::clear()
{
    flag=0;
    timer=0;
}

void skillslot::update()
{
    if(timer==0)
        flag=0;
    if(timer!=0)
        --timer;
}

bool skillslot::isAct()
{
    if(flag==len&&timer==0)
        return true;
    return false;
}

int skillslot::getPri()
{
    return priority;
}

skillslot::skillslot()
{
    for(int i=0;i<skill_len;i++)
    {
        queue[i]=0;
    }
    empty=1;
    len=0;
    priority=-1;
    timer=0;
    flag=0;
}

skillslot::skillslot(int id)
{
    this->id=id;
    for(int i=0;i<skill_len;i++)
    {
        queue[i]=0;
    }
    empty=0;
    timer=0;
    flag=0;
    switch(id)
    {
    case 0:
        len=1;
        priority=1;
        queue[0]=Qt::Key_J;time[0]=0;
        break;
    case 1:
        len=1;
        priority=1;
        queue[0]=Qt::Key_K;time[0]=0;
        break;
    case 2:
        len=1;
        priority=1;
        queue[0]=Qt::Key_L;time[0]=0;
        break;
    case 3:
        len=1;
        priority=1;
        queue[0]=Qt::Key_U;time[0]=0;
        break;
    case 4:
        len=1;
        priority=1;
        queue[0]=Qt::Key_I;time[0]=0;
        break;
    case 5:
        len=1;
        priority=1;
        queue[0]=Qt::Key_O;time[0]=0;
        break;
    //*********************priority  2*************************//
    case 6:
        len=3;
        priority=2;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Right;time[1]=3;       //↓→J
        queue[2]=Qt::Key_J;time[2]=3;
        break;
    case 7:
        len=3;
        priority=2;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Left;time[1]=3;        //↓←J
        queue[2]=Qt::Key_J;time[2]=3;
        break;
    case 8:
        len=3;
        priority=2;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Right;time[1]=3;       //↓→K
        queue[2]=Qt::Key_K;time[2]=3;
        break;
    case 9:
        len=3;
        priority=2;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Left;time[1]=3;        //↓←K
        queue[2]=Qt::Key_K;time[2]=3;
        break;
    case 10:
        len=3;
        priority=2;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Right;time[1]=3;       //↓→U
        queue[2]=Qt::Key_U;time[2]=3;
        break;
    case 11:
        len=3;
        priority=2;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Left;time[1]=3;        //↓←U
        queue[2]=Qt::Key_U;time[2]=3;
        break;
    case 12:
        len=3;
        priority=2;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Right;time[1]=3;       //↓→I
        queue[2]=Qt::Key_I;time[2]=3;
        break;
    case 13:
        len=3;
        priority=2;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Left;time[1]=3;        //↓←I
        queue[2]=Qt::Key_I;time[2]=3;
        break;
    //*******************charactor 0**************************//
    case 14:
        len=4;
        priority=3;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Right;time[1]=3;        //↓→↑J
        queue[2]=Qt::Key_Up;time[2]=3;
        queue[3]=Qt::Key_J;time[3]=2;
        break;
    }
}

void player::push(int key)
{
    for(int i=0;i<skill_num;i++)
    {
        skills[i].push(key);
    }
}

int player::Act()
{
    int nact=-1,npri=0;
    for(int i=0;i<skill_num;i++)
    {
        if(skills[i].isAct()&&skills[i].getPri()>npri)
        {
            nact=i;
            npri=skills[i].getPri();
        }
    }
    if(nact!=-1)
    {
        for(int i=0;i<skill_num;i++)
        {
            if(i!=nact&&npri>skills[i].getPri())
                skills[i].clear();
        }
    }
    return nact;
}

void player::update()
{
    for(int i=0;i<skill_num;i++)
    {
        if(skills[i].getPri()<=0)
            continue;
        skills[i].update();
    }
}

player::player()
{

}

player::player(int id)
{
    //skills[used++]=skillslot();
    int used=3;
    skills[used+0]=skillslot(0); //basic JKLUIO
    skills[used+1]=skillslot(1);
    skills[used+2]=skillslot(2);
    skills[used+3]=skillslot(3);
    skills[used+4]=skillslot(4);
    skills[used+5]=skillslot(5);
    used+=6;
    switch(id)  //basic ↓→J things
    {
    case 0:
    case 1:
        skills[used++]=skillslot(6);
        skills[used++]=skillslot(7);
        skills[used++]=skillslot(8);
        skills[used++]=skillslot(9);
        skills[used++]=skillslot(10);
        skills[used++]=skillslot(11);
        skills[used++]=skillslot(12);
        skills[used++]=skillslot(13);
    }
    switch(id)
    {
    case 0:
        skills[used++]=skillslot(14);
        break;
    case 1:

        break;
    }
}
