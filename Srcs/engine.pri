QT += core gui opengl svg

SrcLoc = $$PWD

INCLUDEPATH += $$SrcLoc

#That is because android still doesn't support the QtMultiMediaKit, once available we'll gear it up by removing the !android { and removing closing cairly bracket at the end }

QT += multimedia

#after having these, create a folder resourc and add to it all the images, sounds that you want to use in your game

unix:!symbian:!maemo5:!win:!android:!macx {
    #Special case for N950 that works, all other devices will use the else case
    DEFINES+=harmattan
    dir1.files = resourc/*
    dir1.path  = /opt/$${TARGET}
    INSTALLS += dir1
} else : android {
    #Special case for android that works, all other devices will use the else case
    dir1.files = resourc/*
    dir1.path  = /assets
    INSTALLS += dir1
} else : macx {
    #Special case for mac that works, all other devices will use the else case
    dir1.files = ../MapBuilder/resourc/*
    dir1.path = Contents/Resources
    QMAKE_BUNDLE_DATA += dir1
}
else {
    dir1.files = ../MapBuilder/resourc/*
    dir1.path =
    QMAKE_BUNDLE_DATA += dir1

#    dir1.source += resourc/*
#    DEPLOYMENTFOLDERS = dir1
}

#for macx static building so that app works on any device mac!!
macx {
    #Special case for mac that works, all other devices will use the else case
    dir2.files = /Users/ahmedalshebli/tmp/qt-everywhere-opensource-src-4.8.0/src/gui/mac/qt_menu.nib
    dir2.path = Contents/Resources
    QMAKE_BUNDLE_DATA += dir2
}


SOURCES += \
    $$SrcLoc/LayerWithPinchAndScroll.cpp \
    $$SrcLoc/transitionscene.cpp \
    $$SrcLoc/textitem.cpp \
    $$SrcLoc/spriteitem.cpp \
    $$SrcLoc/sprite.cpp \
    $$SrcLoc/sequence.cpp \
    $$SrcLoc/scene.cpp \
    $$SrcLoc/node.cpp \
    $$SrcLoc/menuitemimage.cpp \
    $$SrcLoc/menuitem.cpp \
    $$SrcLoc/menu.cpp \
    $$SrcLoc/layer.cpp \
    $$SrcLoc/label.cpp \
    $$SrcLoc/graphicsscene.cpp \
    $$SrcLoc/director.cpp \
    $$SrcLoc/audiomanager.cpp \
    $$SrcLoc/action.cpp \
    $$SrcLoc/xml_cache.cpp \
    $$SrcLoc/elips.cpp \
    $$SrcLoc/linenode.cpp \
    $$SrcLoc/touchhandler.cpp

HEADERS += \
    $$SrcLoc/LayerWithPinchAndScroll.h \
    $$SrcLoc/transitionscene.h \
    $$SrcLoc/trace.h \
    $$SrcLoc/textitem.h \
    $$SrcLoc/spriteitem.h \
    $$SrcLoc/sprite.h \
    $$SrcLoc/sequence.h \
    $$SrcLoc/scene.h \
    $$SrcLoc/node.h \
    $$SrcLoc/myfastergraphicview.h \
    $$SrcLoc/menuitemimage.h \
    $$SrcLoc/menuitem.h \
    $$SrcLoc/menu.h \
    $$SrcLoc/layer.h \
    $$SrcLoc/label.h \
    $$SrcLoc/graphicsscene.h \
    $$SrcLoc/game_engine.h \
    $$SrcLoc/game_config.h \
    $$SrcLoc/director.h \
    $$SrcLoc/audiomanager.h \
    $$SrcLoc/action.h \
    $$SrcLoc/xml_cache.h \
    $$SrcLoc/elips.h \
    $$SrcLoc/linenode.h \
    $$SrcLoc/touchhandler.h
