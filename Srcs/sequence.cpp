#include "sequence.h"

Sequence::Sequence() {
    deaActivating = false;
}

Sequence* Sequence::sequenceWithActions(Action* ActionItem,...) {

    if (ActionItem != NULL) {
        Sequence* newSeq = new Sequence;
        newSeq->ActionList.append(ActionItem);
        Action* addAction;
        va_list list;
        va_start(list,ActionItem);
        addAction = va_arg(list,Action*);
        while (addAction != NULL) {
            newSeq->ActionList.append(addAction);
            addAction = va_arg(list,Action*);
        }
        va_end(list);
        return newSeq;
    }
    else {
        //fileStream << "Game Engine :: Warning : you are trying to construct an empty sequence Action, it will return for you a NULL pointer";
        return NULL;
    }

}

void Sequence::setTarget(Node *target) {
    targetNode = target;
    runNextAction();
}

void Sequence::oneActionisDone() {
    runNextAction();
}

void Sequence::runNextAction() {
    if (!deaActivating) {
        if (!ActionList.isEmpty()) {
            Action* nextAction = ActionList.takeFirst();
            connect(nextAction,SIGNAL(animationFinished(Action*)),this,SLOT(oneActionisDone()));
            targetNode->runAction(nextAction);
        }
        else {
            targetNode->stopSequence(this);
        }
    }
}

void Sequence::stopActions() {
    deaActivating = true;
    while (!ActionList.isEmpty()) {
        Action* nextAction = ActionList.takeFirst();
        if (nextAction->targetNode != 0) {
            nextAction->stopAnimation();
            nextAction->deleteLater();
        }
    }
}
