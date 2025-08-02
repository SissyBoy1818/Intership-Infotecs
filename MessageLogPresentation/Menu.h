#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <thread>
#include <condition_variable>
#include "Journal.h"

class Menu
{
private:
    Journal &_journal;
    std::thread _sendingThread;

public:
    Menu(Journal &journal);
    ~Menu() = default;

    void printMenu() const;
    bool handleControllers();
    void createMessage();
    void sendMessage(std::string data, std::string importance);
};

#endif // MENU_H