#ifndef MENU_H
#define MENU_H

#include "layer.h"
#include "menuitem.h"

class Menu : public Layer
{

public:
    static Menu* menuWithmenuItems(MenuItem* item,...);
    void setEnabled(bool);
private:
    Menu() {}
    ~Menu() {}
    void addChild(Node *child, int tag = 0, int z = 0);
    QList <MenuItem*> items;
};

#endif // MENU_H
