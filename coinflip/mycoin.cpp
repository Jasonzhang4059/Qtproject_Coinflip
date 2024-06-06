#include "mycoin.h"

Mycoin::Mycoin(QString btnImg){
    QPixmap pix;
    bool ret=pix.load(btnImg);
    if(!ret){
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1=new QTimer(this);
    timer2=new QTimer(this);
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max){
            isAnimation=false;
            min=1;
            timer1->stop();
        }
    });
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max){
            isAnimation=false;
            max=8;
            timer2->stop();
        }
    });
}

void Mycoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation||this->isWin){
        return;
    }else{
        QPushButton::mousePressEvent(e);
    }
}

void Mycoin::changeFlag(){
    isAnimation=true;
    if(this->flag){

        timer1->start(30);
        this->flag=false;
    }
    else{
        timer2->start(30);
        this->flag=true;
    }
}
