#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QDebug>
#include <QtMultimedia/QSound>
#pragma execution_character_set("utf-8")
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //翻金币标题
    setWindowTitle("翻金币场景");
    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    QSound  *startMusic=new QSound(":/res/TapButtonSound.wav",this);

    //开始按钮
    MyPushButton *startButton=new MyPushButton(":/res/MenuSceneStartButton.png");
    startButton->setParent(this);
    startButton->move(this->width()*0.5-startButton->width()*0.5,0.7*this->height());

    chooseScene=new chooseLevelScene;
    connect(chooseScene,&chooseLevelScene::chooseMainScene,this,[=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
    });
    connect(startButton,&MyPushButton::clicked,[=](){
        startMusic->play();
        //qDebug()<<"按下开始";
        //弹起特效
        startButton->zoom1();
        startButton->zoom2();

        //延时开始关卡选择按钮
        QTimer::singleShot(500,this,[=](){
            //隐藏自己
            this->hide();
            //显示场景
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
            //监听返回按钮信号

        });


    });


}


void MainScene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画背景上图标
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);



}

MainScene::~MainScene()
{
    delete ui;
}
