#include "director.h"

MyFasterGraphicView* Director::GraphicView = 0;
Director* Director::director = 0;
QMutex Director::mutex;
QRect Director::desk;
Scene* Director::currentscene = 0;
QMainWindow* Director::mainViewWindow = 0;

#include <QGraphicsTextItem>
#include "transitionscene.h"
#include <QSettings>
#include <QMainWindow>
#include "sprite.h"

Director::Director() {    
}
Director::~Director() {
    pauseView();
}

void Director::setupDirector() {

    if (GraphicView == 0)
    {

        //set the cache size in kilo bytes
        QPixmapCache::setCacheLimit(1024*pixmapCacheKey);

        //change current working directory depending on the system

        //this code, until the last QDir is to set the CWD, aka Current Working Directory
        QDir dir(QCoreApplication::applicationDirPath());
        if (dir.dirName().toLower() == "bin")
        {
            dir.cdUp();
        }
#ifdef WIN32
        if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
        {
            dir.cdUp();
        }
#endif
#ifdef Q_OS_MAC64
        dir.cdUp();
        dir.cd("Resources");
        dir.cd("resourc");
#endif
        QDir::setCurrent(dir.absolutePath());
        QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

        //save window size
        desk.setWidth(QApplication::desktop()->screenGeometry(0).width()*QApplication::primaryScreen()->devicePixelRatio());
        desk.setHeight(QApplication::desktop()->screenGeometry(0).height()*QApplication::primaryScreen()->devicePixelRatio());

        //uncomment this if condition and comment the one under it, if you would like a portraite mode
        //if (desk.height() < desk.width()) {
        if (desk.height() > desk.width()) {
            int prevH = desk.height();
            desk.setHeight(desk.width());
            desk.setWidth(prevH);
        }
        mainViewWindow = new QMainWindow;

        qDebug() << "GameEngine::ScreenResultion in pixels " << desk;


        // if it's windows, simulator, check full screen variable, if on mobile phone, run full screen please
#ifdef COMPUTER
#ifdef fullScreen
        GraphicView = new MyFasterGraphicView(desk);
        mainViewWindow->setGeometry(desk);
        mainViewWindow->setCentralWidget(GraphicView);
        mainViewWindow->showFullScreen();
        desk = mainViewWindow->geometry();
        if (desk.height() > desk.width()) {
            int prevH = desk.height();
            desk.setHeight(desk.width());
            desk.setWidth(prevH);
        }
#else
        QSettings configs("config.ini",QSettings::IniFormat);
        desk.setWidth(configs.value("width").toInt());
        desk.setHeight(configs.value("height").toInt());
        GraphicView = new MyFasterGraphicView(desk);
        mainViewWindow->setGeometry(desk);
        mainViewWindow->setCentralWidget(GraphicView);
        mainViewWindow->show();
        mainViewWindow->move(100,100);
#endif
#else   //mobile phones will use full screen no matter
        GraphicView = new MyFasterGraphicView(desk);
        GraphicView->showFullScreen();
#endif

        GraphicView->setStyleSheet("background-color: black");
        GraphicView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        GraphicView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        GraphicView->setOptimizationFlag(QGraphicsView::DontSavePainterState,true);
        //setting Qt::WA_TranslucentBackground improves performance on mobile phones!!,it seems it doesn't help a lot!
        GraphicView->setAttribute(Qt::WA_TranslucentBackground,false);
        GraphicView->setFrameStyle(0);
        setOrientation(Director::ScreenOrientationLockLandscape);
        //advance graphics, can be enabled for all, or can be spefically disabled on Symbian
        //        #ifdef Q_OS_SYMBIAN
        //do nothing, don't turn on advance graphics features
        //        #else   //symbian is slow so this will only apply for OSes other than symbian phones, also we don't need these on other devices, if needed, we'll just uncomment this code
        GraphicView->setRenderHints(QPainter::NonCosmeticDefaultPen | QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
        //        #endif
        GraphicView->setGeometry(desk);
        mainViewWindow->setGeometry(desk);
#ifdef COMPUTER
        mainViewWindow->showFullScreen();
#else
        GraphicView->showFullScreen();
#endif
        desk.setX(0);
        desk.setY(0);
        //set graphics view to screen size
        scene = new graphicsScene;
        GraphicView->setScene(scene);
        GraphicView->setSceneRect(desk);
        scene->setItemIndexMethod(QGraphicsScene::NoIndex);
        scene->addRect(desk,Qt::NoPen,QColor(0,0,0,255))->setZValue(-10000000);

        if (displyFrameRate) {
            Director::sharedDirector()->frameRateText = scene->addText(QString().setNum(60));
            frameRateText->setPlainText(QString().setNum(frameRate));
            QFont newfont("Ariel",16);
            newfont.setPixelSize(newfont.pointSize());
            frameRateText->setFont(newfont);
            Director::sharedDirector()->frameRateText->setZValue(10000);
            Director::sharedDirector()->frameRateText->setDefaultTextColor(QColor(255,255,255,150));
            frameRateText->setPos(0,desk.height()-(frameRateText->document()->size().height()));
        }
        GraphicView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//        GraphicView->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
        Director::sharedDirector()->delta.restart();
        Director::sharedDirector()->frameSchedular.start((1.0/frameRate)*1000.0);
        isRuning = true;


        updateLessTimes = frameRate/3;

#ifdef useOpenGL

        //openGL settings

/*
  QGLFormat is not effective, unless to send it as a paramter to the QGLWidget, the code down might be commented down
*/
//        QGLFormat format;
//        if (format.hasOpenGL()) {
////            format.setProfile(QGLFormat::CoreProfile);
////            format.setAlpha(openGLAlpha);

//            format.setSampleBuffers(true);
//            format.setOverlay(true);
//            format.setDoubleBuffer(true);
//            format.setDepth(true);
//            format.setStencil(true);
//            format.setDirectRendering(true);

////            format.setStereo(true);

////            format.setDepth(openGLdepthBuffer);

//            //set open gl version to max available, they have to be in order from smallest to biggest

//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_ES_CommonLite_Version_1_0) ||
//                    format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_ES_Common_Version_1_0) ) {
//                format.setVersion(1,0);
//            }
//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_1_1) ||
//                    format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_ES_CommonLite_Version_1_1) ||
//                    format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_ES_Common_Version_1_1)
//                    ) {
//                format.setVersion(1,1);
//            }
//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_1_2)
//                    ) {
//                format.setVersion(1,2);
//            }

//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_1_3)
//                    ) {
//                format.setVersion(1,3);
//            }

//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_1_4)
//                    ) {
//                format.setVersion(1,4);
//            }

//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_1_5)
//                    ) {
//                format.setVersion(1,5);
//            }

//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_2_0) ||
//                    format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_ES_Version_2_0)
//                    ) {
//                format.setVersion(2,0);
//            }

//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_2_1)
//                    ) {
//                format.setVersion(2,1);
//            }

//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_3_0)
//                    ) {
//                format.setVersion(3,0);
//            }

//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_3_1)
//                    ) {
//                format.setVersion(3,1);
//            }

//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_3_2)
//                    ) {
//                format.setVersion(3,2);
//            }

//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_3_3)
//                    ) {
//                format.setVersion(3,3);
//            }


//            if (format.openGLVersionFlags().testFlag(QGLFormat::OpenGL_Version_4_0)
//                    ) {
//                format.setVersion(4,0);
//            }


//            openGLwidget = new QGLWidget(format);
            openGLwidget = new QGLWidget();
#ifdef Q_OS_SYMBIAN
            QGLFormat format;
            format.setVersion(2,0);
            openGLwidget->setFormat(format);
#endif
            if (openGLwidget->isValid()) {
                //fileStream << "GL is valid";
            } else {
//                qWarning() << "GL is invalid";
            }
            openGLwidget->setGeometry(desk);
            GraphicView->setViewport(openGLwidget);

            openGLwidget->setStyleSheet("background-color: black");

            //fileStream << "Game Engine :: OpenGL " << openGLwidget->format().majorVersion() << "." << openGLwidget->format().minorVersion();
            //            fileStream << "Supported OpenGL are " << format.openGLVersionFlags();
        } else {
            //fileStream << "Game Engine :: OpenGL not supported, performance might decrease significatly";
            openGLwidget = 0;
        }
#else
        openGLwidget = 0;
#endif
        //end of opengl setting
        if (openGLwidget == 0) {
            connect(&frameSchedular,SIGNAL(timeout()),Director::sharedDirector(),SLOT(updatedEveryFrameRate()));
        } else {
            connect(&frameSchedular,SIGNAL(timeout()),Director::sharedDirector(),SLOT(updatedEveryFrameRateOpenGL()));
        }

        //this is to make sure that ANDROID STATUS BAR is hidden in the game, because taskbar should be hidden in games!!
        QTimer::singleShot(100,Director::sharedDirector(),SLOT(refreshAndroidScreen()));
        QTimer::singleShot(500,Director::sharedDirector(),SLOT(refreshAndroidScreen()));
        QTimer::singleShot(1000,Director::sharedDirector(),SLOT(refreshAndroidScreen()));
        QTimer::singleShot(2000,Director::sharedDirector(),SLOT(refreshAndroidScreen()));
#ifndef useOpenGL
    }
#endif
}

void Director::startWithScene(Scene *scene) {
    intitiatNewLogFile();
    currentscene = scene;
    scene->mainLayer->onEnterTransitionDidStart();
    continueView();
    scene->mainLayer->onEnterTransitionDidFinish();
    return;
}

void Director::replaceScene(Scene *scene) {
    //first let's intial a new file so the log will start from scratch
    intitiatNewLogFile();
    if (currentscene != 0 ) {
        currentscene->mainLayer->onExitTransitionDidStart();
        currentscene->mainLayer->onExitTransitionDidFinish();
        currentscene->deleteLater();
    }
    currentscene = scene;
    scene->mainLayer->onEnterTransitionDidStart();
    continueView();
    currentscene->mainLayer->onEnterTransitionDidFinish();
}

void Director::replaceScene(transitionScene *traSce) {
    traSce->setCurrScene(currentscene);
    continueView();
}
void Director::transitionDone(Scene* scene) {
    currentscene->deleteLater();
    currentscene = scene;
}

Director* Director::sharedDirector()
{
    if (!director)
    {
        mutex.lock();

        if (!director)
        {
            director = new Director;
            director->setupDirector();
        }
        mutex.unlock();
    }

    return director;
}

QRect Director::winSizeInPixels() {
    return desk;
}

void Director::updatedEveryFrameRate() {
    int elapsed = delta.elapsed();
    update(elapsed/1000.0);
    if (displyFrameRate) {
        double rate = elapsed;
        rate/= 1000.0;
        rate = 1.0/rate;
        if (rate > frameRate + 10)
            rate = frameRate;
        updateLessTimes++;
        if (updateLessTimes > (frameRate/2)) {
            updateLessTimes = 0;
            frameRateText->setPlainText(QString().setNum(rate,'g',3));
        }
    }
    delta.start();
//    GraphicView->update(desk);
}
void Director::updatedEveryFrameRateOpenGL() {
    int elapsed = delta.elapsed();
    emit update(elapsed/1000.0);
    if (displyFrameRate) {
        double rate = elapsed;
        rate/= 1000.0;
        rate = 1.0/rate;
        if (rate > frameRate + 10)
            rate = frameRate;
        updateLessTimes++;
        if (updateLessTimes > (frameRate/2)) {
            updateLessTimes = 0;
            frameRateText->setPlainText(QString().setNum(rate,'g',3));

        }
    }
    delta.start();
//    openGLwidget->update(desk);
}


QGraphicsView * Director::sharedGraphicView() {
    return GraphicView;
}

void Director::pauseView() {
    //    if (isRuning) {
    //        if (openGLwidget == 0) {
    //            disconnect(&frameSchedular,SIGNAL(timeout()),Director::sharedDirector(),SLOT(updatedEveryFrameRate()));
    //        } else {
    //            disconnect(&frameSchedular,SIGNAL(timeout()),Director::sharedDirector(),SLOT(updatedEveryFrameRateOpenGL()));
    //        }
    //        isRuning = 0;
    //    }
    refreshAndroidScreen();
}

void Director::continueView() {
    //    if (!isRuning) {
    //        isRuning = 1;
    //        if (openGLwidget == 0) {
    //            connect(&frameSchedular,SIGNAL(timeout()),Director::sharedDirector(),SLOT(updatedEveryFrameRate()));
    //        } else {
    //            connect(&frameSchedular,SIGNAL(timeout()),Director::sharedDirector(),SLOT(updatedEveryFrameRateOpenGL()));
    //        }
    //    }
    refreshAndroidScreen();
}

graphicsScene * Director::sharedGraphicScene() {
    return scene;
}

void Director::setOrientation(ScreenOrientation orientation)
{
}

QPointF Director::convertTouchPoint(const QPointF& oldPoint) {
    //we'll do convert the touch point
    return QPointF(oldPoint.x(),desk.height() - oldPoint.y());
}

bool Director::position_in_sprite(const QPointF& position, Sprite *sprite_to_check) {
    if (position.x() > (sprite_to_check->pos().x() - ((sprite_to_check->width()*(sprite_to_check->scaleX()))/2)) && position.x() < (sprite_to_check->pos().x() + ((sprite_to_check->width()*(sprite_to_check->scaleX()))/2)) ) {
        if (position.y() > (sprite_to_check->pos().y() - ((sprite_to_check->height()*(sprite_to_check->scaleY()))/2)) && position.y() < (sprite_to_check->pos().y() + ((sprite_to_check->height()*(sprite_to_check->scaleY()))/2)) ) {
            //am touching the sprite
            return true;
        }
    }
    return false;
}

void Director::clearCache() {
    QPixmapCache::clear();
}

void Director::onBackKeyEvent() {
    if (currentscene) {
        currentscene->mainLayer->onBackButtonClicked();
    }
}

void Director::refreshAndroidScreen() {
    //this is a temp fix for android only!!
#ifdef Q_WS_QPA
    GraphicView->showMinimized();
    GraphicView->showFullScreen();
#endif

}

void Director::update(double deltams) {
//    static QTime t;
//    t.restart();
    //update all objects
    Node* someNode;
    for (int i = 0; i < subscribedNodesForUpdates.size(); i++) {
        someNode = subscribedNodesForUpdates.at(i);
        someNode->update(deltams);
    }
//    qDebug() << "Time took for object updates is " << t.elapsed();
}

void Director::intitiatNewLogFile() {
    if (m_fileStream.is_open()) {
        m_fileStream.close();
    }
    m_fileStream.open("TheRoyalQuest.log",std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
    //file is not created, create it
    if (!m_fileStream.is_open()) {
        m_fileStream.open("TheRoyalQuest.log",std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
    }
    //adding screen resultion to the file
    m_fileStream << "Game Engine :: Screen size : w: " << desk.width() << " x h: " << desk.height();
}

void Director::subscrbeNodeForUpdates(Node &nodeToSubscribe) {
    subscribedNodesForUpdates.removeOne(&nodeToSubscribe);
    subscribedNodesForUpdates.append(&nodeToSubscribe);
}

void Director::unSubscrbeNodeForUpdates(Node &nodeToSubscribe) {
    subscribedNodesForUpdates.removeOne(&nodeToSubscribe);
}
