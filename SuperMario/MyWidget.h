#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsPixmapItem>
#include<QGraphicsTextItem>
#include<QGraphicsItemAnimation>
#include<QTimeLine>
#include<QString>

class MyWidget : public QWidget
{
    Q_OBJECT
private:
    QGraphicsScene* _scene;
    QGraphicsView* _view;

public:
    explicit MyWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // MYWIDGET_H
