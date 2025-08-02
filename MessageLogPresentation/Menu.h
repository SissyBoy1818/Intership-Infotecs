#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include "Journal.h"

class Menu
{
private:
    Journal& _journal;
    Message* _lastMessage;

    std::thread _sendingThread;
    std::condition_variable _cv;
    std::mutex _sendingMutex;
    std::atomic<bool> _running;

    void createMessage();
    void sendMessage();

public:
    Menu(Journal &journal);
    ~Menu() = default;

    void printMenu() const;
    bool handleControllers();

    void stop();
};

#endif // MENU_H