#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <inputslot.h>
#include <QDebug>
#include <QLabel>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    inputslot input;

    int tottime;

    QLabel* La[2];

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
