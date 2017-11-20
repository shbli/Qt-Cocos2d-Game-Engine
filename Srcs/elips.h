#ifndef ELIPS_H
#define ELIPS_H

#include "node.h"

class Elips : public Node
{
protected:
    Elips();

public:
    static Elips* elipsWith(float width, float hight,const QPen & pen = QPen(), const QBrush & brush = QBrush());
    ~Elips();
private:
    QGraphicsEllipseItem* item;
    QGraphicsScene* getSharedGraphicScene(){ return 0; }
    void setSharedGraphicScene(QGraphicsScene* graphicscene){ return; }
    qreal getwidth();
    qreal getheight();
    float itemWidth;
    float itemHeight;
    QGraphicsItem* getGraphicsItem(){ return Node::getGraphicsItem(); }
    void setGraphicsItem(QGraphicsItem* item) { return;}
    void setW(qreal w) {}
    void setH(qreal h) {}

};

#endif // ELIPS_H
