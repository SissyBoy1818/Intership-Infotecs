#include "Message.h"

Message::Message(std::string data, Importance importance)
    : _data(data), _importance(importance)
{
    _creationTime = time(0);
}