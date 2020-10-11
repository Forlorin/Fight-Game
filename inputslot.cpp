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

void inputslot::getSt(int &a, int &b, int &pa, int &pb,int s0,int s1)
{
    pl[0].Act(s0,a,pa);
    pl[1].Act(s1,b,pb);
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

int skillslot::get_id()
{
    return id;
}

bool skillslot::isAct(int s)
{
    if(flag==len&&timer==0&&(status==0||s==0||s==status))
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
    status=0;       //0 any  1 stand  2 in-air  3  squat   4  right   5   left
    switch(id)//basic
    {
    case 0:
        len=0;          //stand
        priority=-1;
        status=1;
        this->id=0;
        break;
    case 1:
        len=0;          //squat
        priority=-1;
        status=3;
        this->id=2;
        break;
    case 2:
        len=0;
        priority=-1;
        status=4;       //move forward
        this->id=4;
        break;
    case 3:
        len=0;
        priority=-1;
        status=5;       //move forward
        this->id=5;
        break;
    case 4:
        len=1;          //jump
        priority=1;
        status=1;
        this->id=6;
        queue[0]=Qt::Key_Up;time[0]=2;
        break;
    case 5:
        len=1;
        priority=1;     //dash forward
        status=4;
        this->id=7;
        queue[0]=Qt::Key_L;time[0]=0;
        break;
    case 6:
        len=1;
        priority=1;     //dash backward
        status=5;
        this->id=8;
        queue[0]=Qt::Key_L;time[0]=0;
        break;
    case 7:
        len=1;
        priority=1;     //punch
        status=0;
        this->id=13;
        queue[0]=Qt::Key_J;time[0]=0;
        break;
    case 8:
        len=1;
        priority=1;     //kick
        status=0;
        this->id=14;
        queue[0]=Qt::Key_K;time[0]=0;
        break;
    case 9:
        len=1;
        priority=1;     //heavy punch
        status=0;
        this->id=15;
        queue[0]=Qt::Key_U;time[0]=0;
        break;
    case 10:
        len=1;
        priority=1;     //heavy kick
        status=0;
        this->id=16;
        queue[0]=Qt::Key_I;time[0]=0;
        break;
    default:
        break;
    }

    //*************** Aura *********************//
    if(id>=100&&id<200)
    switch(id)
    {
    case 101:
        len=2;          //upper kick      1
        priority=2;
        status=1;
        this->id=17;
        queue[0]=Qt::Key_Up;time[0]=2;
        queue[1]=Qt::Key_K;time[1]=0;
        break;
    case 102:
        len=2;          //upper kick      2
        priority=2;
        status=1;
        this->id=17;
        queue[0]=Qt::Key_Up;time[0]=2;
        queue[1]=Qt::Key_I;time[1]=0;
        break;
    case 103:
        len=1;
        priority=2;    //squat kick    1
        status=3;
        this->id=18;
        queue[0]=Qt::Key_K;time[0]=0;
        break;
    case 104:
        len=1;
        priority=2;    //squat kick    2
        status=3;
        this->id=18;
        queue[0]=Qt::Key_I;time[0]=0;
        break;
    case 105:
        len=3;
        priority=2;    //floor kick
        status=4;
        this->id=19;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Right;time[1]=3;
        queue[2]=Qt::Key_K;time[2]=0;
        break;
    case 106:
        len=4;
        priority=2;    //hair attack
        status=1;       // attention!  in-air not equal to press up
        this->id=20;
        queue[0]=Qt::Key_Left;time[0]=3;
        queue[1]=Qt::Key_Down;time[1]=3;
        queue[2]=Qt::Key_Right;time[2]=3;
        queue[3]=Qt::Key_U;time[3]=0;
        break;
    case 107:
        len=3;
        priority=2;    //ice fly
        status=1;
        this->id=21;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Right;time[1]=3;
        queue[2]=Qt::Key_J;time[2]=0;
        break;
    case 108:
        len=5;
        priority=3;    //blow ice    1
        status=1;
        this->id=22;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Right;time[1]=3;
        queue[2]=Qt::Key_Down;time[2]=3;
        queue[3]=Qt::Key_Right;time[3]=3;
        queue[4]=Qt::Key_J;time[4]=0;
        break;
    case 109:
        len=5;
        priority=3;    //blow ice    2
        status=4;
        this->id=22;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Right;time[1]=3;
        queue[2]=Qt::Key_Down;time[2]=3;
        queue[3]=Qt::Key_Right;time[3]=3;
        queue[4]=Qt::Key_J;time[4]=0;
        break;
    case 110:
        len=4;
        priority=2;    //upper punch
        status=1;       // attention!  in-air not equal to press up
        this->id=23;
        queue[0]=Qt::Key_Down;time[0]=3;
        queue[1]=Qt::Key_Right;time[1]=3;
        queue[2]=Qt::Key_Up;time[2]=3;
        queue[3]=Qt::Key_J;time[3]=0;
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

void player::Act(int stat,int &id,int &pri)
{
    int nact=-1,npri=-10;
    for(int i=0;i<skill_num;i++)
    {
        if(skills[i].empty)
            continue;
        skillslot* tslot=&skills[i];
        if(skills[i].isAct(stat)&&skills[i].getPri()>npri)
        {
            nact=i;
            npri=skills[i].getPri();
        }
    }
    if(nact!=-1)
    {
        if(nact>4)
        {
            for(int i=0;i<skill_num;i++)
            {
                if(i!=nact&&npri>skills[i].getPri())
                    skills[i].clear();
            }
        }
        id=skills[nact].get_id();
        pri=npri;
    }
    else
    {
        id=-1;
        pri=-1;
    }
}

void player::update()
{
    for(int i=0;i<skill_num;i++)
    {
        if(skills[i].empty)
            continue;
        skills[i].update();
    }
}

player::player()
{

}

player::player(int id)
{
    int used=0;
    for(int i=0;i<11;i++)
    {
        skills[i]=skillslot(i);//basic
    }
    used+=11;
    switch(id)
    {
    case 0:     //Aura
        for(int i=1;i<=10;i++)
        {
            skills[used++]=skillslot(100+i);
        }
        break;
    }
}
