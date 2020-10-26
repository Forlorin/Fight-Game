#include "Objectdisplay.h"

FighterDisplay::FighterDisplay()
{
    displayLabel.resize(180,300);
    displayLabel.move(i?700:50,400);
    QFont font1 ( "Microsoft YaHei", 15, 75);
    displayLabel.setFont(font1);
    displayLabel.setText(i?"2":"1");
    //displayLabel.setStyleSheet("QLabel{background-color:rgb(0,168,50);}");
}

void FighterDisplay::setOrder(int num)
{
    i=num;
}
void FighterDisplay::setParent(QWidget* parent)
{
    displayLabel.setParent(parent);
}


void FighterDisplay::display(int x, int y, QString imgPath)
{
    displayLabel.resize(x*4,y*4);
    displayLabel.setStyleSheet("QLabel{border-image:url("+imgPath+")}");
}
void FighterDisplay::display(int x, int y)
{
    displayLabel.move(x,y);
}
void FighterDisplay::display(int x, int y, int dx, int dy, int w, int h, QPixmap img)
{
    displayLabel.move(x+dx,y-dy);
    displayLabel.resize(w,h);
    displayLabel.setPixmap(img);
    displayLabel.setStyleSheet("QLabel{border:2px solid #242424;}");

}

void FighterDisplay::setText (QString str)
{
    displayLabel.setText(str);
}


HitBoxLabels::HitBoxLabel()
{
    for (int i=0; i<2; i++)
    {
        hitBox[i].hide();
        QFont font1 ( "Microsoft YaHei", 15, 75);
        hitBox[i].setFont(font1);
        hitBox[i].setText(i?"2":"1");
        hitBox[i].setStyleSheet("QLabel{background-color:rgb(255,0,0);}");
    }
}

void HitBoxLabels::setParent(QWidget *father)
{
    for(int i=0; i<2; i++)
    {
        hitBox[i].setParent(father);
    }
}

void HitBoxLabels::display(int i, int x, int y, int width, int hight,QPixmap img)
{
    if(width==0||hight==0)
    {
        hitBox[i].hide();
    }
    else
    {
        QLabel* p=&hitBox[i];
        p->move(x,y);
        p->resize(width,hight);
        hitBox[i].show();
        p->setPixmap(img);
        p->setStyleSheet("QLabel{border:2px solid #242424;}");
    }
}
void HitBoxLabels::display(int i, int x, int y, int width, int hight)
{
    if(width==0||hight==0)
    {
        hitBox[i].hide();
    }
    else
    {
        QLabel* p=&hitBox[i];
        p->move(x,y);
        p->resize(width,hight);
        hitBox[i].show();
        p->setStyleSheet("QLabel{border:2px solid #242424;}");
    }
}

void HitBoxLabels:: hide(int i)
{
    hitBox[i].hide();
}

void HitBoxLabels::show(int i)
{
    hitBox[i].show();
}

bool Trangle::isHit(Trangle &beHit)
{
    if(x >= beHit.x && x >= beHit.x+beHit.w)
        return false;
    else if(x <= beHit.x && x+w <= beHit.x)
        return false;
    else if(y >= beHit.y && y >= beHit.y+beHit.h)
        return false;
    else if(y <= beHit.y && y+h <= beHit.y)
        return false;
    return true;
}

HeroSelece::HeroSelece()
{
    for (int i=0; i<2; i++)
    {
        playerTitle[i].move(i?1200:200,200);
        playerTitle[i].resize(200,120);
        playerTitle[i].setText("1P\n  |");

        playerTitle[i].setStyleSheet("background-color:rgb(255,255,255);");
        playerTitle[i].setAlignment(Qt::AlignCenter);

        QFont ft;
        ft.setPointSize(12);
        ft.setBold(true);
        ft.setFamily("Microsoft YaHei");
        playerTitle[i].setFont(ft);

        QPalette pa;
        pa.setColor(QPalette::WindowText,QColor(233,0,0));
        playerTitle[i].setPalette(pa);

        for (int j=0; j<2; j++)
        {
            heroHead[i][j].resize(100,100);
            heroHead[i][j].move(i?1200:200+j*120,400);
            heroHead[i][j].setFont(ft);
            heroHead[i][j].setText(QString::number(j));
            pa.setColor(QPalette::ButtonText,QColor(233,0,0));
            heroHead[i][j].setPalette(pa);
            heroHead[i][j].setStyleSheet("background-color:rgb(255,255,255);");
        }
    }
}

void HeroSelece::changeSelect(int i, int j)
{
    if (i==0)
    {
        playerTitle[0].move(200+j*120,200);
        selectNum[0]=j;
    }
    if (i==1)
    {
        playerTitle[1].move(1200+j*120, 200);
        selectNum[0]=j;
    }
}

void HeroSelece::setParent(QWidget *father)
{
    for (int i=0; i<2; i++)
    {
        playerTitle[i].setParent(father);
        for(int j=0; j<2; j++)
        {
            heroHead[i][j].setParent(father);
        }
    }
}

void HeroSelece::hide()
{
    for (int i=0; i<2; i++)
    {
        playerTitle[i].hide();
        for(int j=0; j<2; j++)
        {
            heroHead[i][j].hide();
        }
    }
}

void HeroSelece::show()
{
    for (int i=0; i<2; i++)
    {
        playerTitle[i].show();
        for(int j=0; j<2; j++)
        {
            heroHead[i][j].show();
        }
    }
}
