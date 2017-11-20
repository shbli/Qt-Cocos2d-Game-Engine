#ifndef NODE_H
#define NODE_H
#include "QPointF"
#include "QGraphicsScene"
#include <QGraphicsItem>
#include <QDebug>
#include "sequence.h"
#include "director.h"


#define watchNodesMemory

class Action;
class Sequence;

class Node : public QObject
{
    Q_OBJECT
    Q_PROPERTY (qreal scale READ scale WRITE setScale)
    Q_PROPERTY (qreal scaleX READ scaleX WRITE setScaleX)
    Q_PROPERTY (qreal scaleY READ scaleY WRITE setScaleY)
    Q_PROPERTY (qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY (qreal rotate READ rotation WRITE setRotation)
    Q_PROPERTY (const QPointF& pos READ pos WRITE setPos)

    //ineffective properties, these would not effect in real time, until the effective function is called with this or any level of it's parents
    Q_PROPERTY (qreal rotateIneffective READ rotation WRITE setIneffectiveRotation)
    Q_PROPERTY (const QPointF& posIneffective READ pos WRITE setIneffectivePos)


public:

#ifdef watchNodesMemory
    static QList <Node*> nodesWithNoParents;
    static void displayNodeLeakedMemory();
#endif

    enum touchPiority {
        veryLow = 0,
        low = 1,
        normal = 2,
        high = 3,
        veryhigh = 4
    };

    Node *parent;
    //these functions should be implemented in the subclass
    virtual qreal getwidth();
    virtual qreal getheight();
    virtual QPointF pos() const;
    virtual QPointF anchorPoint() const;
    virtual qreal opacity() const;
    virtual qreal scale();
    virtual qreal scaleX();
    virtual qreal scaleY();
    virtual qreal rotation();
    virtual int z();
    virtual void setOpacity(const qreal& value);
    virtual void setPos ( const QPointF & pos );
    virtual void setPos ( const qreal& x, const qreal& y );
    QPointF topleftPoint();
    QPointF toprightPoint();
    QPointF bottomrightPoint();
    QPointF bottomleftPoint();

    //due to some heavy calculations, these are used to do the real effect on a position
    virtual void setEffectivePos();
    virtual void setEffectiveRotation();
    virtual void setAnchor (const qreal& xanchorvalue,const qreal& yanchorvalue);
    virtual void setScale ( const qreal& factor );
    virtual void setScale ( const qreal& factorx, const qreal& factory );
    virtual void setScaleX ( const qreal& factorx );
    virtual void setScaleY ( const qreal& factory );
    virtual void setZ ( int zValue );
    virtual void setRotation ( const qreal& rotationDegree );
    virtual void setIneffectiveRotation ( const qreal& rotationDegree );
    virtual void setIneffectivePos ( const qreal& x, const qreal& y );
    virtual void setIneffectivePos ( const QPointF &point );
    virtual Action* runAction(Action* actionPara);
    virtual void runSequence(Sequence* sequencePara);
    virtual void stopAction(Action* stopAction);
    virtual void setGraphicsEffect(QGraphicsEffect * effect);
    void stopSequence(Sequence* stopAction);
    virtual void stopAllActions();
    void schedualUpdate();
    void unSchedualUpdate();
    qreal width();
    qreal height();
    ~Node();
    Node();
    virtual void addChild(Node* child,int tag = 0,int z = 0);
    virtual Node* getChildByTag(int tag);
    virtual void removeChildByTag(int tag);
    virtual void removeChild(Node* child,bool cleanup = true);
    virtual void onEnterTransitionDidStart(){}
    virtual void onEnterTransitionDidFinish(){}
    virtual void onExitTransitionDidStart(){}
    virtual void onExitTransitionDidFinish(){}
    virtual void onBackButtonClicked() {}
    virtual void touchBegin(const QPointF& touchPoint) {}
    virtual void touchMove(const QPointF& touchPoint) {}
    virtual void touchEnd(const QPointF& touchPoint) {}
    void setTouchEnabled(bool enabled = true);
    bool touchEnabled();
    bool ignoreParentRotation;


    //return real time, or on screen values
    QPointF     realTimePos();
    qreal     realTimeXScale() const;
    qreal     realTimeYScale() const;
    int     realTimeZ() const;
    qreal     realTimeRotation() const;
    qreal     realTimeOpacity() const;


    virtual void update(double delta);

    void setNodeTouchPiority(Node::touchPiority piority);
    const Node::touchPiority& getNodeTouchPiority();

protected:

    // these functions are overloaded in base classes as private with no implementation, because they need to be protected
    virtual QGraphicsScene* getSharedGraphicScene();
    virtual void setSharedGraphicScene(QGraphicsScene* graphicscene);
    virtual int getGlobalMaxZ();
    virtual QGraphicsItem* getGraphicsItem();
    virtual void setGraphicsItem(QGraphicsItem* item);
    virtual void setW(qreal w);
    virtual void setH(qreal h);

    // end of protected members
signals:
    void updateChildsPos(const qreal& parentX,const qreal& parentY);
    void updateChildsScale(const qreal& parentxScale,const qreal& parentyScale);
    void updateChildsZ(int myRealZ);
    void updateChildsRotation(const qreal& parentRotate);
    void updateChildsOpacity(const qreal& myRealOpacity);

public slots:
    void actionDone(Action* doneAction);
    void updateMyPos(const qreal& parentX,const qreal& parentY);
    void updateMyScale(const qreal& parentxScale,const qreal& parentyScale);
    void updateMyZ(int parentZ);
    void updateMyRotation(const qreal& parentRotate);
    void updateMyOpacity(const qreal& parentOpacity);

private:
    QGraphicsScale* scalingProperties;
    bool updatescheduled;
    static QGraphicsScene *sharedGraphicScene;
    int z_;
    static int global_max_z;
    int max_local_z;
    QList <Node *> childs;
    QList <Action *> actions;
    QList <Sequence *> sequences;
    QGraphicsItem *graphicsItem;
    qreal center_x;
    qreal center_y;
    qreal parent_real_x;
    qreal parent_real_opacity;
    qreal parent_real_y;
    qreal parent_real_rotation;
    qreal parent_real_x_scale;
    qreal parent_real_y_scale;
    int parent_real_z;
    qreal XscaleFactor;
    qreal YscaleFactor;
    qreal w;
    qreal h;
    qreal rotaionAngle;
    qreal opacityValue;
    qreal x_anchor;
    qreal y_anchor;
    int nodetag;
    bool isTouchEnabled;
    touchPiority nodeTouchPiority;

    qreal m_realTimeLayerX;
    qreal m_realTimeLayerY;

};

#endif // CCNODE_H
