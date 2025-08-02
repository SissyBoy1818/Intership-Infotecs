#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Journal.h"

class Menu
{
private:
    Journal &_journal;

public:
    Menu(Journal &journal);
    ~Menu() = default;

    void printMenu() const;
    void handleControllers();
    void createMessage();
    void sendMessage(std::string,std::string);
};

#endif // MENU_H