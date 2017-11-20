#ifndef SPRITE_H
#define SPRITE_H
#include "node.h"

class spriteItem;

class Sprite : public Node {

protected:
    Sprite() {
        item = 0;
    }
    Sprite(const QString &filename);
    Sprite(const QString &filename,float scaleValue);
    void loadSprite(const QString &filename,float scaleValue);

public:

    bool isImageLoaded() {
        return item;
    }

    enum imageFormat {
        SPRITE_RBG8888,
        SPRITE_RBG4444,
        SPRITE_RBG565
    };

    static Sprite* spriteWithImage(const char* filename);
    QString SpriteFileName;
    static Sprite* spriteWithSvg(const char* filename,float scaleValue,bool saveToCache = true,imageFormat format = SPRITE_RBG4444);
    ~Sprite();
private:
    spriteItem* item;
    QGraphicsScene* getSharedGraphicScene(){ return 0; }
    void setSharedGraphicScene(QGraphicsScene* graphicscene){ return; }
    qreal getwidth();
    qreal getheight();
    QGraphicsItem* getGraphicsItem(){ return Node::getGraphicsItem(); }
    void setGraphicsItem(QGraphicsItem* item) { return;}
    void setW(qreal w) {}
    void setH(qreal h) {}
};

#endif // SPRITE_H
