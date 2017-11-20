#include "main_menu.h"

Scene* main_menu::scene() {
    Scene *scene = Scene::node();
    main_menu* layer = new main_menu;
    scene->addChild(layer);
    return scene;
}


main_menu::main_menu()
{
    qDebug() << Q_FUNC_INFO;
    //taking screen size, saving it to variable called winSize
    winSize = Director::sharedDirector()->winSizeInPixels();

    //we'll start by adding a sprite that represents the background for the menu
    background = Sprite::spriteWithImage("wallpaper.jpg");
    background->setPos(winSize.width()/2,winSize.height()/2);
    addChild(background);
    QString fileName;
    QString temp;
    Sprite *newCard;
    qreal offset = 100;
    //we'll creat the 13 club cards
    fileName = "c.png";
    for (int i = 1; i <= 13; i++) {
        temp = QString().setNum(i);
        temp.append(fileName);
        newCard = Sprite::spriteWithImage(temp.toAscii());
        cards.append(newCard);
        newCard->setPos(offset,offset);
        addChild(newCard);
    }
    //we'll creat the 13 diamond cards
    fileName = "d.png";
    for (int i = 1; i <= 13; i++) {
        temp = QString().setNum(i);
        temp.append(fileName);
        newCard = Sprite::spriteWithImage(temp.toAscii());
        cards.append(newCard);
        newCard->setPos(offset,offset);
        addChild(newCard);
    }
    //we'll creat the 13 heart cards
    fileName = "h.png";
    for (int i = 1; i <= 13; i++) {
        temp = QString().setNum(i);
        temp.append(fileName);
        newCard = Sprite::spriteWithImage(temp.toAscii());
        cards.append(newCard);
        newCard->setPos(offset,offset);
        addChild(newCard);
    }
    //we'll creat the 13 Spade cards
    fileName = "s.png";
    for (int i = 1; i <= 13; i++) {
        temp = QString().setNum(i);
        temp.append(fileName);
        newCard = Sprite::spriteWithImage(temp.toAscii());
        cards.append(newCard);
        newCard->setPos(offset,offset);
        addChild(newCard);
    }
    counter = 0;
    animation();
}

void main_menu::animation() {
    if (counter < cards.size()) {
        cards.at(counter)->runSequence(Sequence::sequenceWithActions(action::easeinout(action::moveBy(0.5,300,200)),action::FuncCall(this,SLOT(animation())),NULL));
        cards.at(counter)->runAction(action::easeinout(action::rotateBy(0.5,360)));
        audioManager::playSound("alert.wav");
        audioManager::playSound("play_card.wav");
        counter++;
    }
}

void main_menu::update(double delta) {
//    runAction(action::rotateBy(4,360));
    runAction(action::easeinout(action::scaleTo(1,1)));
    runAction(action::fadeTo(1,100));
    unSchedualUpdate();
}


void main_menu::onEnterTransitionDidStart() {
    qDebug() << Q_FUNC_INFO;
}

void main_menu::onEnterTransitionDidFinish() {
    qDebug() << Q_FUNC_INFO;
}

void main_menu::onExitTransitionDidStart() {
    qDebug() << Q_FUNC_INFO;
}

void main_menu::onExitTransitionDidFinish() {
    qDebug() << Q_FUNC_INFO;
}

