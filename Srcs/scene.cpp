#include "scene.h"

Scene::Scene() {
    Director::sharedDirector()->pauseView();
    if (Node::getSharedGraphicScene() == 0) {
        Node::setSharedGraphicScene(Director::sharedDirector()->sharedGraphicView()->scene());
    }
    setZ(Node::getGlobalMaxZ()+1);
    setPos(0,Director::sharedDirector()->winSizeInPixels().height());
}

Scene* Scene::node() {
    Scene *node = new Scene;
    return node;
}

Scene::~Scene() {
}
