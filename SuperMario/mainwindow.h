#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include<QKeyEvent>
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include <QSound>
#include<QMenu>
#include<QAction>
#include<QMenuBar>

#include "elebackground.h"
#include "elescoreboard.h"
#include "elereadyboard.h"
#include "eleoverboard.h"
#include "eletitleboard.h"
#include"eleflower.h"
#include"eleBrick.h"
#include"eleCloud.h"
#include"eleTurtle.h"
#include"eleMario.h"
#include"eleReadyBrick.h"
#include"MyWidget.h"



/* 4 status */
enum GameStatus{GAMETITLE,
                GAMEREADY,
                GAMEPLAY,
                GAMEOVER};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QPixmap *bufferPixmap;

    /* Buttons on the start panel. */
    QPushButton *startButton;
    QPushButton *closeButton;
    QPushButton *infoButton;

    /* Elements need to draw */
    EleBackground *background;
    EleScoreBoard *scoreboard;
    EleReadyBoard *readyboard;
    EleOverBoard *overboard;
    EleTitleBoard *titleboard;
    eleFlower* flower;
    eleBrick* brick[3];
    eleCloud* cloud[2];
    eleTurtle* turtle[2];
    eleMario* mario;
    eleReadyBrick* readyBrick;


    /* Sound */
    QSound *soundDie;
    QSound *soundBGM;
    QSound *soundButton;
    QSound *soundOver;
    QSound *soundScore;

    MyWidget* widget;


    int score; // Game score
    QRectF MarioRect;

    GameStatus status;
    QTimer timer; // Main timer, refresh the interface.
    QTimer soundtimer;

    /*Corresponding  to 4 game status. */
    void gameTitle();
    void gameReady();
    void gamePlay();
    void gameOver();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public slots:
    void getScore(); // socre increase.
    void startGame(); // The button clicked , game began.
    void closeGame();// The button clicked , game exit.
    void displayInfo();
    void setButtonVisible(bool,bool,bool); // set 3 button visible .
    void playOverSound();
    void easyLevelOption();
    void mediumLevelOption();
    void highLevelOption();
protected:
    QMenu *level;
    QAction*easy;
    QAction*medium;
    QAction*high;

};

#endif // MAINWINDOW_H
