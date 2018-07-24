#ifndef ELETURTLE_H
#define ELETURTLE_H

#include"gameelement.h"
#include"QTimer"

class eleTurtle : public GameElement
{
    Q_OBJECT
private:
    int startPosX;
    int startPosY;
    float speedY;
    QTimer timer;
    int currentFrame;

    void loadFrame();
public:
    bool isOn;

    explicit eleTurtle(int index,QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
signals:
    void increaseScore();
public slots:
    void updateFrame();
};

#endif // ELETURTLE_H
