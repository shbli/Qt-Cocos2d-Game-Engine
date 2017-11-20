#ifndef MENUITEM_H
#define MENUITEM_H

#include "sprite.h"


class MenuItem : public Node
{
    Q_OBJECT


protected:
    bool touchable;
    bool click;
    spriteItem* item;

public:
    MenuItem();

    virtual void setEnabled(bool val);


private:
    QGraphicsScene* getSharedGraphicScene(){ return 0; }
    void setSharedGraphicScene(QGraphicsScene* graphicscene){ return; }
    QGraphicsItem* getGraphicsItem(){ return 0; }
    void setGraphicsItem(QGraphicsItem* item) { return;}
    void setW(qreal w) {}
    void setH(qreal h) {}    

public slots:
    virtual void touchBegin(const QPointF& touchPosition) {
        if (touchable && contains(touchPosition)) {
            // our item is clicked, do something
            clickedFirst = true;
        }

        touchMove(touchPosition);
    }

    virtual void touchMove(const QPointF& touchPosition);
    virtual void touchEnd(const QPointF& touchPosition);

private:

    bool clickedFirst;

    virtual bool contains(const QPointF& point) = 0;
    virtual void buttonClicked() = 0;

};

#endif // MENUITEM_H
