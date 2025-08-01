#ifndef MESSAGE_H
#define MESSAGE_H

#include <ctime>
#include <string>

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
};

#endif // MESSAGE_H