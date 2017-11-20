#ifndef TOUCHHANDLER_H
#define TOUCHHANDLER_H

#include "game_engine.h"

class TouchHandler
{

public:
    static TouchHandler* SharedHandler();
    void addToTouchHandler(Node & touchObject);
    void removeToTouchHandler(Node & touchObject);

    void sendTouchBeginEvent(QGraphicsSceneMouseEvent* event);
    void sendTouchMoveEvent(QGraphicsSceneMouseEvent* event);
    void sendTouchEndEvent(QGraphicsSceneMouseEvent* event);

private:
    QList <Node*> touchEnabledNodesVeryLow;
    QList <Node*> touchEnabledNodesLow;
    QList <Node*> touchEnabledNodesNormal;
    QList <Node*> touchEnabledNodesHigh;
    QList <Node*> touchEnabledNodesVeryHigh;
    TouchHandler();
    static TouchHandler* SharedHandlerObject;
};

#endif // TOUCHHANDLER_H
