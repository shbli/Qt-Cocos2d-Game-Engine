#Start copying from here
QT += core gui opengl


SrcLoc = Srcs

#That is because android still doesn't support the QtMultiMediaKit, once available we'll gear it up by removing the !android { and removing closing cairly bracket at the end }

!android {
macx {
    QT += multimedia multimediakit
}
win {
    QT += multimedia multimediakit
}
CONFIG += mobility
MOBILITY += multimedia
SOURCES += $$SrcLoc/GEInterfaces.cpp \
    $$SrcLoc/GEAudioOut.cpp \
    $$SrcLoc/GEAudioMixer.cpp \
    $$SrcLoc/GEAudioBufferPlayInstance.cpp \
    $$SrcLoc/GEAudioBuffer.cpp
HEADERS += $$SrcLoc/GEInterfaces.h \
    $$SrcLoc/GEAudioOut.h \
    $$SrcLoc/GEAudioMixer.h \
    $$SrcLoc/GEAudioBufferPlayInstance.h \
    $$SrcLoc/GEAudioBuffer.h
}
#android {
#    INCLUDEPATH += /opt/necessitas/Android/Qt/480/armeabi-v7a/include/QtMultimediaKit
#    INCLUDEPATH += /opt/necessitas/Android/Qt/480/armeabi-v7a/include/QtMobility
#}

#after having these, create a folder resourc and add to it all the images, sounds that you want to use in your game

ios:include($$[QMAKE_MKSPECS]/common/ios/qiosapp.conf)

unix:!symbian:!maemo5:!win:!android:!macx {
    #Special case for N950 that works, all other devices will use the else case
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
    dir1.files = resourc
    dir1.path = Contents/Resources
    QMAKE_BUNDLE_DATA += dir1
}
else {
    dir1.source += resourc/*
    DEPLOYMENTFOLDERS = dir1
}

SOURCES += \
    $$SrcLoc/transitionscene.cpp \
    $$SrcLoc/textitem.cpp \
    $$SrcLoc/spriteitem.cpp \
    $$SrcLoc/sprite.cpp \
    $$SrcLoc/sequence.cpp \
    $$SrcLoc/scene.cpp \
    $$SrcLoc/node.cpp \
    $$SrcLoc/menuitemlabel.cpp \
    $$SrcLoc/menuitemimage.cpp \
    $$SrcLoc/menuitem.cpp \
    $$SrcLoc/menu.cpp \
    $$SrcLoc/layer.cpp \
    $$SrcLoc/label.cpp \
    $$SrcLoc/graphicsscene.cpp \
    $$SrcLoc/director.cpp \
    $$SrcLoc/audiomanager.cpp \
    $$SrcLoc/action.cpp
HEADERS += \
    $$SrcLoc/transitionscene.h \
    $$SrcLoc/trace.h \
    $$SrcLoc/textitem.h \
    $$SrcLoc/spriteitem.h \
    $$SrcLoc/sprite.h \
    $$SrcLoc/sequence.h \
    $$SrcLoc/scene.h \
    $$SrcLoc/node.h \
    $$SrcLoc/myfastergraphicview.h \
    $$SrcLoc/menuitemlabel.h \
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
    $$SrcLoc/action.h

#end copying to here


symbian:TARGET.UID3 = 0xE2886576

# Smart Installer package's UID
# This UID is from the protected range
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices


SOURCES += main.cpp \
    main_menu.cpp
HEADERS += \
    global_keys.h \
    main_menu.h


# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog \
    android/AndroidManifest.xml \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/res/values-ja/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-es/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-ro/strings.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/res/values-rs/strings.xml \
    android/res/drawable-ldpi/icon.png \
    android/res/values/strings.xml \
    android/res/values/libs.xml \
    android/res/values-it/strings.xml \
    android/res/drawable-mdpi/icon.png \
    android/AndroidManifest.xml \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/layout/splash.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog

















