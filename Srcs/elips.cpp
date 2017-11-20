#include "elips.h"

Elips::Elips() {
}

Elips *Elips::elipsWith(float widthV, float hightV, const QPen &pen, const QBrush &brush) {
    Elips* newElips = new Elips;
    newElips->itemWidth = widthV;
    newElips->itemHeight = hightV;
    newElips->item = new QGraphicsEllipseItem(0,0,widthV,hightV);
    newElips->item->setPen(pen);
    newElips->item->setBrush(brush);
    newElips->Node::setGraphicsItem(newElips->item);
    newElips->Node::setW(widthV);
    newElips->Node::setH(hightV);
    newElips->setPos(0,0);
    return newElips;
}

Elips::~Elips() {
}

qreal Elips::getwidth() {
    return itemWidth;
}

qreal Elips::getheight() {
    return itemHeight;
}
