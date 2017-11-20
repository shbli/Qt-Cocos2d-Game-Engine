#ifndef MENUITEMIMAGE_H
#define MENUITEMIMAGE_H

#include "menuitem.h"
#include "spriteitem.h"

template <typename TFuncItem>

class MenuItemImage : public MenuItem
{

public:

    static MenuItemImage* itemWith(const char* image,const char* clicked_image,TFuncItem* target,void (TFuncItem::*toBeNotifiedFunctionPar)()) {
        MenuItemImage<TFuncItem>* newimagebutton = new MenuItemImage<TFuncItem>(QString(image),QString(clicked_image),target,toBeNotifiedFunctionPar,false);
        return newimagebutton;
    }

    static MenuItemImage* itemWithSVG(const char* image,const char* clicked_image ,TFuncItem* target,void (TFuncItem::*toBeNotifiedFunctionPar)(), float scale, Sprite::imageFormat format = Sprite::SPRITE_RBG4444) {
        MenuItemImage<TFuncItem>* newimagebutton = new MenuItemImage<TFuncItem>(QString(image),QString(clicked_image),target,toBeNotifiedFunctionPar,true,scale,format);
        return newimagebutton;
    }

    QString spriteFileName;
    QString spriteFileNameClicked;


private:

    MenuItemImage(const QString &filename,const QString &clickedfilename,TFuncItem* target,void (TFuncItem::*toBeNotifiedFunctionPar)(), bool isVector = 0,float scale = 0, Sprite::imageFormat format = Sprite::SPRITE_RBG4444) {
        spriteFileName = filename;
        spriteFileNameClicked = clickedfilename;
        if (isVector) {
            if (filename.compare(clickedfilename)==0)
                item = new spriteItem(filename,true,scale,"");
            else
                item = new spriteItem(filename,true,scale,clickedfilename);
        } else {
            if (filename.compare(clickedfilename)==0)
                item = new spriteItem(filename,true,"");
            else
                item = new spriteItem(filename,true,clickedfilename);
        }
        Node::setGraphicsItem(item);
        Node::setW(item->width());
        Node::setH(item->height());
        setPos(0,0);
        //item->setTransformOriginPoint(getwidth()/2,getheight()/2);
        item->setParent(this);

        if (target != 0) {
            tagetToBeCalled = target;
            toBeNotifiedFunction = toBeNotifiedFunctionPar;
        }

        setEnabled(0);
        click = false;
        touchable = 0;
    }

    qreal getwidth() {
        return item->width();
    }

    qreal getheight() {
        return item->height();
    }

    bool contains(const QPointF& checkpoint) {
        QPointF point;
        point.setX(checkpoint.x());
        point.setY(checkpoint.y());
        point.setY(Director::sharedDirector()->winSizeInPixels().height() - point.y());
        QPointF pos = item->pos();
        qreal scale = realTimeXScale();

        if (point.x() >= pos.x())
            if (point.x() <= pos.x()+(width()*scale))
                if (point.y() >= pos.y())
                    if (point.y() <= pos.y()+(height()*scale))
                        return true;
        return false;
    }

    TFuncItem* tagetToBeCalled;
    void (TFuncItem::*toBeNotifiedFunction)();
    void buttonClicked() {
        (tagetToBeCalled->*toBeNotifiedFunction)(); // Call member function through pointer which should response to the button action
    }
};

#endif // MENUITEMIMAGE_H
