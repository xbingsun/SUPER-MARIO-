#include "eleReadyBrick.h"

eleReadyBrick::eleReadyBrick(QObject *parent) :
    GameElement(parent)
{
    this->init();
}

void eleReadyBrick::init()
{
    loadFrame();
    this->enabledDraw=true;
    isOn=false;
    this->currentFrame=0;
    this->speedY=-2.5;
    this->bindRect.setRect(110,256+120+5,68,18);
}

void eleReadyBrick::draw(QPainter *painter)
{
    if(!enabledDraw)
        return;

    painter->drawPixmap(this->bindRect.x(),this->bindRect.y(),this->bindRect.width(),this->bindRect.height(),this->pixmapList[0]);
}

void eleReadyBrick::logic()
{
    if(!enabledLogic)
        return;

    this->bindRect.translate(0,this->speedY);

    if(this->bindRect.bottom()<-20)
    {
        this->enabledLogic=false;
    }
}

void eleReadyBrick::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/brick.png"));
}




