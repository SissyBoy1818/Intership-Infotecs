#ifndef MESSAGE_H
#define MESSAGE_H

#include <ctime>
#include <cstring>
#include <ostream>

enum class Importance {Low, Medium, High};

class Message
{
private:
    std::string _data;
    time_t _creationTime;
    Importance _importance;

public:
    Message(std::string data, Importance importance);
    ~Message() = default;

    std::string getData() const;
    time_t getCreationTime() const;
    Importance getImportance() const;
};

std::ostream& operator<<(std::ostream& os, const Message &msg);
Importance stringToImportance(const char *str);

#endif // MESSAGE_H