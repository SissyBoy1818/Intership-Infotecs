#include "Menu.h"

Menu::Menu(Journal &journal) 
	: _journal(journal), _lastMessage(nullptr), _sendingThread([&]{sendMessage();}), _running(true)
{
	_sendingThread.detach();
}

void Menu::printMenu() const
{
	std::cout <<  "Journal commands:\n1. Add new log entry\n2. Set default importance\n3. Show statistic\n0. Exit\n>>> ";
}

bool Menu::handleControllers()
{
	char tmp;
	std::cin.get(tmp);
	std::cin.ignore();
	switch (tmp)
	{
	case '1':
		createMessage();
		break;

	case '2':
		setImportance();
		break;

	case '3':
		showStatistic();
		break;

	case '0':
		stop();
		return false;
		break;

	default:
		std::cerr << "Wrong input.\n";
		break;
	}

	return true;
}

void Menu::createMessage()
{
	{
		std::lock_guard lock(_sendingMutex);

		_lastMessage = new Message;

		std::string tmp;
		std::cout << "Enter a message: ";
		std::getline(std::cin, tmp);
		_lastMessage->setData(tmp);
		std::cout << "Enter an importance of message (skip to set default): ";
		std::getline(std::cin, tmp);

		try {
			_lastMessage->setImportance(stringToImportance(tmp.c_str()));
		} catch(const std::exception& e) {
			std::cerr << e.what() << '\n';
		}

		_lastMessage->setCurrentTime();
	}
	
	_cv.notify_one();
}

void Menu::setImportance()
{
	std::string tmp;
	std::cout << "Enter new default importance: ";
	std::getline(std::cin, tmp);

	try {
		_journal.setDefaultImportance(stringToImportance(tmp.c_str()));
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}

void Menu::showStatistic()
{
	_journal.getFileStream().seekg(0, _journal.getFileStream().beg);

	std::map<Importance, int> counter;

	counter[Importance::Low] = 0;
	counter[Importance::Medium] = 0;
	counter[Importance::High] = 0;

	while(!_journal.getFileStream().eof())
	{
		std::string tmp;
		_journal.getFileStream().seekg(24, _journal.getFileStream().cur);
		_journal.getFileStream() >> tmp;
		tmp.pop_back();
		if (counter.count(stringToImportance(tmp.c_str())))
			counter[stringToImportance(tmp.c_str())]++;
		std::getline(_journal.getFileStream(), tmp);
	}

	for (const auto& imp : counter)
	{
		std::cout << importanceToString(imp.first) << ' ' << imp.second << '\n';
	}
	
	_journal.getFileStream().clear();
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
