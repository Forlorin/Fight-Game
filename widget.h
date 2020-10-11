#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <inputslot.h>
#include <QDebug>
#include <QLabel>
#include <fightobject.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    FightObject* fight;
    inputslot input;

    int tottime;

    int inputtemp[20];
    int skillrec[2][20];

    QLabel* cha[2][2];

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
};

#endif // WIDGET_H
