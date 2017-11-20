#ifndef LABEL_H
#define LABEL_H

#include "textitem.h"
#include "game_engine.h"

class Label : public Node
{
public:
    static Label* LabelWithText(QString string, QColor *color = 0, int fontSize = 16, QString font = "Times");
    void setText(QString text);
    ~Label();
private:
    Label(QString string, QColor *color,int fontSize, QString font);
    QGraphicsScene* getSharedGraphicScene(){ return 0; }
    void setSharedGraphicScene(QGraphicsScene* graphicscene){ return; }
    qreal getwidth();
    qreal getheight();
    QGraphicsItem* getGraphicsItem(){ return Node::getGraphicsItem(); }
    void setGraphicsItem(QGraphicsItem* item) { return;}
    textItem* labelItem;
    void setW(qreal w) {}
    void setH(qreal h) {}
};

#endif // LABEL_H
