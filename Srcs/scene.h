#ifndef SCENE_H
#define SCENE_H
#include "QGraphicsScene"
#include "node.h"

class Scene : public Node
{
public:
    static Scene *node();
    int getGlobalMaxZ(){ return Node::getGlobalMaxZ(); }
    Node *mainLayer;
    void addChild(Node *child, int tag = 0, int z = 0) {
        mainLayer = child;
        Node::addChild(child,tag,z);
    }
    ~Scene();
private:
    Scene();
    QGraphicsScene* getSharedGraphicScene(){ return 0; }
    void setSharedGraphicScene(QGraphicsScene* graphicscene){ return; }
    qreal getwidth(){ return 0; }
    qreal getheight(){ return 0; }
    QGraphicsItem* getGraphicsItem(){ return Node::getGraphicsItem(); }
    void setGraphicsItem(QGraphicsItem* item) { return;}
    void setW(qreal w) {}
    void setH(qreal h) {}

};

#endif // SCENE_H
