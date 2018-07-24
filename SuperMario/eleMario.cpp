#include "eleMario.h"
#include"QDebug"
eleMario::eleMario(QObject *parent) :
    GameElement(parent)
{
    this->init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
}

void eleMario::init()
{
    this->isDie=false;
    this->loadFrame();
    this->fallFrame=4;
    this->lastFrame=1;
    this->currrentFrame=0;
    this->speedX=3;
    //this->speedY=2.5;
    this->increaseSpeedY=0.02;
    this->enabledMove=false;
    this->enabledFall=false;
    this->isLeft=false;
    this->isRight=false;
    this->isPlayLeft=false;
    this->isPlayRight=false;
    //........test
    this->bindRect.setRect(138,240+120,16,16);
    this->timer.start(50);
}

void eleMario::logic()
{
    if(!this->enabledLogic)
        return;
    //move
    if(this->enabledMove)
    {
        if(this->isLeft&&this->getBindRect().left()>0)
        {
            this->bindRect.translate(-this->speedX,0);
            this->isPlayLeft=true;
        }
        else
            this->isPlayLeft=false;
        if(this->isRight&&this->getBindRect().right()<288)
        {
            this->bindRect.translate(this->speedX,0);
            this->isPlayRight=true;
        }
        else
            this->isPlayRight=false;
    }
    //fall
    if(this->enabledFall)
    {
        this->bindRect.translate(0,this->speedY);
        this->currrentFrame=this->fallFrame;
    }
    else
    {
        this->bindRect.translate(0,-2.5);
        if(this->isPlayLeft==false&&this->isPlayRight==false)
            this->currrentFrame=0;
    }
}

void eleMario::draw(QPainter *painter)
{
    if(!enabledDraw)
        return;
     painter->drawPixmap(this->bindRect.x(),this->bindRect.y(),this->bindRect.width(),this->bindRect.height(),this->pixmapList[this->currrentFrame]);
}

void eleMario::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/PlayerIdle.png"));

    this->addFrame(QPixmap(":/image/image/PlayerWalk01.png"));
    this->addFrame(QPixmap(":/image/image/PlayerWalk02.png"));
    this->addFrame(QPixmap(":/image/image/PlayerWalk03.png"));

    this->addFrame(QPixmap(":/image/image/PlayerDie.png"));

    this->addFrame(QPixmap(":/image/image/PlayerWalkLeft01.png"));
    this->addFrame(QPixmap(":/image/image/PlayerWalkLeft02.png"));
    this->addFrame(QPixmap(":/image/image/PlayerWalkLeft03.png"));

}

void eleMario::updateFrame()
{
    if(this->isPlayRight)
    {
        if(this->currrentFrame==0)
        {
            this->currrentFrame=2;
            this->lastFrame=1;
        }
        if(this->currrentFrame > this->lastFrame)
        {
            this->lastFrame = this->currrentFrame;
            this->currrentFrame++;
        }
        else if(this->currrentFrame < this->lastFrame)
        {
            this->lastFrame = this->currrentFrame;
            this->currrentFrame--;
        }

        if(this->currrentFrame<1 || this->currrentFrame>3)
            this->currrentFrame = 2;
    }
    if(this->isPlayLeft)
    {
        if(this->currrentFrame==0)
        {
            this->currrentFrame=6;
            this->lastFrame=5;
        }
        if(this->currrentFrame > this->lastFrame)
        {
            this->lastFrame = this->currrentFrame;
            this->currrentFrame++;
        }
        else if(this->currrentFrame < this->lastFrame)
        {
            this->lastFrame = this->currrentFrame;
            this->currrentFrame--;
        }

        if(this->currrentFrame<5 || this->currrentFrame>7)
              this->currrentFrame = 6;
    }
}

void eleMario::setLevel(int i)
{
    if(i==1)
        this->speedY=2.5;
    if(i==2)
        this->speedY=3.5;
    if(i==3)
        this->speedY=4;
}
void eleMario::initspeedY()
{
    this->speedY=2.5;
}
