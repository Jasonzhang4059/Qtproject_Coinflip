#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"playscene.h"
#include<QtMultimedia/QSound>
chooseLevelScene::chooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");
    //设置菜单栏
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitmenu=startMenu->addAction("退出");

    //实现退出功能
    connect(quitmenu,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    QSound *chooseSound=new QSound(":/res/TapButtonSound.wav");
    QSound *backSound=new QSound(":/res/BackButtonSound.wav");
    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        QTimer::singleShot(500,this,[=](){
            emit chooseMainScene();
        });

    });
    for(int i=0;i<20;i++){
        MyPushButton *menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);

        connect(menuBtn,&MyPushButton::clicked,[=](){
            chooseSound->play();
            //进入游戏场景
            this->hide();
            play=new playscene(i+1);
            play->setGeometry(this->geometry());
            play->show();
            connect(play,&playscene::chooseLevelScene,[=](){
                this->setGeometry(play->geometry());
               this->show();
               delete play;
                play=0;
            });
        });
        QLabel *l=new QLabel;
        l->setParent(this);
        l->setFixedSize(menuBtn->width(),menuBtn->height());
        l->setText(QString::number(i+1));
        l->move(25+i%4*70,130+i/4*70);
        l->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        l->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}

void chooseLevelScene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");

    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,30,pix.width(),pix.height(),pix);
}
