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
    FlyObject* tp=flyhead;
    while(tp!=nullptr)
    {
        int dx,dy,dw,dh;
        tp->x+=tp->v_x;
        tp->y+=tp->v_y;//position
        tp->hit.get(dx,dy,dw,dh);
        if(tp->x+dx>this->w||tp->x+dx+dw<0)
        {
            tp=tp->next;
            flydelete(tp);
        }
        else if(tp->y+dy>this->h||tp->y+dy+dh<0)//y
        {
            tp=tp->next;
            flydelete(tp);
        }
    }
}

void FightObject::flyadd(int x, int y, int id,bool right)
{
    FlyObject* nf=new FlyObject(x,y,id,right);
    flyhead->pre=nf;
    nf->next=flyhead;
    flyhead=nf;
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

int Action::get_damage()
{
    return damage;
}

int Action::get_hittype()
{
    return hittype;
}

QString Action::get_img(int time)
{
    int temp=0;
    while(time>hitstime[temp])
    {
        time-=hitstime[temp];
        temp++;
    }
    return img[temp];
}

Hitbox Action::get_hitbox(int time)
{
    int temp=0;
    while(time>hitstime[temp])
    {
        time-=hitstime[temp];
        temp++;
    }
    return hits[temp];
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
        loop=1;
        img[0]="";
        hits[0]=Hitbox(-5,-5,10,10);
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

QString Character::get_img()
{
    return acts[act_doing].get_img(act_timer>0?act_timer:-act_timer);
}

Hitbox Character::get_atabox()
{
    return acts[act_doing].get_hitbox(act_timer>0?act_timer:-act_timer);
}

void Character::set_health(int h)
{
    health=h;
}

void Character::set_status(int s)
{
    status=s;
}

bool Character::do_act(int id,int pri)
{
    if(status==0&&acts[id].isAirOnly()==in_air&&pri>act_pri)
    {
        act_doing=id;
        act_pri=pri;
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
    int st=nact->start();
    if(st>0)
    {
        if(act_timer==st)
        {
            status=0;
            if(!do_act(0,-1))
                do_act(1,-1);
            return;
        }
        act_timer++;
    }
    else
    {
        if(act_timer==st)
        {
            act_timer=0;
            return;
        }
        act_timer--;
    }
}

Character::Character()
{

}

Character::Character(int id)
{
    health=100;
    status=0;
    hittype=0;
    in_air=0;
    act_doing=0;
    act_pri=0;
    act_timer=0;

    switch(id)
    {
    case 0:;
    }
}

FlyObject::FlyObject(int x, int y, int id,bool right)
{
    this->x=x;
    this->y=y;
    pre=nullptr;
    next=nullptr;
    switch(id)
    {
    case 0: damage=1;
            v_x=1;
            v_y=0;
            img="";
            hit=Hitbox(-5,-5,10,10);
            break;
    }
    if(!right)
        v_x=-v_x;
}
