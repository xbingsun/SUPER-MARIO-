#ifndef ELEFLOWER_H
#define ELEFLOWER_H

#include"gameelement.h"
#include<QTimer>

class eleFlower : public GameElement
{
    Q_OBJECT
private:
    int currentFrame;

    void loadFrame();
public:
    explicit eleFlower(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

    QTimer timer;

public slots:
    void updateFrame();
};

#endif // ELEFLOWER_H
