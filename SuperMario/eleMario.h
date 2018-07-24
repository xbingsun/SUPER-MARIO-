#ifndef ELEMARIO_H
#define ELEMARIO_H

#include <QTimer>
#include "gameelement.h"

class eleMario : public GameElement
{
    Q_OBJECT
private:
    int idleFrame;
    int fallFrame;
    int lastFrame;
    int currrentFrame;
    float speedX;
    float increaseSpeedY;
    QTimer timer;
    float speedY;
    void loadFrame();
public:

    explicit eleMario(QObject *parent = 0);
    void init();
    void logic();
    void draw(QPainter *);
    void setLevel(int i);
    void initspeedY();

    bool isLeft;
    bool isPlayLeft;
    bool isRight;
    bool isPlayRight;
    bool enabledMove;
    bool enabledFall;
    bool isDie;


public slots:
    void updateFrame();
    /*void setEasy();
    void setMedium();
    void setHigh();*/
};

#endif // ELEMARIO_H
