#include "menuitem.h"
#include "spriteitem.h"
#include <QGraphicsSceneMouseEvent>
#include "graphicsscene.h"
#include "touchhandler.h"

MenuItem::MenuItem() {
    clickedFirst = false;
}

void MenuItem::setEnabled(bool val) {
    item->setEnabled(val);
    if (val&&!touchable) {
        touchable = true;
        TouchHandler::SharedHandler()->addToTouchHandler(*this);
    }
    if (!val&&touchable) {
        touchable = false;
        TouchHandler::SharedHandler()->removeToTouchHandler(*this);
    }
}

void MenuItem::touchMove(const QPointF& touchPosition) {
    if (touchable) {
        if (!click) {
            //we have to check if our finger is on our item
            if (contains(touchPosition)) {
                item->setClickedImage();
                click = true;
            }
        }
        else {
            //item is already click, we have to check if finger is out
            //we have to check if our finger is on our item
            if (!contains(touchPosition)) {
                item->setNormalImage();
                click = false;
                clickedFirst = false;
            }
        }
    }
}

void MenuItem::touchEnd(const QPointF& touchPosition) {

    if (click) {
        item->setNormalImage();
        click = false;
    }

    if (clickedFirst) {
        if (touchable && contains(touchPosition)) {
            // our item is clicked, do something
            clickedFirst = false;
            buttonClicked();

        }
    }

}
