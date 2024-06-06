#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#pragma execution_character_set("utf-8")
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg,QString pressImg="");

    void zoom1();//弹跳效果1
    void zoom2();//弹跳效果2
    QString normalImgPath;
    QString pressImgPath;
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
