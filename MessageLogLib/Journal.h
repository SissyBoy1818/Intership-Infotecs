#ifndef JOURNAL_H
#define JOURNAL_H

#include <fstream>
#include "Message.h"

class Journal
{
private:
    std::ofstream _logFile;
    Importance _importanceByDefault;

public:
    Journal(std::string fileName, Importance importanceByDefault);
    ~Journal() = default;
    
    void setDefaultImportance(Importance newDefaultImportance); // Изменить уровень важности сообщения по умолчанию
    void addLogEntry(const Message &msg); // Записать новое сообщение в журнал
};

#endif // JOURNAL_H