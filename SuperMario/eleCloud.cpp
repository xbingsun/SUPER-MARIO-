#include"eleCloud.h"

eleCloud::eleCloud(int index,QObject *parent) :
    GameElement(parent)
{
    this->startPosY=index;
    this->init();
}

void eleCloud::init()
{
    loadFrame();
    this->enabledDraw=true;
    isOn=false;
    this->currentFrame=0;
    this->speedX=2.5;
    this->speedY=-2.5;
    this->bindRect.setRect(qrand()%220,582+90*(startPosY%512),64,22);
}

void eleCloud::draw(QPainter *painter)
{
    if(!enabledDraw)
        return;

    painter->drawPixmap(this->bindRect.x(),this->bindRect.y(),this->bindRect.width(),this->bindRect.height(),this->pixmapList[0]);
}

void eleCloud::logic()
{
    if(!enabledLogic)
        return;

    this->bindRect.translate(this->speedX,this->speedY);

    if(this->bindRect.bottom()<0)
    {
        emit this->increaseScore();
        this->bindRect.moveTo(qrand()%220,621);
    }
    if(this->bindRect.left()<0)
        this->speedX*=-1;
    if(this->bindRect.right()>288)
        this->speedX*=-1;
}

void eleCloud::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/cloud.png"));
}



