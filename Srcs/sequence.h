#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdarg.h> //va_list, va_start, va_arg, va_end
#include "action.h"

class Node;
class Action;

class Sequence : public QObject
{
    Q_OBJECT
public:
    static Sequence* sequenceWithActions(Action* Action,...);
    void setTarget(Node *target);
    void stopActions();

signals:

public slots:
    void oneActionisDone();
private:
    explicit Sequence();
    QList <Action*> ActionList;
    Node *targetNode;
    void runNextAction();
    bool deaActivating;

};

#endif // SEQUENCE_H
