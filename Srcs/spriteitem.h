#ifndef SPRITEITEM_H
#define SPRITEITEM_H
#include <QEvent>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmapCache>
#include "menuitem.h"


class spriteItem : public QGraphicsPixmapItem
{

public:
    spriteItem(const QString &filename, bool button, const QString &clickedFileName);

    //below constructor is only used to load svg files to pixmaps, please don't use it to load png or jpg files
    spriteItem(const QString &filename, bool button,float scaleValu, const QString &clickedFileName);
    ~spriteItem();
    qreal width();
    qreal height();
    void setClickedImage(){ setPixmap(clicked);}
    void setNormalImage(){ setPixmap(normal); }
    void setParent(MenuItem *parent);
protected:

private:
    void setSpriteFlags();
    MenuItem *parentMenuItem;
    QPixmap normal;
    QPixmap clicked;

};

#endif // SPRITEITEM_H
