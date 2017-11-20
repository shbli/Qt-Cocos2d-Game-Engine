#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>

class graphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit graphicsScene(QObject *parent = 0);
    ~graphicsScene();

    void invalidate(const QRectF &rect, SceneLayers layers);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    bool mouseDown;
public slots:
    void gameEnded();

};

#endif // GRAPHICSSCENE_H
