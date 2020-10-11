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
    QString img;
public:
    void get(int& x, int& y, int& w, int& h, QString &timg);

    Hitbox();
    Hitbox(int cha, int ski, int fri,bool hasimg);
};

#define ActionFrame 50

class Action
{
    bool aironly;
    bool jump;
    float move;
    int fly;

    int loop;
    int next;

    int damage[ActionFrame];
    Hitbox hits[ActionFrame];
    Hitbox body[ActionFrame];
    short hitstime[ActionFrame];

public:  
    bool isAirOnly();
    bool isJump();
    int get_move();

    int start();
    int get_next();
    int get_damage(int time);
    Hitbox get_hitbox(int time);
    Hitbox get_body(int time);

    Action();
    Action(int,int);
};

#define actnum 40

class Character
{
    int health;
    int status;
    int hittype;
    bool in_air;
public:
    int act_doing;
    int act_pri;
    int act_timer;

    Action acts[actnum];

//public:

    int get_health();
    int get_status();

    Hitbox get_hitbox();
    Hitbox get_atabox();
    int get_damage();

    void set_health(int);
    void set_status(int);
    void set_in_air(bool);
    bool do_act(int id,int pri);

    void update();

    Character();
    Character(int);
};

#define Fly_frame 10

class FlyObject
{
    friend class FightObject;

    int damage;
    bool disap;
    int x,y;
    int v_x,v_y;

    int loop;
    int timer;

    Hitbox hit[Fly_frame];
public:
    FlyObject* pre;
    FlyObject* next;

    void get_xy(int &x,int &y);
    Hitbox get_hit();
    bool isDis();

    void update();

    FlyObject(int x, int y, int id, bool right);
};

class FightObject
{

    int w,h;

public:
    Character player[2];
    FlyObject* flyhead;

    void flydelete(FlyObject*);
    void flyupdate();
    void flyadd(int x, int y, int id,bool isright);

    FightObject(int,int,int,int);//w h player1 player2
};

#endif // FIGHTOBJECT_H
