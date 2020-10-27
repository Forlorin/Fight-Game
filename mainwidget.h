#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include <QString>
#include "inputslot.h"
#include "fightobject.h"
#include "objectdisplay.h"
#include "optionslot.h"
#include "endwidget.h"

namespace Ui
{
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

    int fighterX[2];
    int fighterY[2];
    int hitboxX[2];
    int hitboxY[2];
    int hitboxDx[2];
    int hitboxDy[2];
    int actionNum[2];
    int actionPriority[2];
    int heroName[2];
    int playerStatue[2];
    int forwardSpeed;
    int backwardSpeed;
    int hp[2];
    int state[2];
    int timerId;
    int jumpSecond[2];
    bool isjump[2];
    bool isStart;
    QLabel hpBar[2];
    HitBoxLabels hitboxLabels;
    HitBoxLabels beHitBoxLabels;
    inputslot* inputSlot;
    FightObject* fightObject;
    FighterDisplay fighterDisplay[2];
    QLabel Debug[2];
    OptionSlot optionSlot;
    HeroSelece heroSelect;
    EndWidget* endWidget;
    bool faceState;

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void upDate();
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    bool hitboxTest(Hitbox A, Hitbox B, int xAtaFighter, int yAtaFighter, int xHitFighter, int yHitFighter);
    bool isIn(int pointX, int pointY, int x1, int y1, int x2, int y2);
    void movePlayer();
    void initialize();
    void showEndWidget(int i);
    void exitEndWidget(int returnNum);
private:
    Ui::MainWidget *ui;

};

#endif // MAINWIDGET_H
