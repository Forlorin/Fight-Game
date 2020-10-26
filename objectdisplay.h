#ifndef OBJECTDISPLAY_H
#define OBJECTDISPLAY_H
#include "fightobject.h"
#include "inputslot.h"
#include <QString>
#include <QLabel>
#include <QWidget>
#include <QPushButton>

class FighterDisplay
{
    int i;
public:
    QLabel displayLabel;
    FighterDisplay();
    void setOrder(int num);
    void setParent(QWidget* parent);
    void display(int x, int y, QString imgPath);
    void display(int x, int y);
    void display(int x, int y, int dx, int dy, int w, int h, QPixmap img);
    void setText (QString str);
};


class HitBoxLabels
{
    QLabel hitBox[2];
public:
    HitBoxLabel();
    void setParent(QWidget* father);
    void display(int i, int x, int y, int width, int hight, QPixmap img);
    void display(int i, int x, int y, int width, int hight);
    void hide(int i);
    void show(int i);
};

class Trangle
{

public:
    int x;
    int y;
    int w;
    int h;
    Trangle(){}
    bool isHit(Trangle &beHit);
};

class HeroSelece
{
    QLabel playerTitle[2];
    int selectNum[2];
public:
    QPushButton heroHead[2][2];
    HeroSelece();
    void changeSelect(int i, int j);
    void setParent(QWidget* father);
    void hide();
    void show();
};

#endif // OBJECTDISPLAY_H
