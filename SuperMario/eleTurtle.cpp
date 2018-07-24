#include"eleTurtle.h"

eleTurtle::eleTurtle(int index,QObject *parent) :
    GameElement(parent)
{
    this->startPosY=index;
    this->init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
}

void eleTurtle::init()
{
    loadFrame();
    this->enabledDraw=true;
    isOn=false;
    this->currentFrame=0;
    this->speedY=-2.5;
    this->timer.start(150);
    this->bindRect.setRect(qrand()%220,582+90*(startPosY%512),68,15);
}

void eleTurtle::draw(QPainter *painter)
{
    if(!enabledDraw)
        return;

    painter->drawPixmap(this->bindRect.x(),this->bindRect.y(),this->bindRect.width(),this->bindRect.height(),this->pixmapList[currentFrame]);
}

void eleTurtle::logic()
{
    if(!enabledLogic)
        return;

    this->bindRect.translate(0,this->speedY);

    if(this->bindRect.bottom()<0)
    {
        emit this->increaseScore();
        this->bindRect.moveTo(qrand()%220,621);
    }
}

void eleTurtle::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/turtle.png"));
    this->addFrame(QPixmap(":/image/image/turtle2.png"));
}

void eleTurtle::updateFrame()
{
    this->currentFrame=(currentFrame+1)%2;
}


