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
        pl[0].push(trans(id,face));
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        pl[1].push(trans(id,face));
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
    if(face)//W is left
    {
        switch(id)
        {
        case Qt::Key_W:
        case Qt::Key_Up:
            return Qt::Key_W;
        case Qt::Key_A:
        case Qt::Key_Left:
            return Qt::Key_A;
        case Qt::Key_D:
        case Qt::Key_Right:
            return Qt::Key_D;
        case Qt::Key_S:
        case Qt::Key_Down:
            return Qt::Key_S;
        default:
            qDebug()<<"Error Keytrans "<<id;
            return 0;
        }
    }
    else
    {
        switch(id)
        {
        case Qt::Key_W:
        case Qt::Key_Up:
            return Qt::Key_W;
        case Qt::Key_A:
        case Qt::Key_Left:
            return Qt::Key_D;//here
        case Qt::Key_D:
        case Qt::Key_Right:
            return Qt::Key_A;//and here
        case Qt::Key_S:
        case Qt::Key_Down:
            return Qt::Key_S;
        default:
            qDebug()<<"Error Keytrans "<<id;
            return 0;
        }
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
        len=3;
        priority=2;
        queue[0]=Qt::Key_A;time[0]=3;
        queue[1]=Qt::Key_D;time[1]=3;
        queue[2]=Qt::Key_W;time[2]=3;
        break;
    case 1:
        len=3;
        priority=2;
        queue[0]=Qt::Key_D;time[0]=3;
        queue[1]=Qt::Key_S;time[1]=3;
        queue[2]=Qt::Key_W;time[2]=3;
        break;
    case 2:
        len=4;
        priority=3;
        queue[0]=Qt::Key_A;time[0]=3;
        queue[1]=Qt::Key_D;time[1]=3;
        queue[2]=Qt::Key_W;time[2]=3;
        queue[3]=Qt::Key_A;time[3]=0;
        break;
    case 3:
        len=1;
        priority=1;
        queue[0]=Qt::Key_A;time[0]=0;
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
    switch(id)
    {
    case 0:
        skills[0]=skillslot(0);
        skills[1]=skillslot(2);
        skills[2]=skillslot(3);
        break;
    case 1:
        skills[0]=skillslot(1);
        break;
    }
}
