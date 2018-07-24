#include "eleoverboard.h"

EleOverBoard::EleOverBoard(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
}

void EleOverBoard::init()
{
    this->score = 0;
    this->highestScore = 0;
    this->overBoardisReady=false;
    this->overBoardRect.setRect(200,180,205,145);
    x=40;

    randofGameover=qrand()%4;
    if(randofGameover==0)
    {
        this->overTextRect.setRect(18,-588,239.8,165);
        y=41;
        currentFrame=11;
    }
    else if(randofGameover==1)
    {
        this->overTextRect.setRect(35,-588,218,150);
        y=49;
        currentFrame=12;
    }
    else if(randofGameover==2)
    {
        this->overTextRect.setRect(15,-588,271,169);
        y=42.5;
        currentFrame=13;
    }
    else
    {
        this->overTextRect.setRect(17,-588,264,175);
        y=36;
        currentFrame=10;
    }
}

void EleOverBoard::logic()
{
    if(!this->enabledLogic)
        return;

    if(this->overTextRect.y() < this->y)
        this->overTextRect.translate(0,15);
    else
        this->overTextRect.setY(this->y);

    if(this->overBoardRect.x() > this->x)
        this->overBoardRect.translate(-15,0);
    else
    {
        this->overBoardRect.setX(this->x);
        overBoardisReady=true;
    }
}

void EleOverBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;
    //gameover面板
    painter->drawPixmap(this->overTextRect.x(),
                      this->overTextRect.y(),
                      this->overTextRect.width(),
                      this->overTextRect.height(),
                      this->pixmapList[this->currentFrame]);
    //木板
    painter->drawPixmap(this->overBoardRect.x(),
                      this->overBoardRect.y(),
                      this->overBoardRect.width(),
                      this->overBoardRect.height(),
                      this->pixmapList[14]);

    //score
    if(overBoardisReady)
    {
        if((this->score%1000)/100 != 0)
        {
            painter->drawPixmap(40,
                                260,
                                34,
                                42,
                                this->pixmapList[(this->score%1000)/100]);
            painter->drawPixmap(74,
                               260,
                                34,
                                42,
                                this->pixmapList[(this->score%100)/10]);
            painter->drawPixmap(108,260,34,42,
                            this->pixmapList[this->score%10]);
        }
        else if((this->score%100)/10 != 0)
        {
            painter->drawPixmap(40,260,34,42,
                            this->pixmapList[(this->score%100)/10]);
            painter->drawPixmap(74,260,34,42,
                            this->pixmapList[this->score%10]);
        }
        else  painter->drawPixmap(40,260,34,42,
                              this->pixmapList[this->score%10]);


         //best score
        if((this->highestScore%1000)/100 != 0)
        {
           painter->drawPixmap(184.0,260.0,17.0,21.0,
                               this->pixmapList[(this->highestScore%1000)/100]);
           painter->drawPixmap(201.0,260.0,17.0,21.0,
                            this->pixmapList[(this->highestScore%100)/10]);
        }
        else if((this->highestScore%100)/10 != 0)
        {
           painter->drawPixmap(201.0,260.0,17.0,21.0,
                               this->pixmapList[(this->highestScore%100)/10]);
        }
        painter->drawPixmap(218.0,260.0,17.0,21.0,
                        this->pixmapList[this->highestScore%10]);
    }

    //Button
    emit this->buttonVisible(true,true,false);
}

void EleOverBoard::setScore(int _score)
{
    this->score = _score;
    this->highestScore = this->getHighestScore();
    switch(this->score/10)
    {
    case    0:
        this->medal = NONE; break;
    case    1:
        this->medal = COPPERMEDAL;  break;
    case    2:
        this->medal = SILVERMEDAL;  break;
    case    3:
        this->medal = GOLDMEDAL;  break;
    default:
        this->medal = PLATINICMEDAL; break;
    }
}

int EleOverBoard::getHighestScore()
{
    int highestScore;
    if( !QFile::exists("./HighestScore.sc"))
    {
        QFile file;
        file.setFileName("./HighestScore.sc");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream txtStrm(&file);
        txtStrm << this->score <<endl;
        highestScore = this->score;
        file.close();
    }
    else
    {
        QFile file;
        file.setFileName("./HighestScore.sc");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream txtStrm(&file);
        txtStrm >> highestScore ;
        file.close();
        file.remove();

        file.open(QIODevice::WriteOnly | QIODevice::Text);
        if( this->score > highestScore)
        {
            txtStrm << this->score <<endl;
            highestScore = this->score;
        }
        else
        {
            txtStrm << highestScore << endl;
        }
        file.close();
    }
    return highestScore;
}

void EleOverBoard::loadFrame()
{
    this->clearAllFrame();

    this->addFrame(QPixmap(":/image/image/number_score_00.png"));
    this->addFrame(QPixmap(":/image/image/number_score_01.png"));
    this->addFrame(QPixmap(":/image/image/number_score_02.png"));
    this->addFrame(QPixmap(":/image/image/number_score_03.png"));
    this->addFrame(QPixmap(":/image/image/number_score_04.png"));
    this->addFrame(QPixmap(":/image/image/number_score_05.png"));
    this->addFrame(QPixmap(":/image/image/number_score_06.png"));
    this->addFrame(QPixmap(":/image/image/number_score_07.png"));
    this->addFrame(QPixmap(":/image/image/number_score_08.png"));
    this->addFrame(QPixmap(":/image/image/number_score_09.png"));

//
    this->addFrame(QPixmap(":/image/image/gameover1.png"));//10
    this->addFrame(QPixmap(":/image/image/gameover2.png"));//11
    this->addFrame(QPixmap(":/image/image/gameover3.png"));//12
    this->addFrame(QPixmap(":/image/image/gameover4.png"));//13
    this->addFrame(QPixmap(":/image/image/overboard.png"));//14
//
}
