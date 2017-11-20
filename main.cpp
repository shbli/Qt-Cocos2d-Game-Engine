#include <QApplication>
//here's the first one to change
#include "main_menu.h"
#include "Srcs/game_engine.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //set up audio playback
    audioManager::setUpAudioManager();
    //here is the second main_menu to change
    Director::sharedDirector()->startWithScene(main_menu::scene());
    return app.exec();
}
