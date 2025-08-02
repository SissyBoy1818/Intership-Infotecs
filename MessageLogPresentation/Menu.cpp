#include "Menu.h"

Menu::Menu(Journal &journal) : _journal(journal)
{}

void Menu::printMenu() const
{
    std::cout <<  "Menu\n";
}

void Menu::handleControllers()
{
   // make something
   createMessage();
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

void Menu::sendMessage(std::string a, std::string b)
{
    Importance imp;
    try {
        imp = stringToImportance(b.c_str());
        _journal.addLogEntry(Message(a,imp));
    } catch(const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }
}
