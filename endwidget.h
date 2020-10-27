#ifndef ENDWIDGET_H
#define ENDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class EndWidget : public QWidget
{
    Q_OBJECT

    int returnNum;
    QPushButton exitBtn;
    QPushButton restartBtn;
    QPushButton mainMenuBtn;
    QLabel wins;

private:
    void closeEvent(QCloseEvent *event);

public:
    EndWidget();
    EndWidget(int i);
    void exitEndWidget();

signals:
    void exitSubWidget(int returnNum);

public slots:
};

#endif // ENDWIDGET_H
