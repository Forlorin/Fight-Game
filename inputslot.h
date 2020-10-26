#ifndef INPUTSLOT_H
#define INPUTSLOT_H

#include <QKeyEvent>

class Widge;

#define skill_len 20

class skillslot
{
public:
    bool empty;
    int status;         //0 any  1 stand  2 in-air  3  squat   4  forward  5   backward
    int queue[skill_len];
    int time[skill_len];
    int flag;
    int len;
    int priority;
    int timer;
    int id;
//public:
    void push(int);
    void clear();
    void update();
    int get_id();
    bool isAct(int stat);
    int getPri();
    skillslot();
    skillslot(int);
};

#define skill_num 40

class player
{
public:
    skillslot skills[skill_num];
//public:
    void push(int);
    void Act(int stat, int &id, int &pri);
    void update();
    player();
    player(int);
};

class inputslot
{
public:
    player pl[2];
//public:
    void push(int, bool);//int: key   bool:  player0 is left?
    void update();          //every frame need to be used
    void getSt(int &a, int &b, int &pa, int &pb, int s0, int s1);
    //player0 id  pri   player1  id pri
    //status 0            status 1

    static int trans(int, bool);

    inputslot(int a,int b);
};

#endif // INPUTSLOT_H
