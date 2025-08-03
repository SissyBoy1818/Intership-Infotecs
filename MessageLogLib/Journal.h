#ifndef JOURNAL_H
#define JOURNAL_H

#include <fstream>
#include <mutex>
#include <algorithm>
#include <vector>
#include "Message.h"

class Journal
{
private:
    std::fstream _logFile;
    Importance _importanceByDefault;
    std::mutex m;

public:
    Journal(const std::string fileName, const Importance importanceByDefault);
    ~Journal() = default;
    
    std::fstream& getFileStream();
    void setDefaultImportance(const Importance newDefaultImportance); // Изменить уровень важности сообщения по умолчанию
    void addLogEntry(Message &msg); // Записать новое сообщение в журнал
};

#endif // JOURNAL_H