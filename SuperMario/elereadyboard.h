#ifndef ELEREADYBOARD_H
#define ELEREADYBOARD_H

#include "gameelement.h"
#include"QTimer"

class EleReadyBoard : public GameElement
{
    Q_OBJECT
private:
    QTimer timer;
    int lastFrame;
    int currentFrame;
    void loadFrame();
public:
    explicit EleReadyBoard(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
signals:

public slots:
    void updateFrame();
};

#endif // ELEREADYBOARD_H
