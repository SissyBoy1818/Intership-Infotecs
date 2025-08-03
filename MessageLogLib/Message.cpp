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

void Message::setData(const std::string newData) {
    _data = newData;
}

void Message::setImportance(const Importance newImportance) {
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

    os << buffer << "| " << importanceToString(msg.getImportance()) << ": " << msg.getData();

    return os;
}

Importance stringToImportance(const char *str)
{
    if (strcmp(str,"low")==0) return Importance::Low;
    if (strcmp(str,"medium")==0) return Importance::Medium;
    if (strcmp(str,"high")==0) return Importance::High;
    if (strlen(str)==0) return Importance::Default;
    throw std::invalid_argument("Unkown importance: " + std::string(str));
}

std::string importanceToString(const Importance &imp)
{
    switch (imp)
    {
    case Importance::Low:
        return "low";
        break;
    case Importance::Medium:
        return "medium";
        break;
    case Importance::High:
        return "high";
        break;
    case Importance::Default:
        break;
    }

    return "";
}
