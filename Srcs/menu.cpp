#include "menu.h"

Menu * Menu::menuWithmenuItems(MenuItem *item,...) {
    if (item != NULL) {
        Menu* newMenu = new Menu;
        newMenu->addChild(item);
        newMenu->items.append(item);
        item->setEnabled(1);
        MenuItem *newItem;
        va_list list;
        va_start(list,item);
        newItem = va_arg(list,MenuItem*);
        while (newItem != NULL) {
            newMenu->addChild(newItem);
            newMenu->items.append(newItem);
            newItem->setEnabled(1);
            newItem = va_arg(list,MenuItem*);
        }
        va_end(list);
        return newMenu;

    }
    else {
        //fileStream << "Game Engine :: Warning : you are trying to construct an empty menu, it will return for you a NULL pointer";
        return NULL;
    }
}

void Menu::setEnabled(bool enabled) {
    MenuItem *item;
    for (int i=0;i < items.size();i++) {
        item = items.at(i);
        item->setEnabled(enabled);
    }
}

void Menu::addChild(Node *child, int tag, int z) {
    Node::addChild(child,tag,z);
}
