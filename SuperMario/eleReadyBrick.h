#ifndef ELEREADYBRICK_H
#define ELEREADYBRICK_H

#include"gameelement.h"

class eleReadyBrick : public GameElement
{
    Q_OBJECT
private:
    float speedY;
    int currentFrame;

    void loadFrame();
public:
    bool isOn;

    explicit eleReadyBrick(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

};
#endif // ELEREADYBRICK_H
