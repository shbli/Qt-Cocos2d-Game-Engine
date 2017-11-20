#ifndef MYFASTERGRAPHICVIEW_H
#define MYFASTERGRAPHICVIEW_H

#include <QGraphicsView>
#include <QPaintEvent>

class MyFasterGraphicView :public QGraphicsView
{
Q_OBJECT
public:
MyFasterGraphicView(QRect deskSize){
    winSize = deskSize;
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing,true);
}
protected:
void paintEvent ( QPaintEvent * event ) {
//    QPaintEvent *newEvent=new QPaintEvent(event->region().boundingRect());
    QPaintEvent *newEvent=new QPaintEvent(winSize);
    QGraphicsView::paintEvent(newEvent);
    delete newEvent;
    }
private:
    QRect winSize;
};

#endif // MYFASTERGRAPHICVIEW_H
