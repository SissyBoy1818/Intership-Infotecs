#ifndef MESSAGE_H
#define MESSAGE_H

#include <ctime>
#include <cstring>
#include <ostream>

enum class Importance {Low, Medium, High, Default};

class Message
{
private:
    std::string _data;
    time_t _creationTime;
    Importance _importance;

public:
    Message(std::string data, Importance importance);
    Message() = default;
    ~Message() = default;

    std::string getData() const;
    time_t getCreationTime() const;
    Importance getImportance() const;

    void setData(const std::string newData);
    void setImportance(const Importance newImportance);
    void setCurrentTime();
};

std::ostream& operator<<(std::ostream& os, const Message &msg);
Importance stringToImportance(const char *str);
std::string importanceToString(const Importance& imp);

#endif // MESSAGE_H