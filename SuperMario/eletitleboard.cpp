#include "eletitleboard.h"

EleTitleBoard::EleTitleBoard(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
    timer.start(150);
}

void EleTitleBoard::init()
{
    this->lastFrame = 0;
    this->currentFrame = 1;

}

void EleTitleBoard::logic()
{
    if(!this->enabledLogic)
        return;
}

void EleTitleBoard::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(54.5,120.0,200.0,90.0,
                        this->pixmapList[3]);

    painter->drawPixmap(119.5,220.0,49.0,49.0,
                        this->pixmapList[this->currentFrame]);
}

void EleTitleBoard::updateFrame()
{
    if( !this->enabledDraw )
        return;

    if(this->currentFrame > this->lastFrame)
    {
        this->lastFrame = this->currentFrame;
        this->currentFrame++;
    }
    else if(this->currentFrame < this->lastFrame)
    {
        this->lastFrame = this->currentFrame;
        this->currentFrame--;
    }

    if(this->currentFrame<0 || this->currentFrame>2)
        this->currentFrame = 1;
}

void EleTitleBoard::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/PlayerWalk01.png"));
    this->addFrame(QPixmap(":/image/image/PlayerWalk02.png"));
    this->addFrame(QPixmap(":/image/image/PlayerWalk03.png"));
    this->addFrame(QPixmap(":/image/image/title.png"));
}
