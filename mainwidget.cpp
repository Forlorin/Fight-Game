#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QPixmap>
#define INTERVAL 33

bool hitboxTest(Hitbox A, Hitbox B, int xA, int yA, int xB, int yB);

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setFixedSize(1500,1000);
    heroSelect.setParent(this);
    for(int i=0; i<2; i++)
    {
        for (int i=0; i<2; i++)
        {
             connect(&heroSelect.heroHead[i][j], &QPushButton::clicked, this, [=]()
             {
                 heroSelect.changeSelect(i, j);
             });
        }
    }

    initialize();
}

void MainWidget::initialize()
{
    faceState=true;

    for(int i=0;i<2;i++)
    {
         heroName[i]=0;
         playerStatue[i]=1;
    }
    fighterX[0]=200;
    fighterY[0]=900;
    fighterX[1]=1200;
    fighterY[1]=900;
    forwardSpeed=15;
    backwardSpeed=11;
    //设置初始数据

    for (int i=0; i<2; i++)
    {
    Debug[i].resize(10,500);
    Debug[i].setParent(this);
    Debug[i].setStyleSheet("QLabel{background-color:rgb(248,168,0);}");
    }

    fightObject=new FightObject(800,500,heroName[0],heroName[1]);
    fightObject->player[0].set_health(100);
    fightObject->player[1].set_health(100);
    inputSlot = new inputslot(heroName[0],heroName[1]);
    hitboxLabels.setParent(this);

    for (int i=0; i<2; i++)
    {
        fighterDisplay[i].setParent(this);
        fighterDisplay[i].setOrder(i);
    }
    //初始化人物，并设置人物初始画面
    for (int i=0; i<2; i++)
    {
        hpBar[i].setParent(this);
        hpBar[i].resize(300,30);
        hpBar[i].move(50+i*400, 30);
        QFont font ( "Microsoft YaHei", 20, 75);
        hpBar[i].setFont(font);
        hpBar[i].setText(i?"2":"1"); //清空字体
        hpBar[i].setStyleSheet("QLabel{background-color:rgb(248,168,0);}");
    }//设置血条

    startTimer(INTERVAL);
    //开启定时器
}

MainWidget::~MainWidget()
{
    delete ui;
}

/**************************按键事件***********************************/

void MainWidget:: keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        inputSlot->push(event->key(),faceState);
        switch(event->key())
        {
            case Qt::Key_S:
                optionSlot.addKeyQueue(kS);
                optionSlot.setOption(0);
                break;
            case Qt::Key_A:
                optionSlot.addKeyQueue(kA);
                optionSlot.setOption(0);
                break;
            case Qt::Key_D:
                optionSlot.addKeyQueue(kD);
                optionSlot.setOption(0);
                break;
//            case Qt::Key_W:
//                optionSlot.addKeyQueue(kW);
//                optionSlot.setOption(0);
            case Qt::Key_Down:
                optionSlot.addKeyQueue(kDown);
                optionSlot.setOption(1);
                break;
            case Qt::Key_Left:
                optionSlot.addKeyQueue(kLeft);
                optionSlot.setOption(1);
                break;
            case Qt::Key_Right:
                optionSlot.addKeyQueue(kRight);
                optionSlot.setOption(1);
                break;
//            case Qt::Key_Up:
////                optionSlot.addKeyQueue(kUp);
////                optionSlot.setOption(1);
//            break;
         }
        //optionSlot.coutOpt();

    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())
    {
        switch(event->key())
        {
            case Qt::Key_S:
                optionSlot.removeKeyQueue(kS);
                optionSlot.setOption(0);
                break;
            case Qt::Key_A:
                optionSlot.removeKeyQueue(kA);
                optionSlot.setOption(0);
                break;
            case Qt::Key_D:
                optionSlot.removeKeyQueue(kD);
                optionSlot.setOption(0);
                break;
            case Qt::Key_Down:
                optionSlot.removeKeyQueue(kDown);
                optionSlot.setOption(1);
                break;
            case Qt::Key_Left:
                optionSlot.removeKeyQueue(kLeft);
                optionSlot.setOption(1);
                break;
            case Qt::Key_Right:
                optionSlot.removeKeyQueue(kRight);
                optionSlot.setOption(1);
                break;
        }

        //optionSlot.coutOpt();
    }

}



/****************************计时器********************************/
void MainWidget::timerEvent(QTimerEvent *event)
{
    /*************位移****************/
    movePlayer();

    /*************判定****************/
    /* 获取当前人物是否自由的状态
     * 如果是，不对其进行受击判定
     *
     * 取出所选的人物当前动作的编号，取出动作的优先级，传入当前人物状态编号
     *
     * 进行攻击判定
     *      读取攻击者的攻击碰撞箱
     *      读取受击者的受击碰撞箱
     *      查看是否重叠
     * 处理受击者的受击事件
     * 受击事件：
     *      血量，当前状态发生改变
     *      播放动画
     * 更新inputslot和character
     */

    //获取当前人物是否自由的状态
    bool isControled[2];
    isControled[0]=fightObject->player[0].get_status();
    isControled[1]=fightObject->player[1].get_status();
    //取出所选的人物当前动作的编号，取出动作的优先级，传入当前人物状态编号
    inputSlot->getSt
            (actionNum[0],actionNum[1],
            actionPriority[0],actionPriority[1],
            playerStatue[0],playerStatue[1]);
    for(int i=0; i<2; i++)
    {

        fightObject->player[i].do_act(actionNum[i],actionPriority[i]);
    }


    /****************攻击事件*****************/

    Hitbox hit[2],ata[2];
    bool isUnderAttack[2];
    Trangle ataTrangle[2], hitTrangle[2];
    for(int i=0; i<2; i++)
    {
        hit[i]=fightObject->player[i].get_hitbox();
        ata[i]=fightObject->player[i].get_atabox();
    }
    //分别获取受击碰撞箱和攻击碰撞箱


    for(int i=0; i<2; i++)
    {
        int x, y, w, h;
        bool flag;
        if(i==0&&faceState==1||i==1&&faceState==0)
            flag=1;
        else
            flag=0;
        QString str;
        hit[i].get(x,y,w,h,str);
        if(w!=0&&h!=0)
        {
            QImage image(str);
            if(bool(i)==faceState)
                image=image.mirrored(true,false);
            image=image.scaled(w*4,h*4);

            fighterDisplay[i].display
                    ( fighterX[i] , fighterY[i],
                     (flag?x:-w-x)*4 , y*4,w*4,h*4,
                     QPixmap::fromImage(image));
            hitTrangle[i].x=fighterX[i]+(flag?x:-w-x)*4;
            hitTrangle[i].y=fighterY[i]-y*4;
            hitTrangle[i].w=w*4;
            hitTrangle[i].h=h*4;

            Debug[i].move(fighterX[i]-5,fighterY[i]-500);
        }
        //人物显示

        ata[i].get(x,y,w,h,str);
        if(w!=0&&h!=0)
        {
            if(str=="")
            {
                hitboxLabels.display
                        ( i ,
                          fighterX[i]+(flag?x:-w-x)*4,
                          fighterY[i]-y*4 , w*4 , h*4
                          );

                ataTrangle[i].x=fighterX[i]+(flag?x:-w-x)*4;
                ataTrangle[i].y=fighterY[i]-y*4;
                ataTrangle[i].w=w*4;
                ataTrangle[i].h=h*4;
            }
            else
            {
                QImage image(str);
                if(bool(i)==faceState)
                    image=image.mirrored(true,false);
                image=image.scaled(w*4,h*4);
                hitboxLabels.display
                        ( i ,
                          fighterX[i]+(flag?x:-w-x)*4,
                          fighterY[i]-y*4 , w*4 , h*4 ,
                          QPixmap::fromImage(image)
                        );

                ataTrangle[i].x=fighterX[i]+(flag?x:-w-x)*4;
                ataTrangle[i].y=fighterY[i]-y*4;
                ataTrangle[i].w=w*4;
                ataTrangle[i].h=h*4;
            }
        }
        else
        {
            hitboxLabels.hide(i);
            ataTrangle[i].w=0;
            ataTrangle[i].h=0;

        }
        //攻击显示
    }

    /************碰撞箱检测*************/
    isUnderAttack[0]=0;
    isUnderAttack[1]=0;
    if(!isControled[0])
    {
        isUnderAttack[1] =
            ataTrangle[0].isHit(hitTrangle[1]);
        if(isUnderAttack[1])
            qDebug()<<"true";
    }

    if(!isControled[1])
    {
        isUnderAttack[0] =
            ataTrangle[1].isHit(hitTrangle[0]);

    }

    /*************受击事件**************/
    int damage[2],health;//damage:攻击者的攻击伤害
    int force[2];
    damage[0]=fightObject->player[1].get_damage();

    force[0]=fightObject->player[0].get_action().get_force();
    force[1]=fightObject->player[1].get_action().get_force();
    if(isUnderAttack[0])
    {
        damage[1]=fightObject->player[1].get_damage();
    }
    if(isUnderAttack[1])
    {
        damage[0]=fightObject->player[0].get_damage();
    }
    if(isUnderAttack[0]&&fightObject->player[0].beHit(force[1]))
    {
        health=fightObject->player[0].get_health();
        health-=damage[1];
        fightObject->player[0].set_health(health);
        hpBar[0].resize(int(300.0*health/100),30);
        qDebug()<<"0 get hit :"<<fightObject->player[1].act_doing;
    }
    if(isUnderAttack[1]&&fightObject->player[1].beHit(force[0]))
    {
        health=fightObject->player[1].get_health();
        health-=damage[0];
        fightObject->player[1].set_health(health);
        hpBar[1].resize(int(300.0*health/100),30);
        qDebug()<<"1 get hit :"<<fightObject->player[1].act_doing;
    }




    fightObject->player[0].update();
    fightObject->player[1].update();
    inputSlot->update();
}


/****************可用接口*******************/
/*Class： inputslot
 *
 * void push(int, bool);
 * 传入键盘输入和面朝方向
 *
 * void getSt(int &a, int &b, int &pa, int &pb, int s0, int s1);
 * 取出所选的人物当前动作的编号，取出动作的优先级，传入当前人物状态编号
 *      人物状态编号：1站立  2滞空  3下蹲  4前进 5后退
 *
 * void update();
 * 计时器结束前调用以更新
 *
 *
 *Class：character (use class fightObject to Call)
 *
 * bool beHit(int force);
 * 受击动作，传入受到攻击的硬直大小
 *
 *
 * int get_health();
 * int get_status();
 *  读取状态：1无法控制，2无法选取，0正常
 *  为非0，则受击判断直接略过
 *
 * Hitbox get_hitbox();
 * 人物受击碰撞箱
 *
 * Hitbox get_atabox();
 * 人物攻击碰撞箱
 *
 * int get_damage();
 * void set_health(int);
 *
 * void set_status(int);
 * 设置当前状态
 *
 * void set_in_air(bool);
 *
 * bool do_act(int id,int pri);
 * 进行动作
 * void update();
 *
 *Class：Action (use class character to call)
 *
 * bool isJump();
 * 这个动作是否会让他起跳
 *
 * int get_move();
 * 获取移动速率，用以设置当前动作的移动速度
 *
 * int get_force();
 * 获取当前动作的的攻击强度，能造成多大硬直
 *
 */

/****************位移******************/
void MainWidget::movePlayer()
{
    float moverate[2]{1,1};
//    moverate[0]=fightObject->player[0].get_action().get_move();
//    moverate[1]=fightObject->player[1].get_action().get_move();
//    qDebug()<<moverate[0]<<moverate[1];
    QString str;
    switch (optionSlot.getOption(0))
    {
        case moveL:
            fighterX[0]-=backwardSpeed * moverate[0];
            playerStatue[0]=faceState?5:4;
            str="moveL";
            break;
        case moveR:
            fighterX[0]+=forwardSpeed * moverate[0];
            playerStatue[0]=faceState?4:5;
            str="moveR";
            break;
        case noneOpt:
            str="none";
            playerStatue[0]=1;
            break;
        case squat:
            playerStatue[0]=3;
            str = "squat";
            break;
    }
    fighterDisplay[0].setText(str);
    switch (optionSlot.getOption(1))
    {
        case moveL:
            fighterX[1]-=forwardSpeed * moverate[1];
            playerStatue[1]=faceState?4:5;
            str="moveL";
            break;
        case moveR:
            fighterX[1]+=backwardSpeed * moverate[1];
            playerStatue[1]=faceState?5:4;
            str="moveR";
            break;
        case noneOpt:
            playerStatue[1]=1;
            str="none";
            break;
        case squat:
            playerStatue[1]=3;
            str = "squat";
            break;
    }
    fighterDisplay[1].setText(str);
    //fighterDisplay[0].displayLabel.move(fighterX[0],fighterY[0]);
    //fighterDisplay[1].displayLabel.move(fighterX[1],fighterY[1]);

    //当相对位置互换之后，人的朝向也要改变
    for(int i=0; i<2; i++)
    {
        fighterDisplay[i].display(fighterX[i],fighterY[i]);
    }
    if ((faceState && fighterX[0]>fighterX[1])||(!faceState && fighterX[0]<fighterX[1]))
    {
        int i=forwardSpeed;
        forwardSpeed=backwardSpeed;
        backwardSpeed=i;
        faceState=!faceState;
    }
    static int jumpSpeed[2][20]
    {9,9,7,7,5,5,3,3,1,0,0,-1,-3,-3,-5,-5,-7,-7,-9,-9,
    9,9,7,7,5,5,3,3,1,0,0,-1,-3,-3,-5,-5,-7,-7,-9,-9};
    static int jumpSecond[2]{0,0};
//    for(int i=0; i<2; i++)
//    {
        qDebug()<<fightObject->player[0].get_action().isJump();
        if(fightObject->player[0].get_action().isJump()==true);
        {
            if(jumpSecond[0]==0)
            {
                jumpSecond[0]==1;
            }
            if(jumpSecond[0]<=10)
            {
                fighterY[0]+=jumpSpeed[0][jumpSecond[0]-1];
            }
        }
//    }
}


