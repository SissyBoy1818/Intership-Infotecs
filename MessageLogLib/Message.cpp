#include "Message.h"

Message::Message(std::string data, Importance importance)
    : _data(data), _importance(importance)
{
    time(&_creationTime);
}

std::string Message::getData() const{
    return _data;
}

time_t Message::getCreationTime() const{
    return _creationTime;
}

Importance Message::getImportance() const{
    return _importance;
}

void Message::setData(std::string newData) {
    _data = newData;
}

void Message::setImportance(Importance newImportance) {
    _importance = newImportance;
}

void Message::setCurrentTime() {
    time(&_creationTime);
}

std::ostream &operator<<(std::ostream &os, const Message &msg)
{
    time_t creationTime = msg.getCreationTime();
    tm *tm = localtime(&creationTime);
    char buffer[32]{'\0'};

    std::strftime(buffer, 32, "%d.%m.%Y %H:%M:%S", tm);

    std::string importance;
    switch (msg.getImportance())
    {
    case Importance::Low:
        importance = "Low";
        break;
    case Importance::Medium:
        importance = "Medium";
        break;
    case Importance::High:
        importance = "High";
        break;
    }

    os << buffer << "| " << importance << ": " << msg.getData();

    return os;
}

Importance stringToImportance(const char *str)
{
    if (strcmp(str,"low")==0) return Importance::Low;
    if (strcmp(str,"medium")==0) return Importance::Medium;
    if (strcmp(str,"high")==0) return Importance::High;
    throw std::invalid_argument("Unkown importance: " + std::string(str));
}
    