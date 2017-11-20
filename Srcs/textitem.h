#ifndef TEXTITEM_H
#define TEXTITEM_H
#include <QGraphicsTextItem>
#include <QTextDocument>

class textItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit    textItem();
    qreal width();
    qreal height();
};

#endif // TEXTITEM_H
