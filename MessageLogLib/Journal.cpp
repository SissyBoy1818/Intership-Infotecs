#include "Journal.h"

Journal::Journal(std::string fileName, Importance importanceByDefault)
    : _logFile(fileName), _importanceByDefault(importanceByDefault)
{
    if (!_logFile.is_open())
        throw std::exception();
}

void Journal::setDefaultImportance(Importance newDefaultImportance)
{
    _importanceByDefault = newDefaultImportance;
}

void Journal::addLogEntry(const Message &msg)
{
    if (static_cast<int>(msg.getImportance()) >= static_cast<int>(_importanceByDefault))
    {
        _logFile << msg << '\n';
        _logFile.flush();
    }
}
