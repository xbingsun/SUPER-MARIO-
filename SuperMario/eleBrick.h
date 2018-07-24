#ifndef ELEBRICK_H
#define ELEBRICK_H

#include"gameelement.h"

class eleBrick : public GameElement
{
    Q_OBJECT
private:
    int startPosX;
    int startPosY;
    float speedY;
    int currentFrame;

    void loadFrame();
public:
    bool isOn;

    explicit eleBrick(int index,QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
signals:
    void increaseScore();

};

#endif // ELEBRICK_H
