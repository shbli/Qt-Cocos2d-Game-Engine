#include "sprite.h"
#include "spriteitem.h"

Sprite::Sprite(const QString &filename) {
    item = new spriteItem(filename,false,"");
    Node::setGraphicsItem(item);
    Node::setW(item->width());
    Node::setH(item->height());
    setPos(0,0);
}

Sprite::Sprite(const QString &filename, float scaleValue) {
    loadSprite(filename,scaleValue);
}

void Sprite::loadSprite(const QString &filename, float scaleValue) {
    item = new spriteItem(filename,false,scaleValue,"");
    Node::setGraphicsItem(item);
    Node::setW(item->width());
    Node::setH(item->height());
    if (parent) {
        setPos(pos());
        setZ(z());
        setScaleX(scaleX());
        setScaleY(scaleY());
        setOpacity(opacity());
        setRotation(rotation());
        // if this is actually some item, ie, not a layer nor a scene, we'll add it to the view
        Director::sharedDirector()->sharedGraphicScene()->addItem(item);
    }
}

Sprite::~Sprite() {
    //deleting item will make the app crash, because it's already being deleted in the node class else
    //    delete item;
}

qreal Sprite::getwidth() {
    return item->width();
}

qreal Sprite::getheight() {
    return item->height();
}

Sprite* Sprite::spriteWithImage(const char* filename) {
    Sprite* newsprite = new Sprite(QString(filename));

    newsprite->SpriteFileName = filename;
    return newsprite;
}

Sprite *Sprite::spriteWithSvg(const char *filename, float scaleValue, bool saveToCache, imageFormat format)
{
    Sprite* newsprite = new Sprite(QString(filename),scaleValue);

    newsprite->SpriteFileName = filename;
    return newsprite;
}
