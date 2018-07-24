#include "elereadyboard.h"

EleReadyBoard::EleReadyBoard(QObject *parent) :
    GameElement(parent)
{

    this->loadFrame();
    this->init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
    timer.start(150);
}

void EleReadyBoard::init()
{
    this->lastFrame = 6;
    this->currentFrame = 7;
}
void EleReadyBoard::logic()
{
    if(!this->enabledLogic)
        return;
}
void EleReadyBoard::updateFrame()
{
    if( !this->enabledDraw )
        return;

    if(this->currentFrame > this->lastFrame)
    {
        this->lastFrame = this->currentFrame;
        this->currentFrame--;
    }
    else if(this->currentFrame < this->lastFrame)
    {
        this->lastFrame = this->currentFrame;
        this->currentFrame++;
    }

    if(this->currentFrame<6 || this->currentFrame>7)
        this->currentFrame = 6;
}


void EleReadyBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;
    painter->drawPixmap(45.0,145.0,197.0,63.0,  //text_ready
                        this->pixmapList[0]);
    painter->drawPixmap(76.5,240.0,40.0,40.0,   //arrow_left1black
                        this->pixmapList[1]);
    painter->drawPixmap(156.5,240.0,40.0,40.0,  //arrow_right1black
                        this->pixmapList[2]);
    painter->drawPixmap(26.5,240.0,40.0,40.0,  //A
                        this->pixmapList[3]);
    painter->drawPixmap(206.5,240.0,40.0,40.0,   //D
                        this->pixmapList[4]);
    painter->drawPixmap(166.5,300.0,60.0,60.0,  //bomb
                        this->pixmapList[5]);
    painter->drawPixmap(46.5,320.0,68.0,16.0,  //turtle1
                        this->pixmapList[this->currentFrame]);
    painter->drawPixmap(126.5,310.0,40.0,40.0,   //arrow_right3
                        this->pixmapList[8]);


}
void EleReadyBoard::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/text_ready.png")); //0
    this->addFrame(QPixmap(":/image/image/arrow_left1black.png")); //1
    this->addFrame(QPixmap(":/image/image/arrow_right1black.png"));//2
    this->addFrame(QPixmap(":/image/image/A.png"));//3
    this->addFrame(QPixmap(":/image/image/D.png"));//4
    this->addFrame(QPixmap(":/image/image/bomb.png"));//5
    this->addFrame(QPixmap(":/image/image/turtle.png"));//6
    this->addFrame(QPixmap(":/image/image/turtle2.png"));//7
    this->addFrame(QPixmap(":/image/image/arrow_right3.png"));//8
}
