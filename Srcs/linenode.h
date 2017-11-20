#ifndef LINENODE_H
#define LINENODE_H

#include "node.h"

class lineNode : public Node
{
protected:
    lineNode();
public:
    static lineNode* lineWithPen(const QPen & pen = QPen());
    float x1() { return item->line().x1(); }
    float x2() { return item->line().x2(); }
    float y1() { return -item->line().y1(); }
    float y2() { return -item->line().y2(); }
    void setLineEndPoints(float x1,float y1,float x2,float y2);
    void setPen(QPen pen);


private:
    QGraphicsLineItem* item;
    QGraphicsScene* getSharedGraphicScene(){ return 0; }
    void setSharedGraphicScene(QGraphicsScene* graphicscene){ return; }
    qreal getwidth(){ return 0;}
    qreal getheight(){ return 0;}
    QGraphicsItem* getGraphicsItem(){ return Node::getGraphicsItem(); }
    void setGraphicsItem(QGraphicsItem* item) { return;}
    void setW(qreal w) {}
    void setH(qreal h) {}
    void setLineFlags();
};

#endif // LINENODE_H
