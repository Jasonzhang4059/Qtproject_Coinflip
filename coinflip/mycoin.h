#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>
class Mycoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit Mycoin(QWidget *parent = nullptr);
    Mycoin(QString btnImg);
    int posx;
    int posy;
    bool flag;
    void changeFlag();
    QTimer *timer1;
    int min=1;
    int max=8;
    QTimer *timer2;
    bool isAnimation=false;
    void mousePressEvent(QMouseEvent *e);
    bool isWin=false;
signals:

public slots:
};

#endif // MYCOIN_H
