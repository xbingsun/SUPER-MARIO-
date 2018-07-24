#include "eleBrick.h"

eleBrick::eleBrick(int index,QObject *parent) :
    GameElement(parent)
{
    this->startPosY=index;
    this->init();
}

void eleBrick::init()
{
    loadFrame();
    this->enabledDraw=true;
    isOn=false;
    this->currentFrame=0;
    this->speedY=-2.5;
    this->bindRect.setRect(qrand()%220,582+90*(startPosY%512),68,18);
}

void eleBrick::draw(QPainter *painter)
{
    if(!enabledDraw)
        return;

    painter->drawPixmap(this->bindRect.x(),this->bindRect.y(),this->bindRect.width(),this->bindRect.height(),this->pixmapList[0]);
}

void eleBrick::logic()
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

void eleBrick::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/brick.png"));
}



