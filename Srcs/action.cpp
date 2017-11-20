#include "Action.h"

Action::Action() {
    targetNode = 0;
    target = 0;
}

Action* Action::moveTo(float duration,qreal x,qreal y, effectiveness effectivenessValue) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeMoveTo;
    newAction->endValue[0] = x;
    newAction->endValue[1] = y;
    newAction->animation.setDuration(1000*duration);
    if (effectivenessValue == Effective) {
        newAction->animation.setPropertyName("pos");
    } else {
        newAction->animation.setPropertyName("posIneffective");
    }
    return newAction;
}

Action* Action::moveBy(float duration,qreal x,qreal y, effectiveness effectivenessValue) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeMoveBy;
    newAction->endValue[0] = x;
    newAction->endValue[1] = y;
    newAction->animation.setDuration(1000*duration);
    if (effectivenessValue == Effective) {
        newAction->animation.setPropertyName("pos");
    } else {
        newAction->animation.setPropertyName("posIneffective");
    }
    return newAction;

}

Action* Action::scaleTo(float duration,qreal scale) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeScaleTo;
    newAction->endValue[0] = scale;
    newAction->animation.setDuration(1000*duration);
    newAction->animation.setPropertyName("scale");
    return newAction;

}

Action* Action::scaleBy(float duration,qreal scale) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeScaleBy;
    newAction->endValue[0] = scale;
    newAction->animation.setDuration(1000*duration);
    newAction->animation.setPropertyName("scale");
    return newAction;

}

Action* Action::scaleYTo(float duration,qreal scale) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeScaleYTo;
    newAction->endValue[0] = scale;
    newAction->animation.setDuration(1000*duration);
    newAction->animation.setPropertyName("scaleY");
    return newAction;

}

Action* Action::scaleYBy(float duration,qreal scale) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeScaleYBy;
    newAction->endValue[0] = scale;
    newAction->animation.setDuration(1000*duration);
    newAction->animation.setPropertyName("scaleY");
    return newAction;

}

Action* Action::scaleXTo(float duration,qreal scale) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeScaleXTo;
    newAction->endValue[0] = scale;
    newAction->animation.setDuration(1000*duration);
    newAction->animation.setPropertyName("scaleX");
    return newAction;

}

Action* Action::scaleXBy(float duration,qreal scale) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeScaleXBy;
    newAction->endValue[0] = scale;
    newAction->animation.setDuration(1000*duration);
    newAction->animation.setPropertyName("scaleX");
    return newAction;
}

Action* Action::fadeTo(float duration,qreal value) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeFadeTo;
    newAction->endValue[0] = value;
    newAction->animation.setDuration(1000*duration);
    newAction->animation.setPropertyName("opacity");
    return newAction;

}

Action* Action::fadeBy(float duration,qreal value) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeFadeBy;
    newAction->endValue[0] = value;
    newAction->animation.setDuration(1000*duration);
    newAction->animation.setPropertyName("opacity");
    return newAction;

}

Action* Action::rotateTo(float duration,qreal angle, effectiveness effectivenessValue) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeRotateTo;
    newAction->endValue[0] = angle;
    newAction->animation.setDuration(1000*duration);
    if (effectivenessValue == Effective) {
        newAction->animation.setPropertyName("rotate");
    } else {
        newAction->animation.setPropertyName("rotateIneffective");
    }
    return newAction;

}

Action* Action::rotateBy(float duration,qreal angle, effectiveness effectivenessValue) {
    Action *newAction = new Action;
    newAction->ActionTypeV = ActionTypeRotateBy;
    newAction->endValue[0] = angle;
    newAction->animation.setDuration(1000*duration);
    if (effectivenessValue == Effective) {
        newAction->animation.setPropertyName("rotate");
    } else {
        newAction->animation.setPropertyName("rotateIneffective");
    }
    return newAction;

}


Action* Action::easein(Action* withAction,int rate) {
    if (rate < 0) {
        rate = 0;
        //fileStream << "GameEngine :: easing rate should have a range between 0 and 5, range has been set to 0 for you this time";
    }
    if (rate > 5) {
        rate = 5;
        //fileStream << "GameEngine :: easing rate should have a range between 0 and 5, range has been set to 5 for you this time";
    }
    if (rate == 0)
        withAction->animation.setEasingCurve(QEasingCurve::Linear);
    if (rate == 1)
        withAction->animation.setEasingCurve(QEasingCurve::InQuad);
    if (rate == 2)
        withAction->animation.setEasingCurve(QEasingCurve::InCubic);
    if (rate == 3)
        withAction->animation.setEasingCurve(QEasingCurve::InQuart);
    if (rate == 4)
        withAction->animation.setEasingCurve(QEasingCurve::InCirc);
    if (rate == 5)
        withAction->animation.setEasingCurve(QEasingCurve::InBack);

    return withAction;
}

Action* Action::easeout(Action* withAction,int rate) {
    if (rate < 0) {
        rate = 0;
        //fileStream << "GameEngine :: easing rate should have a range between 0 and 5, range has been set to 0 for you this time";
    }
    if (rate > 5) {
        rate = 5;
        //fileStream << "GameEngine :: easing rate should have a range between 0 and 5, range has been set to 5 for you this time";
    }
    if (rate == 0)
        withAction->animation.setEasingCurve(QEasingCurve::Linear);
    if (rate == 1)
        withAction->animation.setEasingCurve(QEasingCurve::OutQuad);
    if (rate == 2)
        withAction->animation.setEasingCurve(QEasingCurve::OutCubic);
    if (rate == 3)
        withAction->animation.setEasingCurve(QEasingCurve::OutQuart);
    if (rate == 4)
        withAction->animation.setEasingCurve(QEasingCurve::OutCirc);
    if (rate == 5)
        withAction->animation.setEasingCurve(QEasingCurve::OutBack);
    return withAction;
}

Action* Action::easeinout(Action* withAction,int rate) {
    if (rate < 0) {
        rate = 0;
        //fileStream << "GameEngine :: easing rate should have a range between 0 and 5, range has been set to 0 for you this time";
    }
    if (rate > 5) {
        rate = 5;
        //fileStream << "GameEngine :: easing rate should have a range between 0 and 5, range has been set to 5 for you this time";
    }
    if (rate == 0)
        withAction->animation.setEasingCurve(QEasingCurve::Linear);
    if (rate == 1)
        withAction->animation.setEasingCurve(QEasingCurve::InOutQuad);
    if (rate == 2)
        withAction->animation.setEasingCurve(QEasingCurve::InOutCubic);
    if (rate == 3)
        withAction->animation.setEasingCurve(QEasingCurve::InOutQuart);
    if (rate == 4)
        withAction->animation.setEasingCurve(QEasingCurve::InOutCirc);
    if (rate == 5)
        withAction->animation.setEasingCurve(QEasingCurve::InOutBack);
    return withAction;
}

Action *Action::easCurve(Action *withAction, QEasingCurve curve) {
    withAction->animation.setEasingCurve(curve);
    return withAction;
}


void Action::setTarget(Node *targeted) {
    connect(this,SIGNAL(animationFinished(Action*)),targeted,SLOT(actionDone(Action*)));
    if (ActionTypeV == ActionTypeFuncCall) {
        connect(this,SIGNAL(animationFinished(Action*)),target,slotCall);
        delete_self();
    } else if (ActionTypeV == ActionTypeFuncCallBack) {
    } else {
        target = targeted;
        targetNode = targeted;
        qreal newY;
        qreal newX;
        switch (ActionTypeV) {
        case ActionTypeMoveTo :
            animation.setStartValue(targeted->pos());
            //here we are setting the new position
            animation.setEndValue(QPointF(endValue[0],endValue[1]));
            break;
        case ActionTypeMoveBy :
            animation.setStartValue(targeted->pos());
            //here we'll calculate the new point as it's moveBy, we'll add the value to the original
            newX = endValue[0] + targeted->pos().x();
            newY = endValue[1] + targeted->pos().y();
            animation.setEndValue(QPointF(newX,newY));
            break;
        case ActionTypeFadeTo :
            animation.setStartValue(targeted->opacity());
            //here we'll set the new scale
            animation.setEndValue(endValue[0]);
            break;
        case ActionTypeFadeBy :
            animation.setStartValue(targeted->opacity());
            //here we'll calculate the new scale as it's multiplied by original scale
            animation.setEndValue(endValue[0]+targeted->opacity());
            break;
        case ActionTypeScaleTo:
            animation.setStartValue(targeted->scale());
            //here we'll set the new scale
            animation.setEndValue(endValue[0]);
            break;
        case ActionTypeScaleBy :
            animation.setStartValue(targeted->scale());
            //here we'll calculate the new scale as it's multiplied by original scale
            animation.setEndValue(endValue[0]*targeted->scale());
            break;
        case ActionTypeScaleYTo:
            animation.setStartValue(targeted->scaleY());
            //here we'll set the new scale
            animation.setEndValue(endValue[0]);
            break;
        case ActionTypeScaleYBy :
            animation.setStartValue(targeted->scaleY());
            //here we'll calculate the new scale as it's multiplied by original scale
            animation.setEndValue(endValue[0]*targeted->scaleY());
            break;
        case ActionTypeScaleXTo:
            animation.setStartValue(targeted->scaleX());
            //here we'll set the new scale
            animation.setEndValue(endValue[0]);
            break;
        case ActionTypeScaleXBy :
            animation.setStartValue(targeted->scaleX());
            //here we'll calculate the new scale as it's multiplied by original scale
            animation.setEndValue(endValue[0]*targeted->scaleX());
            break;
        case ActionTypeRotateTo :
            animation.setStartValue(targeted->rotation());
            //here we'll set the new scale
            animation.setEndValue(endValue[0]);
            break;
        case ActionTypeRotateBy :
            animation.setStartValue(targeted->rotation());
            //here we'll calculate the new scale as it's multiplied by original scale
            animation.setEndValue(endValue[0]+targeted->rotation());
            break;
        default:
            emit animationFinished(this);
            break;
        }
        animation.setTargetObject(target);
        animation.start();
        //here we are connecting it to delete itself slot, and emit done signal
        connect(&animation,SIGNAL(finished()),this,SLOT(delete_self()));
    }

}


void Action::delete_self() {
    emit animationFinished(this);
}

void Action::stopAnimation() {
    animation.stop();
}

