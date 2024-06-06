#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    bool ret=pix.load(normalImgPath);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }
    //设置固定图标
    this->setFixedSize(pix.width(),pix.height());
    //设置不规定图标
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

//弹跳效果1
void MyPushButton::zoom1(){
    //创建动画对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //创建时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //终止位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}


//弹跳效果2
void MyPushButton::zoom2(){
    //创建动画对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //创建时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //终止位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e){

    if(this->pressImgPath!=""){

        QPixmap pix;
        bool ret=pix.load(pressImgPath);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }
        //设置固定图标
        this->setFixedSize(pix.width(),pix.height());
        //设置不规定图标
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImgPath!=""){

        QPixmap pix;
        bool ret=pix.load(this->normalImgPath);
        if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }
        //设置固定图标
        this->setFixedSize(pix.width(),pix.height());
        //设置不规定图标
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }

    return QPushButton::mouseReleaseEvent(e);
}

