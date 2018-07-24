#include"eleflower.h"

eleFlower::eleFlower(QObject *parent) :
    GameElement(parent)
{
    this->init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
}

void eleFlower::init()
{
    this->loadFrame();
    this->currentFrame=0;
    this->bindRect.setRect(0,10,288,23);
    timer.start(150);
}

void eleFlower::logic()
{
    if(!enabledLogic)
        return;
    return;
}

void eleFlower::draw(QPainter *painter)
{
    if(!enabledDraw)
        return;
    painter->drawPixmap(this->bindRect.x(),this->bindRect.y(),this->bindRect.width(),this->bindRect.height(),this->pixmapList[currentFrame]);
}

void eleFlower::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/flower_1.png"));
    this->addFrame(QPixmap(":/image/image/flower_2.png"));
}

void eleFlower::updateFrame()
{
    this->currentFrame=(currentFrame+1)%2;
}
