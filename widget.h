#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <inputslot.h>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <fightobject.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:

    int nact;
    int nstat;
    int frime;

    FightObject* fight;
    inputslot input;

    int tottime;

    int inputtemp[20];
    int skillrec[2][20];

    int ndx,ndy;

    QLabel* cha[2][2];

    QPushButton* nextact;
    QPushButton* actit;
    QPushButton* ctime;
    QPushButton* cx[2];
    QPushButton* cy[2];
    QPushButton* pbut;

    QLabel* La[2];
    QLabel* Lskill[2];
    QLabel* tempslot;
    QLabel* Ltime;

    int timer;  

    explicit Widget(QWidget *parent = 0);

    void timerEvent(QTimerEvent *);

    void keyPressEvent(QKeyEvent *);

    void viewupdate();

    ~Widget();

private:
    Ui::Widget *ui;
public slots:
    void changeact();
    void changetime();
    void changexy(int, int);
    void act();
    void pac();
};

#endif // WIDGET_H
