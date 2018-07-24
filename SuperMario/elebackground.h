#ifndef ELEBACKGROUND_H
#define ELEBACKGROUND_H

#include "gameelement.h"

class EleBackground : public GameElement
{
    Q_OBJECT
private:
    void loadFrame();
public:
    explicit EleBackground(QObject *parent = 0);
    int currentFrame;
    void init();
    void draw(QPainter *);
    void logic();
};

#endif // ELEBACKGROUND_H
