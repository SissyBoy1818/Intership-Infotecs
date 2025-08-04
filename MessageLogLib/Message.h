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

    std::string getData() const noexcept;
    time_t getCreationTime() const noexcept;
    Importance getImportance() const noexcept;

    void setData(const std::string newData) noexcept;
    void setImportance(const Importance newImportance) noexcept;
    void setCurrentTime() noexcept;
};

std::ostream& operator<<(std::ostream& os, const Message &msg);
Importance stringToImportance(const std::string_view& str);
std::string importanceToString(const Importance& imp);

#endif // MESSAGE_H