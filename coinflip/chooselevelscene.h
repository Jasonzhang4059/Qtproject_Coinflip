#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include"playscene.h"
class chooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    playscene *play=0;
signals:
    //返回按钮发送信号返回主场景
    void chooseMainScene();

public slots:
};

#endif // CHOOSELEVELSCENE_H
