#include "Journal.h"

Journal::Journal(const std::string fileName, const Importance importanceByDefault)
	: _logFile(fileName, std::ios::in | std::ios::out | std::ios::binary), _importanceByDefault(importanceByDefault)
{
	if (!_logFile.is_open())
		throw std::invalid_argument("Cannot open file " + fileName);

	_lines = std::count(std::istreambuf_iterator<char>(_logFile), 
						std::istreambuf_iterator<char>(), '\n');
}

std::fstream &Journal::getFileStream() {
	return _logFile;
}

int Journal::getLines() const {
	return _lines;
}

void Journal::setDefaultImportance(const Importance newDefaultImportance) {
	_importanceByDefault = newDefaultImportance;
}

void Journal::addLogEntry(Message &msg)
{
	if (msg.getImportance() == Importance::Default)
		msg.setImportance(_importanceByDefault);
	if (msg.getImportance() >= _importanceByDefault)
	{   
		std::lock_guard lock(m);
		_logFile << '#' << ++_lines << ' ' <<  msg << '\n';
		_logFile.flush();
	}
}
