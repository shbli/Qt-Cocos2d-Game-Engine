#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Srcs/game_engine.h"
#include <QList>

class main_menu : public Layer
{
    Q_OBJECT

public:
    static Scene* scene();
    explicit main_menu();
//    void onEnterTransitionDidFinish();
//    void onExitTransitionDidFinish();
    void onEnterTransitionDidStart();
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
    void onExitTransitionDidFinish();
private:
    QRect winSize;
    qreal backGroundHeight;
    Sprite *background;
    QList<Sprite*> cards;
    int counter;
public slots:
    void update(double delta);
    void animation();
};

#endif // MAIN_MENU_H
