#include "message.h"


namespace me {

    Message::Message() : type(), data() {};

    Message::Message(MessageType type, MessageData data) : type(type), data(data) {};

    Message::~Message() {};

    Message* Message::clone() const {
        return new Message(*this);
    };

};