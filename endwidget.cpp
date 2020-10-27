#include "endwidget.h"

EndWidget::EndWidget()
{
    resize(1000,618);
    QPixmap pixmap = QPixmap("://Aura/winBackground.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    exitBtn.setParent(this);
    exitBtn.resize(150,150);
    exitBtn.move(100,400);
    exitBtn.setStyleSheet("QPushButton{border-image:url(:Aura/SunExit.png)}");
    connect(&exitBtn, &QPushButton::clicked, this,
        [=]()
        {
            returnNum=0;
            exitEndWidget();
            hide();
        });

    restartBtn.setParent(this);
    restartBtn.resize(150,150);
    restartBtn.move(400,400);
    restartBtn.setStyleSheet("QPushButton{border-image:url(:Aura/SubRefresh.png)}");
    connect(&restartBtn, &QPushButton::clicked,this,
        [=]()
        {
            returnNum=1;
            exitEndWidget();
            hide();
        });

    mainMenuBtn.setParent(this);
    mainMenuBtn.resize(150,150);
    mainMenuBtn.move(700,400);
    mainMenuBtn.setStyleSheet("QPushButton{border-image:url(:Aura/SubHome.png)}");
    connect(&mainMenuBtn, &QPushButton::clicked,this,
        [=]()
        {
            returnNum=2;
            exitEndWidget();
            hide();
        });

}

EndWidget::EndWidget(int i)
{
    resize(1000,618);
    QPixmap pixmap = QPixmap("://Aura/winBackground.png").scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    exitBtn.setParent(this);
    exitBtn.resize(150,150);
    exitBtn.move(100,400);
    exitBtn.setStyleSheet("QPushButton{border-image:url(:Aura/SunExit.png)}");
    connect(&exitBtn, &QPushButton::clicked, this,
        [=]()
        {
            returnNum=0;
            exitEndWidget();
            hide();
        });

    restartBtn.setParent(this);
    restartBtn.resize(150,150);
    restartBtn.move(400,400);
    restartBtn.setStyleSheet("QPushButton{border-image:url(:Aura/SubRefresh.png)}");
    connect(&restartBtn, &QPushButton::clicked,this,
        [=]()
        {
            returnNum=1;
            exitEndWidget();
            hide();
        });

    mainMenuBtn.setParent(this);
    mainMenuBtn.resize(150,150);
    mainMenuBtn.move(700,400);
    mainMenuBtn.setStyleSheet("QPushButton{border-image:url(:Aura/SubHome.png)}");
    connect(&mainMenuBtn, &QPushButton::clicked,this,
        [=]()
        {
            returnNum=2;
            exitEndWidget();
            hide();
        });
    wins.setParent(this);
    wins.resize(800,300);
    wins.move(100,100);
    if(i==0)
    {
        wins.setStyleSheet("QLabel{border-image:url(:/Aura/1PWin.png)}");
    }
    else
    {
        wins.setStyleSheet("QLabel{border-image:url(:/Aura/1PWin.png)}");
    }

}

void EndWidget::exitEndWidget()
{
    emit exitSubWidget(returnNum);
}

void EndWidget::closeEvent(QCloseEvent *event)
{
    returnNum=1;
    exitEndWidget();
    hide();
}
