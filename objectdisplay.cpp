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
    //displayLabel.setStyleSheet("QLabel{border:2px solid #242424;}");

}
void FighterDisplay::display(int x, int y, int dx, int dy, int w, int h)
{
    displayLabel.move(x+dx,y-dy);
    displayLabel.resize(w,h);
    displayLabel.clear();
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
        //p->setStyleSheet("QLabel{border:2px solid #242424;}");
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
        hitBox[i].clear();
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
    QFont ft;
    ft.setPointSize(20);
    ft.setBold(true);
    ft.setFamily("Microsoft YaHei");

    QPalette pa;
    pa.setColor(QPalette::WindowText,QColor(233,0,0));

    for (int i=0; i<2; i++)
    {
        playerTitle[i].move(i?1000:200,100);
        playerTitle[i].resize(150,150);
        playerTitle[i].setAlignment(Qt::AlignCenter);
        playerTitle[i].setFont(ft);

        for (int j=0; j<2; j++)
        {
            heroHead[i][j].resize(150,400);
            heroHead[i][j].move((i?1000:200)+(j*200),300);
            heroHead[i][j].setFont(ft);
            pa.setColor(QPalette::ButtonText,QColor(233,0,0));
            heroHead[i][j].setPalette(pa);
        }
    }

    playerTitle[0].setStyleSheet("QLabel{border-image:url(:Aura/1P.png)}");
    playerTitle[1].setStyleSheet("QLabel{border-image:url(:Aura/P2.png)}");

    heroHead[0][0].setStyleSheet("QPushButton{border-image:url(:Aura/Aura by Crucifix_0-1.png)}");
    heroHead[0][1].setStyleSheet("QPushButton{border-image:url(:Aura/Aura by Crucifix_20-5.png)}");
    heroHead[1][0].setStyleSheet("QPushButton{border-image:url(:Aura/Aura by Crucifix_0-1.png)}");
    heroHead[1][1].setStyleSheet("QPushButton{border-image:url(:Aura/Aura by Crucifix_20-5.png)}");

    sure.resize(200,120);
    sure.move(700,700);
    sure.setFont(ft);
    sure.setStyleSheet("QPushButton{border-image:url(:Aura/Sure.png)}");

}

void HeroSelece::changeSelect(int i, int j)
{
    if (i==0)
    {
        playerTitle[0].move(200+j*200,100);
        selectNum[0]=j;
    }
    if (i==1)
    {
        playerTitle[1].move(1000+j*200, 100);
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
    sure.setParent(father);
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
    sure.hide();
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
    sure.show();
}



