#ifndef INPUTSLOT_H
#define INPUTSLOT_H

#include <QKeyEvent>

class Widge;

#define skill_len 20

class skillslot
{
public:
    bool empty;
    int status;         //0 any  1 stand  2 in-air  3  squat   4  right   5   left
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
    int Act(int stat);
    void update();
    player();
    player(int);
};

class inputslot
{
public:
    player pl[2];
//public:
    void push(int, bool);
    void update();
    void getSt(int&,int&,int);

    static int trans(int, bool);

    inputslot(int a,int b);
};

#endif // INPUTSLOT_H
