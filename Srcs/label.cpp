#include "label.h"

Label::Label(QString string, QColor *color, int fontSize, QString font) {

    labelItem = new textItem;
    labelItem->setPlainText(string);
    if (color == 0)
        labelItem->setDefaultTextColor(QColor(255,255,255,255));
    else
        labelItem->setDefaultTextColor(*color);
    QFont newfont(font,fontSize);
    newfont.setPixelSize(newfont.pointSize());
    newfont.setBold(true);
    labelItem->setFont(newfont);
    Node::setGraphicsItem(labelItem);
    Node::setW(labelItem->width());
    Node::setH(labelItem->height());
    setPos(0,0);
}

Label::~Label() {
    //delete labelItem;
}

qreal Label::getwidth() {
    return labelItem->width();
}

qreal Label::getheight() {
    return labelItem->height();
}

Label * Label::LabelWithText(QString string,QColor *color, int fontSize, QString font) {
    Label* newLabel = new Label(string,color,fontSize,font);
    return newLabel;
}

void Label::setText(QString text) {
    labelItem->setPlainText(text);
    Node::setW(labelItem->width());
    Node::setH(labelItem->height());
    setEffectivePos();
}
