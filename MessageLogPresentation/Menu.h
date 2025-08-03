#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <map>
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

    void createMessage(); // Запросить ввод у пользователя
    void setImportance(); // Изменить важность по умолчанию
    void showStatistic(); // Вывести в терминал статистику по записям
    
    void sendMessage(); // Функция для потока, записывающего сообщения в файл
    void stop(); // Останов для корректного завершения записи в файл

public:
    Menu(Journal &journal);
    ~Menu() = default;

    void printMenu() const; // Вывод меню в консоль
    bool handleControllers(); // Получение пользовательского ввода для выбора пункта меню  
};

#endif // MENU_H