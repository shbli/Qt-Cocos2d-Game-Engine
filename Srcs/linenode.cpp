#include "linenode.h"

lineNode::lineNode() {

}

lineNode *lineNode::lineWithPen(const QPen &pen) {
    lineNode* newLine = new lineNode;
    newLine->item = new QGraphicsLineItem();
    newLine->item->setPen(pen);
    newLine->Node::setGraphicsItem(newLine->item);
    return newLine;
}

void lineNode::setLineEndPoints(float x1, float y1, float x2, float y2) {
    item->setLine(x1,-y1,x2,-y2);
}

void lineNode::setLineFlags() {
    item->setFlag(QGraphicsItem::ItemSendsGeometryChanges,0);
    item->setFlag(QGraphicsItem::ItemIsMovable,0);
    item->setFlag(QGraphicsItem::ItemIsSelectable,0);
    item->setFlag(QGraphicsItem::ItemIsFocusable,0);
    item->setFlag(QGraphicsItem::ItemIgnoresTransformations,1);
    item->setFlag(QGraphicsItem::ItemIgnoresParentOpacity,1);
    item->setFlag(QGraphicsItem::ItemAcceptsInputMethod,0);
    item->setFlag(QGraphicsItem::ItemNegativeZStacksBehindParent,0);
    item->setEnabled(0);
    item->setCacheMode(QGraphicsItem::NoCache);
}

void lineNode::setPen(QPen pen) {
    item->setPen(pen);
}
