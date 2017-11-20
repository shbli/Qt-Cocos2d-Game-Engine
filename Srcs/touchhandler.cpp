#include "touchhandler.h"

TouchHandler* TouchHandler::SharedHandlerObject = 0;

TouchHandler *TouchHandler::SharedHandler() {
    if (SharedHandlerObject == 0) {
        SharedHandlerObject = new TouchHandler;
    }
    return SharedHandlerObject;
}

void TouchHandler::addToTouchHandler(Node & touchObject) {
    touchEnabledNodesVeryLow.removeOne(&touchObject);
    touchEnabledNodesLow.removeOne(&touchObject);
    touchEnabledNodesNormal.removeOne(&touchObject);
    touchEnabledNodesHigh.removeOne(&touchObject);
    touchEnabledNodesVeryHigh.removeOne(&touchObject);

    if (touchObject.getNodeTouchPiority() == Node::veryLow) {
        touchEnabledNodesVeryLow.append(&touchObject);
    }
    if (touchObject.getNodeTouchPiority() == Node::low) {
        touchEnabledNodesLow.append(&touchObject);
    }
    if (touchObject.getNodeTouchPiority() == Node::normal) {
        touchEnabledNodesNormal.append(&touchObject);
    }
    if (touchObject.getNodeTouchPiority() == Node::high) {
        touchEnabledNodesHigh.append(&touchObject);
    }
    if (touchObject.getNodeTouchPiority() == Node::veryhigh) {
        touchEnabledNodesVeryHigh.append(&touchObject);
    }
}

void TouchHandler::removeToTouchHandler(Node & touchObject) {
    touchEnabledNodesVeryLow.removeOne(&touchObject);
    touchEnabledNodesLow.removeOne(&touchObject);
    touchEnabledNodesNormal.removeOne(&touchObject);
    touchEnabledNodesHigh.removeOne(&touchObject);
    touchEnabledNodesVeryHigh.removeOne(&touchObject);
}

TouchHandler::TouchHandler() {

}

void TouchHandler::sendTouchEndEvent(QGraphicsSceneMouseEvent *event) {
    Node* newNode;
    QPointF touchPosition = Director::sharedDirector()->convertTouchPoint(event->scenePos());

    //call touches from highest to lowest
    for (int i = 0; i < touchEnabledNodesVeryHigh.count(); i++) {
        newNode = touchEnabledNodesVeryHigh.at(i);
        newNode->touchEnd(touchPosition);
    }

    for (int i = 0; i < touchEnabledNodesHigh.count(); i++) {
        newNode = touchEnabledNodesHigh.at(i);
        newNode->touchEnd(touchPosition);
    }


    for (int i = 0; i < touchEnabledNodesNormal.count(); i++) {
        newNode = touchEnabledNodesNormal.at(i);
        newNode->touchEnd(touchPosition);
    }


    for (int i = 0; i < touchEnabledNodesLow.count(); i++) {
        newNode = touchEnabledNodesLow.at(i);
        newNode->touchEnd(touchPosition);
    }


    for (int i = 0; i < touchEnabledNodesVeryLow.count(); i++) {
        newNode = touchEnabledNodesVeryLow.at(i);
        newNode->touchEnd(touchPosition);
    }
}

void TouchHandler::sendTouchMoveEvent(QGraphicsSceneMouseEvent *event) {
    Node* newNode;
    QPointF touchPosition = Director::sharedDirector()->convertTouchPoint(event->scenePos());

    //call touches from highest to lowest
    for (int i = 0; i < touchEnabledNodesVeryHigh.count(); i++) {
        newNode = touchEnabledNodesVeryHigh.at(i);
        newNode->touchMove(touchPosition);
    }

    for (int i = 0; i < touchEnabledNodesHigh.count(); i++) {
        newNode = touchEnabledNodesHigh.at(i);
        newNode->touchMove(touchPosition);
    }


    for (int i = 0; i < touchEnabledNodesNormal.count(); i++) {
        newNode = touchEnabledNodesNormal.at(i);
        newNode->touchMove(touchPosition);
    }


    for (int i = 0; i < touchEnabledNodesLow.count(); i++) {
        newNode = touchEnabledNodesLow.at(i);
        newNode->touchMove(touchPosition);
    }


    for (int i = 0; i < touchEnabledNodesVeryLow.count(); i++) {
        newNode = touchEnabledNodesVeryLow.at(i);
        newNode->touchMove(touchPosition);
    }
}

void TouchHandler::sendTouchBeginEvent(QGraphicsSceneMouseEvent *event) {
    Node* newNode;
    QPointF touchPosition = Director::sharedDirector()->convertTouchPoint(event->scenePos());

    //call touches from highest to lowest
    for (int i = 0; i < touchEnabledNodesVeryHigh.count(); i++) {
        newNode = touchEnabledNodesVeryHigh.at(i);
        newNode->touchBegin(touchPosition);
    }

    for (int i = 0; i < touchEnabledNodesHigh.count(); i++) {
        newNode = touchEnabledNodesHigh.at(i);
        newNode->touchBegin(touchPosition);
    }


    for (int i = 0; i < touchEnabledNodesNormal.count(); i++) {
        newNode = touchEnabledNodesNormal.at(i);
        newNode->touchBegin(touchPosition);
    }


    for (int i = 0; i < touchEnabledNodesLow.count(); i++) {
        newNode = touchEnabledNodesLow.at(i);
        newNode->touchBegin(touchPosition);
    }


    for (int i = 0; i < touchEnabledNodesVeryLow.count(); i++) {
        newNode = touchEnabledNodesVeryLow.at(i);
        newNode->touchBegin(touchPosition);
    }

}
