#ifndef TRANSITIONSCENE_H
#define TRANSITIONSCENE_H
#include <QObject>
#include "scene.h"
#include "director.h"
#include "action.h"
#include "sequence.h"

class transitionScene : public QObject
{
    Q_OBJECT

public:
    static transitionScene* FadeTransition(Scene* otherScene,float duration);
    void setCurrScene(Scene* scene);
private:
    transitionScene();
    Scene* currScene;
    Scene* nextScene;
    float dur;
    qreal origFade;
public slots:
    void FadeTransition_half_done();
    void transition_done();

};

#endif // TRANSITIONSCENE_H
