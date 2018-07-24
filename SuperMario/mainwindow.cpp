#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    level=new QMenu("level");
    menuBar()->addMenu(level);
    easy=new QAction("easy",this);
    level->addAction(easy);
    medium=new QAction("medium",this);
    level->addAction(medium);
    high=new QAction("high",this);
    level->addAction(high);
    connect(easy,SIGNAL(triggered(bool)),this,SLOT(easyLevelOption()));
    connect(medium,SIGNAL(triggered(bool)),this,SLOT(mediumLevelOption()));
    connect(high,SIGNAL(triggered(bool)),this,SLOT(highLevelOption()));


    qsrand(QTime::currentTime().second());

    this->bufferPixmap = new QPixmap(288,512);
    // Set size.
    this->resize(540,960);

    /* Init 3 buttons. */
    this->startButton = new QPushButton(this);
    this->startButton->setGeometry(QRect((20.0/288)*this->width(),
                                   (341.0/512)*this->height(),
                                   (117.0/288)*this->width(),
                                   (71.0/512)*this->height()));
    this->startButton->setStyleSheet("QPushButton{border-image:url(:/image/image/button_play.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->startButton,SIGNAL(clicked()),this,SLOT(startGame()));

    this->closeButton = new QPushButton(this);
    this->closeButton->setGeometry(QRect((151.0/288)*this->width(),
                                         (341.0/512)*this->height(),
                                         (117.0/288)*this->width(),
                                         (71.0/512)*this->height()));
    this->closeButton->setStyleSheet("QPushButton{border-image:url(:/image/image/button_close.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->closeButton,SIGNAL(clicked()),this,SLOT(closeGame()));

    this->infoButton = new QPushButton(this);
    this->infoButton->setGeometry(QRect((106.5/288)*this->width(),
                                         (300.0/512)*this->height(),
                                         (75.0/288)*this->width(),
                                         (48.0/512)*this->height()));
    this->infoButton->setStyleSheet("QPushButton{border-image:url(:/image/image/button_rate.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->infoButton,SIGNAL(clicked()),this,SLOT(displayInfo()));

    /* Init all the game elements. */
    this->background = new EleBackground();
    this->scoreboard = new EleScoreBoard();
    this->readyboard = new EleReadyBoard();
    this->overboard = new EleOverBoard();
    this->titleboard = new EleTitleBoard();

    this->widget=new MyWidget;

    this->flower=new eleFlower;
    this->brick[0]=new eleBrick(0);
    this->brick[1]=new eleBrick(3);
    this->brick[2]=new eleBrick(5);

    //for  ready
    this->readyBrick=new eleReadyBrick;

    this->cloud[0]=new eleCloud(1);
    this->cloud[1]=new eleCloud(6);
    this->turtle[0]=new eleTurtle(2);
    this->turtle[1]=new eleTurtle(4);
    this->mario=new eleMario;
    this->MarioRect.setRect(0,0,this->mario->getBindRect().width(),0.25*this->mario->getBindRect().height());



    /* Sound */
    this->soundDie = new QSound(":/sounds/sounds/death.wav");
    this->soundBGM=new QSound(":/sounds/sounds/bgm0.wav");
    this->soundButton=new QSound(":/sounds/sounds/button.wav");
    this->soundOver=new QSound(":/sounds/sounds/over.wav");
    this->soundScore=new QSound(":/sounds/sounds/score.wav");

    /* The refresh rate : 50Hz */
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    timer.start(20);

    connect(this->cloud[0],SIGNAL(increaseScore()),this,SLOT(getScore()));
    connect(this->cloud[1],SIGNAL(increaseScore()),this,SLOT(getScore()));
    connect(this->brick[0],SIGNAL(increaseScore()),this,SLOT(getScore()));
    connect(this->brick[1],SIGNAL(increaseScore()),this,SLOT(getScore()));
    connect(this->brick[2],SIGNAL(increaseScore()),this,SLOT(getScore()));
    connect(this->turtle[0],SIGNAL(increaseScore()),this,SLOT(getScore()));
    connect(this->turtle[1],SIGNAL(increaseScore()),this,SLOT(getScore()));
    connect(this->overboard,SIGNAL(buttonVisible(bool,bool,bool)),this,SLOT(setButtonVisible(bool,bool,bool)));

    // Game Start.
    this->gameTitle();
}

MainWindow::~MainWindow()
{
    delete this->startButton;
    delete this->infoButton;
    delete this->closeButton;

    delete this->background;
    delete this->scoreboard;
    delete this->readyboard;
    delete this->overboard;
    delete this->titleboard;
    delete this->flower;
    delete this->brick[0];
    delete this->brick[1];
    delete this->brick[2];
    delete this->readyBrick;
    delete this->cloud[0];
    delete this->cloud[1];
    delete this->turtle[0];
    delete this->turtle[1];
    delete this->mario;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    /*When the game is ready , start the game. */
    if( this->status == GAMEREADY && event->button() == Qt::LeftButton )
    {
        this->soundButton->play();
        this->gamePlay();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key=event->key();
    if(key==65)
        this->mario->isLeft=true;
    if(key==68)
        this->mario->isRight=true;
}

void MainWindow::keyReleaseEvent(QKeyEvent *)
{
    this->mario->isLeft=false;
    this->mario->isRight=false;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this->bufferPixmap);
    /* Draw all the elements. */
    this->background->logic();
    this->background->draw(&painter);

    this->scoreboard->logic();
    this->scoreboard->draw(&painter);

    this->readyboard->logic();
    this->readyboard->draw(&painter);

    this->titleboard->logic();
    this->titleboard->draw(&painter);

    this->overboard->logic();
    this->overboard->draw(&painter);


    this->flower->logic();
    this->flower->draw(&painter);
    this->brick[0]->logic();
    this->brick[0]->draw(&painter);
    this->brick[1]->logic();
    this->brick[1]->draw(&painter);
    this->brick[2]->logic();
    this->brick[2]->draw(&painter);
    this->readyBrick->logic();
    this->readyBrick->draw(&painter);
    this->cloud[0]->logic();
    this->cloud[0]->draw(&painter);
    this->turtle[0]->logic();
    this->turtle[0]->draw(&painter);
    this->cloud[1]->logic();
    this->cloud[1]->draw(&painter);
    this->turtle[1]->logic();
    this->turtle[1]->draw(&painter);
    this->mario->logic();
    this->mario->draw(&painter);

    QPainter mainWindowPainter(this);
    mainWindowPainter.drawPixmap(QRect(0,0,this->width(),this->height()),*this->bufferPixmap);

    if(this->status == GAMEPLAY)
    {
        this->MarioRect.moveCenter(QPointF(this->mario->getBindRect().center().x(),this->mario->getBindRect().center().y()+8));

        if(this->MarioRect.intersects(this->brick[0]->getBindRect())
          ||this->MarioRect.intersects(this->brick[1]->getBindRect())
          ||this->MarioRect.intersects(this->brick[2]->getBindRect())
          ||this->MarioRect.intersects(this->readyBrick->getBindRect())
          ||this->MarioRect.intersects(this->cloud[0]->getBindRect())
          ||this->MarioRect.intersects(this->cloud[1]->getBindRect())
           )
        {
            this->mario->enabledFall=false;
        }
        else{
            this->mario->enabledFall=true;
        }
        if(this->mario->getBindRect().top()<=30
           ||this->MarioRect.intersects(this->turtle[0]->getBindRect())
           ||this->MarioRect.intersects(this->turtle[1]->getBindRect())
           ||this->mario->getBindRect().top()>=512)
        {
            this->mario->isDie=true;
            if(this->mario->isDie)
            {
                this->soundDie->play();
                this->gameOver(); //Game over
            }
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    this->startButton->setGeometry(QRect((20.0/288)*this->width(),
                                   (341.0/512)*this->height(),
                                   (117.0/288)*this->width(),
                                   (71.0/512)*this->height()));
    this->closeButton->setGeometry(QRect((151.0/288)*this->width(),
                                         (341.0/512)*this->height(),
                                         (117.0/288)*this->width(),
                                         (71.0/512)*this->height()));
    this->infoButton->setGeometry(QRect((106.5/288)*this->width(),
                                         (300.0/512)*this->height(),
                                         (75.0/288)*this->width(),
                                         (48.0/512)*this->height()));
}

void MainWindow::gameTitle()
{
    this->mario->initspeedY();
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titleboard->enabledLogic = true;
    this->titleboard->enabledDraw = true;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->flower->enabledLogic=false;
    this->flower->enabledDraw=false;
    this->brick[0]->enabledLogic = false;
    this->brick[0]->enabledDraw = false;
    this->brick[1]->enabledLogic = false;
    this->brick[1]->enabledDraw = false;
    this->brick[2]->enabledLogic = false;
    this->brick[2]->enabledDraw = false;
    this->readyBrick->enabledLogic=false;
    this->readyBrick->enabledDraw=false;
    this->cloud[0]->enabledDraw=false;
    this->cloud[0]->enabledLogic=false;
    this->cloud[1]->enabledDraw=false;
    this->cloud[1]->enabledLogic=false;
    this->turtle[0]->enabledDraw=false;
    this->turtle[0]->enabledLogic=false;
    this->turtle[1]->enabledDraw=false;
    this->turtle[1]->enabledLogic=false;

    this->mario->enabledLogic=false;
    this->mario->enabledDraw=false;
    this->mario->enabledFall=false;
    this->mario->enabledMove=false;


    this->background->currentFrame=1;

    this->setButtonVisible(true,true,true);
    this->status = GAMETITLE;
}

void MainWindow::gameReady()
{
    this->score = 0;

    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titleboard->enabledLogic = false;
    this->titleboard->enabledDraw = false;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = true;
    this->readyboard->enabledDraw = true;

    this->scoreboard->enabledLogic = true;
    this->scoreboard->enabledDraw = true;

    this->flower->enabledLogic=false;
    this->flower->enabledDraw=false;
    this->brick[0]->enabledLogic = false;
    this->brick[0]->enabledDraw = false;
    this->brick[1]->enabledLogic = false;
    this->brick[1]->enabledDraw = false;
    this->brick[2]->enabledLogic = false;
    this->brick[2]->enabledDraw = false;
    this->readyBrick->enabledLogic=false;
    this->readyBrick->enabledDraw=true;
    this->cloud[0]->enabledDraw=false;
    this->cloud[0]->enabledLogic=false;
    this->cloud[1]->enabledDraw=false;
    this->cloud[1]->enabledLogic=false;
    this->turtle[0]->enabledDraw=false;
    this->turtle[0]->enabledLogic=false;
    this->turtle[1]->enabledDraw=false;
    this->turtle[1]->enabledLogic=false;

    this->mario->enabledLogic=false;
    this->mario->enabledDraw=true;
    this->mario->enabledFall=false;
    this->mario->enabledMove=false;

    this->background->currentFrame=2;

    this->setButtonVisible(false,false,false);
    this->status = GAMEREADY;
}

void MainWindow::gamePlay()
{
    this->soundBGM->play();
    soundBGM->setLoops(100);
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titleboard->enabledLogic = false;
    this->titleboard->enabledDraw = false;

    this->overboard->enabledLogic = false;
    this->overboard->enabledDraw = false;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->scoreboard->enabledLogic = true;
    this->scoreboard->enabledDraw = true;

    this->flower->enabledLogic=true;
    this->flower->enabledDraw=true;
    this->brick[0]->enabledLogic = true;
    this->brick[0]->enabledDraw = true;
    this->brick[1]->enabledLogic = true;
    this->brick[1]->enabledDraw = true;
    this->brick[2]->enabledLogic = true;
    this->brick[2]->enabledDraw = true;
    this->cloud[0]->enabledDraw=true;
    this->cloud[0]->enabledLogic=true;
    this->cloud[1]->enabledDraw=true;
    this->cloud[1]->enabledLogic=true;
    this->turtle[0]->enabledDraw=true;
    this->turtle[0]->enabledLogic=true;
    this->turtle[1]->enabledDraw=true;
    this->turtle[1]->enabledLogic=true;

    this->mario->enabledLogic=true;
    this->mario->enabledDraw=true;
    this->mario->enabledFall=true;
    this->mario->enabledMove=true;

    this->readyBrick->enabledLogic=true;
    this->readyBrick->enabledDraw=true;

    this->background->currentFrame=0;
    this->setButtonVisible(false,false,false);

    this->status = GAMEPLAY;
}

void MainWindow::gameOver()
{
    this->soundBGM->stop();
    soundtimer.start(2000);
    connect(&soundtimer,SIGNAL(timeout()),this,SLOT(playOverSound()));

    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titleboard->enabledLogic = false;
    this->titleboard->enabledDraw = false;

    this->overboard->setScore(this->score);
    this->overboard->enabledLogic = true;
    this->overboard->enabledDraw = true;

    this->readyboard->enabledLogic = false;
    this->readyboard->enabledDraw = false;

    this->scoreboard->enabledLogic = false;
    this->scoreboard->enabledDraw = false;

    this->flower->enabledLogic=false;
    this->flower->enabledDraw=false;
    this->brick[0]->enabledLogic = false;
    this->brick[0]->enabledDraw = false;
    this->brick[1]->enabledLogic = false;
    this->brick[1]->enabledDraw = false;
    this->brick[2]->enabledLogic = false;
    this->brick[2]->enabledDraw = false;
    this->readyBrick->enabledLogic=false;
    this->readyBrick->enabledDraw=false;
    this->cloud[0]->enabledDraw=false;
    this->cloud[0]->enabledLogic=false;
    this->cloud[1]->enabledDraw=false;
    this->cloud[1]->enabledLogic=false;
    this->turtle[0]->enabledDraw=false;
    this->turtle[0]->enabledLogic=false;
    this->turtle[1]->enabledDraw=false;
    this->turtle[1]->enabledLogic=false;

    this->mario->enabledLogic=false;
    this->mario->enabledDraw=false;
    this->mario->enabledFall=false;
    this->mario->enabledMove=false;

    this->background->currentFrame=3;

    this->status = GAMEOVER;
}

void MainWindow::startGame()
{
    /* Init all the game elements. */
    this->background->init();
    this->scoreboard->init();
    this->readyboard->init();
    this->overboard->init();
    this->flower->init();
    this->brick[0]->init();
    this->brick[1]->init();
    this->brick[2]->init();
    this->readyBrick->init();
    this->cloud[0]->init();
    this->turtle[0]->init();
    this->cloud[1]->init();
    this->turtle[1]->init();
    this->mario->init();
    this->soundOver->stop();

    // Game Start.
    this->gameReady();

    this->soundButton->play();
}

void MainWindow::closeGame()
{
    this->soundButton->play();
    this->close();
}

void MainWindow::getScore()
{
    this->score += 1;
    this->scoreboard->setScore(this->score);
    this->soundScore->play();
}

void MainWindow::displayInfo()
{
    this->soundButton->play();
    widget->resize(640,1080);
    widget->show();
}

void MainWindow::setButtonVisible(bool _startBtn, bool _scoreBtn, bool _rateBtn)
{
    this->startButton->setVisible(_startBtn);
    this->closeButton->setVisible(_scoreBtn);
    this->infoButton->setVisible(_rateBtn);
}

void MainWindow::playOverSound()
{
    this->soundOver->play();
    soundtimer.stop();
}

void MainWindow::easyLevelOption()
{
    this->mario->setLevel(1);
}

void MainWindow::mediumLevelOption()
{
    this->mario->setLevel(2);
}

void MainWindow::highLevelOption()
{
    this->mario->setLevel(3);
}
