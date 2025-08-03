#include "Journal.h"

Journal::Journal(const std::string fileName, const Importance importanceByDefault)
	: _logFile(fileName, std::ios::in | std::ios::out | std::ios::binary), _importanceByDefault(importanceByDefault)
{
	if (!_logFile.is_open())
		throw std::invalid_argument("Cannot open file " + fileName);
}

std::fstream &Journal::getFileStream() {
	return _logFile;
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
		_logFile.seekp(0, _logFile.end);
		_logFile <<  msg << '\n';
		_logFile.flush();
	}
}
