#include "textitem.h"

textItem::textItem() {
    setFlag(QGraphicsItem::ItemIsMovable,0);
    setFlag(QGraphicsItem::ItemIsSelectable,0);
    setFlag(QGraphicsItem::ItemIsFocusable,0);
    setFlag(QGraphicsItem::ItemIgnoresTransformations,0);
    setFlag(QGraphicsItem::ItemIgnoresParentOpacity,0);
    setFlag(QGraphicsItem::ItemAcceptsInputMethod,0);
    setFlag(QGraphicsItem::ItemNegativeZStacksBehindParent,0);
    setEnabled(0);
}

qreal textItem::height() {
    return document()->size().height();
}
qreal textItem::width() {
    return document()->size().width();
}

