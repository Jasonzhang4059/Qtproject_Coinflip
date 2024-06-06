#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include"mycoin.h"
#include<QLabel>
#include<QDebug>
#include<dataconfig.h>
#include<QPropertyAnimation>
#include<QtMultimedia/QSound>
playscene::playscene(int levelNum)
{
    this->levelIndex=levelNum;
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币");
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitmenu=startMenu->addAction("退出");
    QSound *backSound=new QSound(":/res/BackButtonSound.wav");
    QSound *flipSound=new QSound(":/res/ConFlipSound.wav");
    QSound *winSound=new QSound(":/res/LevelWinSound.wav");
    //实现退出功能
    connect(quitmenu,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        backSound->play();
        QTimer::singleShot(500,this,[=](){
            emit this->chooseLevelScene();
        });

    });
    QLabel *label=new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    label->setText(QString("Level:%1").arg(this->levelIndex));
    label->setGeometry(QRect(30,this->height()-50,120,50));
    dataConfig config;
    //初始化每个数组位置
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){

            this->playArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }

        //设置胜利图片
    QPixmap temppix;
    QLabel *winlabel=new QLabel;
    temppix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0,0,temppix.width(),temppix.height());
    winlabel->setPixmap(temppix);
    winlabel->setParent(this);
    winlabel->move(this->width()*0.5-temppix.width()*0.5,-temppix.height());

    //设置金币位置
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QLabel *label=new QLabel(this);
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->move(57+i*50,200+j*50);
            QString str;
            if(this->playArray[i][j]==1){
            //设置金币
                str=":/res/Coin0001.png";
            }
            else{
                str=":/res/Coin0008.png";

            }

            Mycoin *coin=new Mycoin(str);
            coinArr[i][j]=coin;
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posx=i;
            coin->posy=j;
            coin->flag=this->playArray[i][j];
            connect(coin,&Mycoin::clicked,[=](){
                flipSound->play();
                coin->changeFlag();
                this->playArray[i][j]=this->playArray[i][j]?0:1;
                if(i<3){
                    coinArr[i+1][j]->changeFlag();
                    this->playArray[i+1][j]=this->playArray[i+1][j]?0:1;
                }
                if(i>0){
                    coinArr[i-1][j]->changeFlag();
                    this->playArray[i-1][j]=this->playArray[i-1][j]?0:1;
                }
                if(j<3){
                    coinArr[i][j+1]->changeFlag();
                    this->playArray[i][j+1]=this->playArray[i][j+1]?0:1;
                }
                if(j>0){
                    coinArr[i][j-1]->changeFlag();
                    this->playArray[i][j-1]=this->playArray[i][j-1]?0:1;
                }

                //判断是否胜利
                isWin=true;
                for(int ii=0;ii<4;ii++){
                    for(int jj=0;jj<4;jj++){
                        if(playArray[ii][jj]==false){
                            isWin=false;
                            break;
                        }
                    }
                    if(!isWin) break;
                }

                if(isWin){
                    winSound->play();
                    for(int ii=0;ii<4;ii++){
                        for(int jj=0;jj<4;jj++){
                           coinArr[ii][jj]->isWin=true;
                        }

                    }

                    //
                    QPropertyAnimation *animation=new QPropertyAnimation(winlabel,"geometry");
                    animation->setDuration(1000);
                    animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                    animation->setEndValue(QRect(winlabel->x(),winlabel->y()+114,winlabel->width(),winlabel->height()));
                    animation->setEasingCurve(QEasingCurve::OutBounce);
                    animation->start();
                }

            });
        }
    }

}

void playscene::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");

    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,30,pix.width(),pix.height(),pix);
}
