#include "graphicsscene.h"
#include "QDebug"
#include <QGraphicsSceneMouseEvent>
#include "director.h"
#include "touchhandler.h"
//#include <shared_storage.h>

graphicsScene::graphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mouseDown = 0;
    setSceneRect(0,0,Director::sharedDirector()->winSizeInPixels().width(),Director::sharedDirector()->winSizeInPixels().height());
    setItemIndexMethod(QGraphicsScene::NoIndex);


}

graphicsScene::~graphicsScene() {
    //shared_storage::sharedGameStorage()->gameHasEnd();
}

void graphicsScene::invalidate(const QRectF &rect, QGraphicsScene::SceneLayers layers) {
    QGraphicsScene::invalidate(rect,QGraphicsScene::ItemLayer);
}

void graphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    TouchHandler::SharedHandler()->sendTouchBeginEvent(event);
    mouseDown = true;
}
void graphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (mouseDown)
        TouchHandler::SharedHandler()->sendTouchMoveEvent(event);
}
void graphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    TouchHandler::SharedHandler()->sendTouchEndEvent(event);
    mouseDown = false;
}

void graphicsScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        //run the key escape
        Director::sharedDirector()->onBackKeyEvent();
    }
}

void graphicsScene::gameEnded() {
    //shared_storage::sharedGameStorage()->gameHasEnd();
}
