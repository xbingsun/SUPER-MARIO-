#include "MyWidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    QGraphicsPixmapItem* pixmapItem1;

    _view=new QGraphicsView(this);
    _view->setScene(_scene=new QGraphicsScene);
    _view->resize(1920,1080);

    _scene->addItem(pixmapItem1=new QGraphicsPixmapItem(QPixmap(":/image/image/000.png")));
    pixmapItem1->setPos(0,0);
}
