#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include"mycoin.h"
class playscene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playscene(QWidget *parent = nullptr);
    playscene(int levelNum);
    int levelIndex;
    void paintEvent(QPaintEvent *event);
    int playArray[4][4];
    Mycoin *coinArr[4][4];
    bool isWin;


signals:
    void chooseLevelScene();

public slots:
};

#endif // PLAYSCENE_H
