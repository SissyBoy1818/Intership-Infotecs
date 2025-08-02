#include "Menu.h"

Menu::Menu(Journal &journal) : _journal(journal)
{}

void Menu::printMenu() const
{
    std::cout <<  "Menu\n";
}

bool Menu::handleControllers()
{
    int a;
    std::cin >> a;
    if (a==0) return false;
   // make something
   createMessage();
   return true;
}

void Menu::createMessage()
{
    std::string content, importance;
    std::cout << "Enter a message: ";
    std::cin >> content;
    std::cout << "Enter an importance of message: ";
    std::cin >> importance;
    sendMessage(content, importance);
}

void Menu::sendMessage(std::string data, std::string importance)
{
    Importance imp;
    try {
        imp = stringToImportance(importance.c_str());
        _journal.addLogEntry(Message(data,imp));
    } catch(const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }
}
