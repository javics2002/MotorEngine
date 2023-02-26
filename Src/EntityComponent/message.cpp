#include "message.h"


namespace me {

    Message::Message() : type(), data() {};

    Message::Message(MessageType type, MessageData data) : type(type), data(data) {};

    MessageType Message::getType() const {
        return type;
    };

    MessageData Message::getData() const {
        return data;
    };

    Message* Message::clone() const {
        return new Message(*this);
    };

};