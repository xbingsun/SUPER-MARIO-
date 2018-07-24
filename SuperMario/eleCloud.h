#ifndef ELECLOUD_H
#define ELECLOUD_H

#include"gameelement.h"

class eleCloud : public GameElement
{
    Q_OBJECT
private:
    int startPosX;
    int startPosY;
    float speedX;
    float speedY;
    int currentFrame;

    void loadFrame();
public:
    bool isOn;

    explicit eleCloud(int index,QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
signals:
    void increaseScore();

};

#endif // ELECLOUD_H
