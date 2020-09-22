#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{

    Q_OBJECT
    QLabel hpBar[2];
    QLabel fighter[2];
    QTimer* myTimer;

public:
    explicit Widget(QWidget *parent = 0);
    void upDate();
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
