#ifndef LAYER_H
#define LAYER_H
#include <QGraphicsScene>
#include "node.h"

class Layer : public Node
{
public:
    static Layer* node();
protected:
    Layer();
private:
    QGraphicsScene* getSharedGraphicScene(){ return 0; }
    void setSharedGraphicScene(QGraphicsScene* graphicscene){ return; }
    QGraphicsItem* getGraphicsItem(){ return 0; }
    void setGraphicsItem(QGraphicsItem* item) { return;}
};

#endif // LAYER_H
