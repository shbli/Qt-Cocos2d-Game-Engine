#ifndef ACTION_H
#define ACTION_H

#include <QPropertyAnimation>
#include <QDebug>
#include "node.h"

class Node;

class Action : public QObject
{
    Q_OBJECT

public:



    enum effectiveness {
        Effective = 0,
        Ineffective
    };

    static Action* moveTo(float duration,qreal x,qreal y, effectiveness effectivenessValue = Effective);
    static Action* moveBy(float duration,qreal x,qreal y, effectiveness effectivenessValue = Effective);
    static Action* scaleTo(float duration,qreal scale);
    static Action* scaleBy(float duration,qreal scale);
    static Action* scaleYTo(float duration,qreal scale);
    static Action* scaleYBy(float duration,qreal scale);
    static Action* scaleXTo(float duration,qreal scale);
    static Action* scaleXBy(float duration,qreal scale);
    static Action* fadeTo(float duration,qreal value);
    static Action* fadeBy(float duration,qreal value);
    static Action* rotateTo(float duration,qreal angle, effectiveness effectivenessValue = Effective);
    static Action* rotateBy(float duration,qreal angle, effectiveness effectivenessValue = Effective);
    static Action* easein(Action* withAction,int rate = 4);
    static Action* easeout(Action* withAction,int rate = 4);
    static Action* easeinout(Action* withAction,int rate = 4);
    static Action* easCurve(Action* withAction,QEasingCurve curve);
    virtual void setTarget(Node *targeteted);
    void stopAnimation();
    Node* targetNode;

protected:
    enum ActionType {
        ActionTypeMoveTo = 0,
        ActionTypeMoveBy,
        ActionTypeFadeTo,
        ActionTypeFadeBy,
        ActionTypeScaleTo,
        ActionTypeScaleBy,
        ActionTypeScaleYTo,
        ActionTypeScaleYBy,
        ActionTypeScaleXTo,
        ActionTypeScaleXBy,
        ActionTypeRotateTo,
        ActionTypeRotateBy,
        ActionTypeFuncCall,
        ActionTypeFuncCallBack
    };

    QObject *target;
    //this is the animation variable
    QPropertyAnimation animation;
    ActionType ActionTypeV;
    qreal endValue[2];
    const char* slotCall;

    Action();

public slots:
    void delete_self();
signals:
    void animationFinished(Action *finishedAction);
};


template <typename TFunc>


class ActionFuncCall : public Action {

public:

    static ActionFuncCall* FuncCall(TFunc* targeted,void (TFunc::*toBeNotifiedFunctionPar)()) {
        ActionFuncCall<TFunc>* newFuncCall = new ActionFuncCall<TFunc>();
        newFuncCall->tagetToBeCalled = targeted;
        newFuncCall->toBeNotifiedFunction = toBeNotifiedFunctionPar;
        return newFuncCall;
    }

    void setTarget(Node *targeteted) {
        Action::setTarget(targeteted);
        (tagetToBeCalled->*toBeNotifiedFunction)(); // Call member function through pointer.
        delete_self();
    }

private:
    TFunc* tagetToBeCalled;
    void (TFunc::*toBeNotifiedFunction)();
};

#endif // ACTION_H
