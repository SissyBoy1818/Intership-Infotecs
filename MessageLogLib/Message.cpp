#include "Message.h"

Message::Message(std::string data, Importance importance)
    : _data(data), _importance(importance)
{
    time(&_creationTime);
}

std::string Message::getData() const noexcept{
    return _data;
}

time_t Message::getCreationTime() const noexcept{
    return _creationTime;
}

Importance Message::getImportance() const noexcept{
    return _importance;
}

void Message::setData(const std::string newData) noexcept{
    _data = newData;
}

void Message::setImportance(const Importance newImportance) noexcept{
    _importance = newImportance;
}

void Message::setCurrentTime() noexcept{
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

Importance stringToImportance(const std::string_view& str)
{
    if (str == "low") return Importance::Low;
    if (str == "medium") return Importance::Medium;
    if (str == "high") return Importance::High;
    if (str.empty()) return Importance::Default;
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
