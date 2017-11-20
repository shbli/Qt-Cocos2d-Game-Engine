#include "transitionscene.h"


transitionScene::transitionScene() {

}

transitionScene * transitionScene::FadeTransition(Scene *otherScene,float duration) {
    transitionScene* newTrans = new transitionScene;
    newTrans->nextScene = otherScene;
    otherScene->mainLayer->onEnterTransitionDidStart();
    newTrans->dur = duration;
    newTrans->origFade = newTrans->nextScene->opacity();
    newTrans->nextScene->setOpacity(0);
    return newTrans;
}

void transitionScene::setCurrScene(Scene *scene) {
    currScene = scene;
    currScene->mainLayer->onExitTransitionDidStart();
    Action* firststep = Action::fadeTo(dur/2,0);
    Action* gotostep2 = ActionFuncCall<transitionScene>::FuncCall(this,&transitionScene::FadeTransition_half_done);
    scene->runSequence(Sequence::sequenceWithActions(firststep,gotostep2,NULL));
}

void transitionScene::FadeTransition_half_done() {
    Action* firststep = Action::fadeTo(dur/2,origFade);
    Action* gotostep3 = ActionFuncCall<transitionScene>::FuncCall(this,&transitionScene::transition_done);
    nextScene->runSequence(Sequence::sequenceWithActions(firststep,gotostep3,NULL));
}
void transitionScene::transition_done() {
    currScene->mainLayer->onExitTransitionDidFinish();
    nextScene->mainLayer->onEnterTransitionDidFinish();
    Director::sharedDirector()->transitionDone(nextScene);
    deleteLater();
}
