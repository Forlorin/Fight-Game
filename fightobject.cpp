#include "fightobject.h"



void FightObject::flydelete(FlyObject *np)
{
    if(np==nullptr)
    {
        qDebug()<<"delete nullptr! (flyobject)";
        return;
    }
    if(np->pre==nullptr)
    {
        flyhead=np->next;
        delete np;
    }
    else
    {
        np->pre->next=np->next;
        delete np;
    }
}

void FightObject::flyupdate()
{
    return;
    //to be continue
    FlyObject* tp=flyhead;
    while(tp!=nullptr)
    {
        int dx,dy,dw,dh;
        tp->hit.get(dx,dy,dw,dh);
        if(tp->x+dx>this->w||tp->x+dx+dw<0)
        {
            tp=tp->next;
            flydelete(tp);
        }
    }
}

void FightObject::flyadd(int, int, int)
{

}

FightObject::FightObject(int a,int b,int c,int d)
{
    w=c;
    h=d;
    player[0]=Character(a);
    player[1]=Character(b);
    flyhead=nullptr;
}

void Hitbox::get(int& tx, int& ty, int& tw, int& th)
{
    tx=dx;
    ty=dy;
    tw=w;
    th=h;
}

Hitbox::Hitbox()
{
    dx=0;
    dy=0;
    w=0;
    h=0;
}

Hitbox::Hitbox(int tx, int ty, int tw, int th)
{
    dx=tx;
    dy=ty;
    w=tw;
    h=th;
}

bool Action::isAirOnly()
{
    return aironly;
}

int Action::start()
{
    return loop;
}

int Action::get_hittype()
{
    return hittype;
}

Action::Action()
{

}

Action::Action(int id)
{
    switch(id)
    {
    case 0:
        hittype=0;
        aironly=0;
        loop=-1;
        //img
        hitstime[0]=1;
    }
}

int Character::get_health()
{
    return health;
}

int Character::get_status()
{
    return status;
}

Hitbox Character::get_hitbox()
{
    return hit[acts[act_doing].get_hittype()];
}

void Character::set_health(int h)
{
    health=h;
}

void Character::set_status(int s)
{
    status=s;
}

bool Character::do_act(int id)
{
    if(status==0&&acts[id].isAirOnly()==in_air)
    {
        act_doing=id;
        act_timer=acts[id].start();
        return true;
    }
    return false;
}

void Character::set_in_air(bool s)
{
    in_air=s;
}

void Character::update()
{
    Action* nact=&acts[act_doing];
    if(nact->start()>0)
    {
        if(act_timer==0)
        {
            status=0;
            do_act(0);
            return;
        }
        act_timer--;
    }
    else
    {
        act_timer++;
        if(act_timer>=0)
        {
            act_timer=nact->start();
        }
    }
}

Character::Character()
{

}

Character::Character(int id)
{
    //switch(id)
    {

    }
}

FlyObject::FlyObject(int x, int y, int id)
{
    this->x=x;
    this->y=y;
    pre=nullptr;
    next=nullptr;
    //switch(id)
    {

    }
}
