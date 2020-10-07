#ifndef FIGHTOBJECT_H
#define FIGHTOBJECT_H

#include <QString>
#include <QDebug>

class Character;
class Hitbox;
class Action;
class FlyObject;

class Hitbox
{
    int dx,dy;
    int w,h;
public:
    void get(int& x,int& y,int& w,int& h);

    Hitbox();
    Hitbox(int x,int y,int w,int h);
};

#define ActionFrame 50

class Action
{
    int hittype;
    bool aironly;
    int damage;
    int loop;
    QString img[ActionFrame];
    Hitbox hits[ActionFrame];
    short hitstime[ActionFrame];
public:
    bool isAirOnly();
    int start();
    int get_damage();
    int get_hittype();
    QString get_img(int);
    Hitbox get_hitbox(int);

    Action();
    Action(int);
};

#define actnum 20

class Character
{
    int health;
    int status;
    int hittype;
    bool in_air;
    Action acts[actnum];
    int act_doing;
    int act_pri;
    int act_timer;
    Hitbox hit[2];
public:
    int get_health();
    int get_status();
    Hitbox get_hitbox();
    QString get_img();
    Hitbox get_atabox();

    void set_health(int);
    void set_status(int);
    bool do_act(int id,int pri);
    void set_in_air(bool);

    void update();

    Character();
    Character(int);
};

class FlyObject
{
    friend class FightObject;

    QString img;
    int damage;
    int x,y;
    int v_x,v_y;
    Hitbox hit;
public:
    FlyObject* pre;
    FlyObject* next;

    FlyObject(int x,int y,int id);
};

class FightObject
{
    int w,h;
public:
    Character player[2];
    FlyObject* flyhead;

    void flydelete(FlyObject*);
    void flyupdate();
    void flyadd(int vx,int vy,int id);

    FightObject(int,int,int,int);
};

#endif // FIGHTOBJECT_H
