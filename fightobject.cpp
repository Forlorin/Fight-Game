#include "fightobject.h"
#include <QImage>
#include <QDir>

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
    QString tstr;
    while(tp!=nullptr)
    {
        tp->update();
        int x,y,dx,dy,dw,dh;
        tp->get_hit().get(dx,dy,dw,dh,tstr);
        tp->get_xy(x,y);
        if(x+dx>this->w||x+dx+dw<0)
        {
            tp=tp->next;
            flydelete(tp);
        }
        else if(y+dy>this->h||y+dy+dh<0)//y
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
    w=a;
    h=b;
    player[0]=Character(c);
    player[1]=Character(d);
    flyhead=nullptr;
}

void Hitbox::get(int& tx, int& ty, int& tw, int& th, QString& timg)
{
    tx=dx;
    ty=dy;
    tw=w;
    th=h;
    timg=img;
}

Hitbox::Hitbox()
{
    dx=0;
    dy=0;
    w=0;
    h=0;
}

Hitbox::Hitbox(int cha,int ski,int fri,bool hasimg)
{
    if(cha==-1)
    {
        dx=dy=w=h=0;
        img="";
        return;
    }

    QString name=":/";
    switch(cha)
    {
    case 0:
        name+="Aura/Aura by Crucifix_";
        break;
    }
    img=name+QString::number(ski)+QString("-")+QString::number(fri)+QString(".png");
    QImage imgs(img);
    dx=-imgs.width()/2;
    h=dy=imgs.height();
    w=imgs.width();

    if(!hasimg)
        img="";

    int num0[16]={8,7,1,0,-1};
    int num200[8]={0,10,30,30,30,25,25,20};
    int num230[11]={5,5,7,7,0,-5,18,22,5,5,0};
    int num220[15]={10,14,13,19,23,   28,41,45,46,46,   47,29,29,16,13};
    int num210[13]={0,3,0,-3,-10,-17,13,16,7,7,5,5,7};
    int num240[8]={0,10,10,20,20,20,23,25};
    int num400[6]={0,10,20,15,3,0};
    int num420[8]={3,12,20,25,26,19,17,5};
    int num943[8]={0,-1,-2,-3,-4,12,12,12};
    int num1000[10]={4,-1,-2,-2,0,4,3,2,-2,4};
    int num1010[2][19]={
        {78,70,51,35,29,27,27,27,27,21,21,21,21,21,21,21,21,21,21},
        {33,44,63,76,81,81,81,81,81,92,92,92,92,92,92,92,92,92,92}
    };
    int num600[2][7]={
        {17,17,-42,-42,-42,-14,-14},
        {-10,0,15,15,15,12,12}
    };
    int num610[2][5]={
        {0,0,0,0,5},
        {10,10,12,0,-20}
    };
    switch(cha)
    {
    case 0:     //Aura
        switch(ski)
        {
        case 0:
            dx+=num0[fri];
            break;
        case 5000:
            switch(fri)
            {
            case 30:
                dx-=6;
                break;
            }
            break;
        case 200:
            dx+=num200[fri];
            break;
        case 230:
            dx+=num230[fri];
            break;
        case 220:
            dx+=num220[fri];
            break;
        case 210:
            dx+=num210[fri];
            break;
        case 240:
            dx+=num240[fri];
            break;
        case 400:
            dx+=num400[fri];
            break;
        case 420:
            dx+=num420[fri];
            break;
        case 943:
            dx+=num943[fri];
            break;
        case 1000:
            dx+=num1000[fri];
            break;
        case 1010:
            dy+=num1010[0][fri];
            dx+=num1010[1][fri];
            break;
        case 600:
            dy+=num600[0][fri];
            dx+=num600[1][fri];
            break;
        case 610:
            dy+=num610[0][fri];
            dx+=num610[1][fri];
            break;
        }
        break;
    }

    //qDebug()<<img<<' '<<dx<<' '<<dy<<' '<<w<<' '<<h;
}



bool Action::isAirOnly()
{
    return aironly;
}

bool Action::isJump()
{
    return jump;
}

float Action::get_move()
{
    return move;
}

int Action::start()
{
    return loop;
}

int Action::get_next()
{
    return next;
}

int Action::get_force()
{
    return force;
}

int Action::get_damage(int time)
{
    int temp=0;
    while(time>hitstime[temp])
    {
        time-=hitstime[temp];
        temp++;
    }
    return damage[temp];
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

Hitbox Action::get_body(int time)
{
    int temp=0;
    while(time>hitstime[temp])
    {
        time-=hitstime[temp];
        temp++;
    }
    return body[temp];
}

Action::Action()
{

}

Action::Action(int cha, int ski)
{
    aironly=0;
    //qDebug()<<"Build "<<QString::number(ski);
    jump=0;
    move=0;
    next=1;
    fly=0;
    force=0;

    int no_hit=3;

    switch(cha)
    {
    case 0://Aura
        int st=0;
        int len=0;
        int tdam=0;
        if(ski<=12||ski==24||ski==9||ski==10||ski==12)
            no_hit=100;
        switch(ski)
        {
        case 0:         //start
            len=5;
            loop=len;
            next=1;
            ski=0;
            break;
        case 1:         //stand
            st=5;
            len=11;
            loop=-len;
            ski=0;
            break;
        case 2:         //start squat
            len=3;
            loop=len;
            next=3;
            ski=10;
            break;
        case 3:         //squat
            len=8;
            loop=-len;
            ski=11;
            break;
        case 4:         //move forward
            len=10;
            move=1;
            loop=-len;
            ski=20;
            break;
        case 5:         //move backward
            len=6;
            move=1;
            loop=-len;
            ski=21;
            break;
        case 6:         //jump
            len=7;
            move=0.5;
            loop=len;
            ski=41;
            next=24;
            jump=1;
            break;
        case 24:         //falling
            len=1;
            move=0.5;
            aironly=1;
            loop=-len;
            ski=41;
            st=7;
            break;
        case 7:         //dash forward
            len=8;
            loop=len;
            ski=100;
            move=2;
            break;
        case 8:         //dash backward
            len=4;
            loop=len;
            ski=105;
            move=2;
            break;
        case 9:         //get hit
            len=4;
            loop=len;
            ski=5000;
            break;
        case 10:        //get down
            len=3;
            loop=len;
            ski=5100;
            next=11;
            break;
        case 11:        //on the floor
            len=1;
            loop=-len;
            ski=5110;
            break;
        case 12:        //get up
            len=3;
            loop=len;
            ski=5120;
            break;
        case 13:        //punch
            len=8;
            loop=len;
            ski=200;
            no_hit=2;
            tdam=4;
            break;
        case 14:        //kick
            len=11;
            loop=len;
            ski=230;
            no_hit=1;
            tdam=6;
            break;
        case 15:        //heavy punch
            len=15;
            loop=len;
            ski=220;
            tdam=7;
            break;
        case 16:        //heavy kick
            len=13;
            loop=len;
            ski=210;
            tdam=7;
            break;
        case 17:        //upper kick
            len=8;
            loop=len;
            ski=240;
            force=21;
            no_hit=5;
            tdam=8;
            break;
        case 18:        //squat kick
            len=6;
            loop=len;
            ski=400;
            next=3;
            tdam=6;
            break;
        case 19:        //floor kick
            len=7;
            loop=len;
            move=2;
            ski=410;
            next=3;
            tdam=7;
            break;
        case 20:        //hair attack
            len=8;
            loop=len;
            ski=420;
            next=3;
            tdam=7;
            break;
        case 21:        //ice fly
            len=8;
            loop=len;
            ski=943;
            fly=1;
            break;
        case 22:        //blow ice
            len=10;     //special
            loop=len;
            ski=1000;
            no_hit=0;
            tdam=1;
            force=2;
            break;
        case 23:        //upper punch
            len=9;      //special
            loop=len;
            ski=1500;
            next=1;
            force=21;
            tdam=8;
            break;
        case 25:        //flying punch
            len=7;
            aironly=1;
            move=0.5;
            loop=len;
            ski=600;
            next=24;
            tdam=5;
            break;
        case 26:
            len=5;      //flying kick
            aironly=1;
            loop=len;
            move=0.5;
            ski=610;
            next=24;
            tdam=8;
            break;
        }
        for(int i=st;i<st+len;i++)
        {
            if(!i<no_hit)
                damage[i]=tdam;
            else
                damage[i]=0;
            //qDebug()<<QString::number(i)<<":";
            if(!(i<no_hit))
                hits[i-st]=Hitbox(0,ski,i,0);
            else
                hits[i-st]=Hitbox(-1,0,0,0);
            body[i-st]=Hitbox(0,ski,i,1);
            hitstime[i]=1;
        }
        if(force==0&&no_hit!=100)
            force=len-no_hit;
        force=force>0?force:1;
        switch(ski) //special deal
        {
        default:
            break;
        case 11:
            loop=-32;
            for(int i=8;i<-loop;i++)
            {
                body[i]=Hitbox(0,ski,15-i,1);
            }
            for(int i=0;i<-loop;i++)
            {
                hitstime[i]=2;
            }
            break;
        case 20:
            loop=2*loop;
            for(int i=0;i<-loop;i++)
            {
                hitstime[i]=2;
            }
            break;
        case 21:
            loop=2*loop;
            for(int i=0;i<-loop;i++)
            {
                hitstime[i]=2;
            }
            break;
        case 24:
            loop=3*loop;
            for(int i=0;i<loop;i++)
            {
                hitstime[i]=3;
            }
            break;
        case 105:
            hitstime[1]=8;
            break;
        case 5000:
            loop+=100;
            for(int i=0;i<4;i++)
            {
                body[i]=Hitbox(0,ski,10*i,1);
            }
            hitstime[3]=100;
            break;
        case 5100:
            loop=2*loop;
            for(int i=0;i<loop;i++)
            {
                hitstime[i]=2;
            }
            break;
        case 5120:
            loop=2*loop;
            for(int i=0;i<loop;i++)
            {
                hitstime[i]=2;
            }
            break;
        case 400:
            loop=2*loop;
            for(int i=0;i<loop;i++)
            {
                hitstime[i]=2;
            }
            break;
        case 410:
            loop=2*loop;
            for(int i=0;i<loop;i++)
            {
                hitstime[i]=2;
            }
            break;
        case 420:
            loop=loop+1;
            for(int i=0;i<1;i++)
            {
                hitstime[i]=2;
            }
            break;
        case 1000:
            loop=19;
            for(int i=10;i<loop;i++)
            {
                body[i]=Hitbox(0,ski,9,1);
            }
            for(int i=0;i<loop;i++)
            {
                hits[i]=Hitbox(0,1010,i,1);
            }
            break;
        case 1500:
            for(int i=0;i<loop;i++)
            {
                hits[i]=Hitbox(0,1510,i,1);
            }
            break;
        }
        break;
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
    //qDebug()<<act_doing<<' '<<act_pri;
    return acts[act_doing].get_body(act_timer);
}

Hitbox Character::get_atabox()
{
    return acts[act_doing].get_hitbox(act_timer);
}

int Character::get_damage()
{
    return acts[act_doing].get_damage(act_timer);
}

Action Character::get_action()
{
    return acts[act_doing];
}

bool Character::beHit(int force)
{
    if(status!=0||force<=0)
    {
        return false;
    }
    if(force<=20)//normal
    {
        hit_timer=force;
        do_act(9,15);
        status=2;
        inv_time=0;
    }
    else
    {
        hit_timer=force;
        do_act(10,15);
        status=2;
        inv_time=-5;
    }
    return true;
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
    if(id<0||id>actnum)
        return false;
    if(id==25)
    {
        qDebug()<<"?";
    }
    if(status==0||status==-1||pri<=-10||pri>100)
    {
        if(!acts[id].isAirOnly()==in_air&&pri>-10&&pri<15)
             return false;
        if(!(pri>act_pri||(pri<-1&&act_pri>0)||(id<=5&&(act_doing<=5||act_doing==24)&&id!=act_doing)||pri<=-10||pri>100))
            return false;
        if(id==0&&act_doing==1&&pri>-10)
            return false;
        if(id==2&&act_doing==3&&pri>-10)
            return false;
        qDebug()<<id<<" succeed";
        act_doing=id;
        act_pri=pri;
        if(pri==-10)
            act_pri=15;
        if(pri<-100||pri>100)
            act_pri=pri>100?pri-100:pri+100;
        act_timer=0;

        return true;
    }
    qDebug()<<id<<" fail";
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
            act_pri=-2;
            if(do_act(nact->get_next(),-101))
                 return;
            else if(do_act(1,-1))
                 return;                // 1 stand
            else
                  do_act(24,-1);         // 24 falling
            return;
        }
        act_timer++;
    }
    else
    {
        if(act_pri==15)
            act_pri=-2;
        if(act_timer==-st)
        {
            act_timer=0;
            return;
        }
        act_timer++;
    }
    if(hit_timer==4)
    {
        if(act_doing==11)
        {
            act_doing=12;
            act_pri=-1;
            act_timer=0;
        }
        else
            status=1;
    }
    else if(hit_timer==0)
    {
        status=-1;
        act_doing=1;
        act_pri=-1;
        act_timer=0;
    }
    if(hit_timer==inv_time)
    {
        status=0;
    }
    if(hit_timer>=-10)
        --hit_timer;
}

Character::Character()
{

}

Character::Character(int id)
{
    health=100;
    status=0;
    in_air=0;
    hit_timer=0;
    act_doing=0;
    act_pri=0;
    act_timer=0;
    hit_timer=-1;
    inv_time=0;

    switch(id)
    {
    case 0: //Aura
        for(int i=0;i<=26;i++)
        {
            acts[i]=Action(0,i);
        }
        break;
    }
}



void FlyObject::get_xy(int &x, int &y)
{
    x=this->x;
    y=this->y;
}

Hitbox FlyObject::get_hit()
{
    return hit[timer];
}

bool FlyObject::isDis()
{
    return disap;
}

void FlyObject::update()
{
    timer++;
    if(timer==loop)
        timer=0;
}

FlyObject::FlyObject(int x, int y, int id,bool right)
{
    this->x=x;
    this->y=y;
    pre=nullptr;
    next=nullptr;
    timer=0;
    if(!right)
        v_x=-v_x;
    switch(id)
    {
    case 1://Aura
        disap=1;
        damage=2;
        loop=4;
        for(int i=0;i<loop;i++)
            hit[i]=Hitbox(0,940,i,1);
        break;
    }
}
