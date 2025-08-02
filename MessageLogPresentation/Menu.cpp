#include "Menu.h"

Menu::Menu(Journal &journal) 
	: _journal(journal), _lastMessage(nullptr), _sendingThread([&]{sendMessage();}), _running(true)
{
	_sendingThread.detach();
}

void Menu::printMenu() const
{
	std::cout <<  "Menu\n";
}

bool Menu::handleControllers()
{
	std::cout << "a\n";
	int a = 1;
	std::cin >> a;
	if (a==0) return _running = false;

   	std::cout << "a\n";
	createMessage();
   	std::cout << "a\n";
   return true;
}

void Menu::createMessage()
{
	{
		std::lock_guard lock(_sendingMutex);

		_lastMessage = new Message;

		std::string tmp;
		std::cout << "Enter a message: ";
		std::cin >> tmp;
		_lastMessage->setData(tmp);
		std::cout << "Enter an importance of message: ";
		std::cin >> tmp;
		try {
			_lastMessage->setImportance(stringToImportance(tmp.c_str()));
		} catch(const std::exception& e) {
			std::cerr << e.what() << '\n';
		}

		_lastMessage->setCurrentTime();
	}
	
	_cv.notify_one();
}

void Menu::sendMessage()
{
	while (_running)
	{
		std::unique_lock lock(_sendingMutex);
		_cv.wait(lock);

		if (_lastMessage)
			_journal.addLogEntry(*_lastMessage);
		
		delete _lastMessage;
		_lastMessage = nullptr;
	}
}

void Menu::stop()
{
	_running = false;
	_cv.notify_all();
}
