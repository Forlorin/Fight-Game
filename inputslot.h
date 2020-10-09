#ifndef INPUTSLOT_H
#define INPUTSLOT_H

#include <QKeyEvent>

class Widge;

#define skill_len 20

class skillslot
{
public:
    bool empty;
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
    bool isAct();
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
    int Act();
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
    void getSt(int&,int&);

    static int trans(int, bool);

    inputslot(int a,int b);
};

#endif // INPUTSLOT_H
