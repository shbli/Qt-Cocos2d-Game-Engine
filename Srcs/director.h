#ifndef DIRECTOR_H
#define DIRECTOR_H

// this is a singletone class, the director is one and can change the scenes as you wish to
//class Scene;

#include <QTimer>
#include <QTime>
#include <QApplication>
#include <QDesktopWidget>
#include "global_keys.h"
#include "game_config.h"
#include <QDebug>
#include "graphicsscene.h"
#include <QtOpenGL>
#include "textitem.h"
#include "myfastergraphicview.h"



#include <iostream>
#include <fstream>
#include <sstream>


class transitionScene;
class Scene;
class Sprite;
class Node;

class Director : public QObject
{
    Q_OBJECT

private:

    std::fstream m_fileStream;
    Director();	// hide constructor
    ~Director();	// hide destructor
    Director(const Director &); // hide copy constructor
    Director& operator=(const Director &); // hide assign op
    static Scene *currentscene;
    static Director *director;
    static QMutex mutex;
    static QRect desk;
    QGraphicsTextItem *frameRateText;
    QTime delta;
    QTimer frameSchedular;
    static MyFasterGraphicView *GraphicView;
    bool isRuning;
    graphicsScene *scene;
    QGLWidget* openGLwidget;
    int updateLessTimes;
    QList <Node*> subscribedNodesForUpdates;
    void update(double deltams);

    void intitiatNewLogFile();
public:

    std::fstream& getFileStream() {
        return m_fileStream;
    }

    void subscrbeNodeForUpdates(Node& nodeToSubscribe);
    void unSubscrbeNodeForUpdates(Node& nodeToSubscribe);

    void setupDirector();
    QGraphicsView* sharedGraphicView();
    graphicsScene* sharedGraphicScene();
    static Director* sharedDirector();
    QRect winSizeInPixels();
    void startWithScene(Scene *scene);
    void replaceScene(Scene *scene);
    void replaceScene(transitionScene *traSce);
    void pauseView();
    void continueView();
    static QMainWindow *mainViewWindow;
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };
    void setOrientation(ScreenOrientation orientation);
    static QPointF convertTouchPoint(const QPointF& oldPoint);

    bool position_in_sprite(const QPointF& position,Sprite* sprite_to_check);
    void clearCache();

    void onBackKeyEvent();

public slots:
    void refreshAndroidScreen();
    void updatedEveryFrameRate();
    void updatedEveryFrameRateOpenGL();
    void transitionDone(Scene* scene);

protected:

};

#endif // SHAREDDIRECTOR_H
